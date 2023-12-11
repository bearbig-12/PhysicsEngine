#include "GameEngine.h"
std::vector<GameObject*> GameEngine::objects;
std::vector<GameObject*> GameEngine::objects_collider;



int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;
int GameEngine::LastShot = 0;

int GameEngine::HP = 10;
int GameEngine::Score = 0;


void GameEngine::UpdateGame()
{
	//Work out the delta time - the time between the last frame and this frame
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	
	

	float deltaTime = (newTimeSinceStart - oldTimeSinceStart);
	
	deltaTime /= 1000.f;
	std::cout << "Delta Time (seconds): " << deltaTime << std::endl; //- if you want to check the delta time

	if (GameObject::keys['t'] == true)	// show the score
	{
		std::cout << "Player HP : " << HP << " , " << "Score : " << Score << std::endl;
	}

	if (GameObject::keys['f'] == true)
	{
		int currentTime = glutGet(GLUT_ELAPSED_TIME);
		if (currentTime - LastShot > 1000)	// For the next bullet shooting, player need to wait for 1 sec cooldown
		{
			LastShot = currentTime;
		
			GameObject* bullet = new Bullet(objects[0]);	// object[0] is player.
			AddGameObject(bullet);							// need to bind bullet's postion with player's position

			GameObject* s_colldier = new CollidierSphere(bullet->x, bullet->y, bullet->z, 0.2f, bullet);
			
			AddObjects_Collider(s_colldier);
			
		}

	}

	
	

	// O(n2) cost for checking collider
	for (int i = 0; i < objects_collider.size() - 1; ++i)
	{
		for (int j = i + 1; j < objects_collider.size(); ++j)
		{

			if (objects_collider[i]->mType == 1 && objects_collider[j]->mType == 1)	// Type 1 is sphere collider
			{
				CollidierSphere* temp = (CollidierSphere*)objects_collider[i];

				if (temp->Sphere_SphereCheck(objects_collider[j]) == true && i <= 7)	// bullet and bullet do not work
				{
					
					std::cout << "Sphere Collision detective";
					std::cout << std::endl;
					temp->r = 1.0f;
					temp->g = 1.0f;
					temp->b = 1.0f;

					Bullet* bullet = (Bullet*)objects[j];	// To access bullet's members(ex mass, velocity and etc)
					Sphere* sphere = (Sphere*)objects[i];	// Need to cast type

					float Bullet_mass = bullet->bullet_mass;
					float Sphere_mass = sphere->mass;

					float coefficient = 0.5f;

					// J = -(V1(old) - V2(old)) dot(normal)(1+coeff) / normal dot(normal) * ( 1.0f/ M1 + 1.0f/M2)

					float Impulse; // it's only affecting velocity
					Vec3 Velocity_s = Vec3(bullet->bullet_Velocity - sphere->Sphere_velocity); //Vs = V1(old) - V2(old)
					//saperating velocity can be seen and as regarded as the relative velocity
					Vec3 temp = Vec3(bullet->x - sphere->x, bullet->y - sphere->y, bullet->z - sphere->z);
					Vec3 Normal_Vec = Normalization(temp);

					Impulse = -(Dot(Velocity_s, Normal_Vec) * (1.0f + coefficient))
						/
						(Dot(Normal_Vec, Normal_Vec) * ((1.0f / Bullet_mass) + (1.0f / Sphere_mass)));

					bullet->bullet_Velocity = bullet->bullet_Velocity + (Normal_Vec * (Impulse / Bullet_mass));
					sphere->Sphere_velocity = sphere->Sphere_velocity - (Normal_Vec * (Impulse / Sphere_mass));	
					// Newton's 3rd Law, every action has equal on opposite reaction

					/*delete bullet_objects[bullet_count];
					bullet_objects.pop_back();*/
					
					
					delete objects[j];
					objects.erase(objects.begin() + j);
					
					delete objects_collider[j];
					objects_collider.erase(objects_collider.begin() + j);
					//To delete bullet obj and collider when sphere to sphere check is true

				}

			}
			
			if (objects_collider[i]->mType == 0 && objects_collider[j]->mType == 0) // type 0 is Cube obj
			{
				ColliderCube* temp = (ColliderCube*)objects_collider[j];
				if(temp->AABB_AABB(objects_collider[i]) == true)
				{
					if (temp->g != 1.0f)
					{
						std::cout << "Player got 10 point!!" << std::endl;
						Score += 10;
					}
					std::cout << "Cube Collision detective" << std::endl;
					temp->r = 1.0f;
					temp->g = 1.0f;
					temp->b = 1.0f;
					
				}
			}
			if (objects_collider[i]->mType == 0 && objects_collider[j]->mType == 2)	// if player hit against wall obj
			{																		// type 2 is wall
				ColliderCube* temp = (ColliderCube*)objects_collider[j];
				if (temp->AABB_AABB(objects_collider[i]) == true)
				{
					std::cout << "Cube Collision detective" << std::endl;
					temp->r = 1.0f;
					temp->g = 1.0f;
					temp->b = 1.0f;


					Player* player = (Player*)objects[i];	// To access bullet's members(ex mass, velocity and etc)
					Cube* wall = (Cube*)objects[j];	// Need to cast type

					float Player_mass = player->mMass;
					float Wall_mass = 100.0f;
					float coefficient = 1.0f;
					

					// J = -(V1(old) - V2(old)) dot(normal)(1+coeff) / normal dot(normal) * ( 1.0f/ M1 + 1.0f/M2)

					float Impulse; // it's only affecting velocity
					Vec3 Velocity_s = Vec3(player->mVelocity - wall->velocity); //Vs = V1(old) - V2(old)
					//saperating velocity can be seen and as regarded as the relative velocity
					Vec3 temp = Vec3(player->x - wall->x, player->y - wall->y, player->z - wall->z);
					Vec3 Normal_Vec = Normalization(temp);

					Impulse = -(Dot(Velocity_s, Normal_Vec) * (1.0f + coefficient))
						/
						(Dot(Normal_Vec, Normal_Vec) * ((1.0f / Player_mass) + (1.0f / Wall_mass)));

					player->mVelocity = player->mVelocity + (Normal_Vec * (Impulse / Player_mass));
					//wall->velocity = wall->velocity - (Normal_Vec * (Impulse / Wall_mass));
					// Newton's 3rd Law, every action has equal on opposite reaction
				}
			}

			if (objects_collider[i]->mType == 0 && objects_collider[j]->mType == 1 && j <= 7)
			{																		// AABB to sphere check
				ColliderCube* temp = (ColliderCube*)objects_collider[i];

				if (temp->AABB_Sphere(objects_collider[j]) == true)
				{
					if (objects_collider[j]->g != 1.0f)
					{
						std::cout << "Get 10HP!!!" << std::endl;
						HP += 10;
					}
					std::cout << "Sphere to AABB Collision detective";
					std::cout << std::endl;
					objects_collider[j]->r = 1.0f;
					objects_collider[j]->g = 1.0f;
					objects_collider[j]->b = 1.0f;
				}
			
				
			}

		}
	}
	
	//Update all our game objects
	for (int i = 0; i < objects.size(); ++i)
	{
		
		objects[i]->Update(deltaTime);
	}
	
	for (int i = 0; i < objects_collider.size(); ++i)
	{
		objects_collider[i]->Update(deltaTime);
	}

	glutPostRedisplay();
}
// Draw objects which is in vectors
void GameEngine::DrawGame(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Position the objects for viewing
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



	//Draw all our game objects
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Draw();
	}
	

	for (int i = 0; i < objects_collider.size(); ++i)
	{
		objects_collider[i]->Draw();
	}
	glutSwapBuffers();
}

void GameEngine::CleanUpEngine()
{
	for (int i = objects.size() - 1; i >= 0; --i)
	{
		delete objects[i];
	}
	objects.clear();

	for (int i = objects_collider.size() - 1; i >= 0; --i)
	{
		delete objects_collider[i];
	}
	objects_collider.clear();
}

void GameEngine::ResizeWindow(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void GameEngine::keyInput(unsigned char key, int x, int y)
{
	GameObject::keys[key] = true;
	//If you want to see keys pressed printed to the console
	//std::cout << "Key pressed: " << key << std::endl;

	switch (key)
	{
	case 27: // Esc key
		CleanUpEngine();
		exit(0);
		break;
	default:
		break;
	}
}

void GameEngine::keyInputUp(unsigned char key, int x, int y)
{
	GameObject::keys[key] = false;
}

void GameEngine::keySpecialInput(int key, int x, int y)
{
	GameObject::specialKeys[key] = true;
}

void GameEngine::keySpecialInputUp(int key, int x, int y)
{
	GameObject::specialKeys[key] = false;
}

void GameEngine::InitEngine(int argc, char** argv, const char* windowTitle, int width, int height)
{
	glutInit(&argc, argv); //this is why we need to use argc and argv

	glutInitContextVersion(2, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height); //changed to include the parameters
	glutInitWindowPosition(100, 100);
	glutCreateWindow(windowTitle); //changed to include the parameters

	glewExperimental = GL_TRUE;
	glewInit();

	//Draw the obejects on the screen
	glutDisplayFunc(DrawGame); //changed to include the GameEngine function
	// Window shape and name
	glutReshapeFunc(ResizeWindow); //changed to include the GameEngine function

	glutIdleFunc(UpdateGame); //changed to include the GameEngine function

	//It is Keyboard CallBakcs.
	glutKeyboardFunc(keyInput);
	glutKeyboardUpFunc(keyInputUp);
	glutSpecialFunc(keySpecialInput);
	glutSpecialUpFunc(keySpecialInputUp);


	
}


void GameEngine::AddGameObject(GameObject* object)
{
	objects.push_back(object);
}

void GameEngine::AddObjects_Collider(GameObject* obj_collider)
{
	objects_collider.push_back(obj_collider);
}



void GameEngine::StartEngine()
{
	std::cout << "Press escape to exit the game." << std::endl;
	std::cout << "W key is Forward move, S key is Backward move" << std::endl;
	std::cout << "Space bar for Jump" << std::endl;
	std::cout << "Right arrow key for turn right" << std::endl;
	std::cout << "Left arrow key for turn Left" << std::endl;
	std::cout << "f key is for shooting bullet" << std::endl;
	std::cout << "t key is for show status " << std::endl;
	std::cout << "If players collet sphere obj, players get 10 HP" << std::endl;
	std::cout << "If players collet box obj, players get 10 point" << std::endl;

	glutMainLoop();
}


