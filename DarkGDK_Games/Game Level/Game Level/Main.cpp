
/*
 *  Game Level - Started as a simple mock of the DarkGDK Sample
 *               "Game Level" now, it is a full working FPS.
 *
 *  Simple FPS DarkGDK Game
 *  Lead Programmer:     Philip "ZeroCooL" Simonson
 *  Programmer:          Sweden "Phontric"
 *
 */


#include "DarkGDK.h"
#include "SC_Collision.h"

//global variables
int map = 1; //defines map as object 1
int character = 2; //defines main character as 2
int sphereCam = 3;//used as a camera
int skyBox = 4; //defines the skybox
float vx = 0;
float vy = 0;
float vz = 0;
float gravity = -0.05f;
float slope = 0.5f;
float radius = 7.0f;
int ground = 1;
int jumptimer = 0;

bool Moving = false; // this is used because dbKeystate within a dbKeystate is a bag of shit
bool Running = false;
bool noClip = false;
bool PressingF1 = false; //used when going into noclip
//bool mouseClicked = false; //used to stop multiple events fired on 1 click

float pos_x = 0.0f;
float pos_y = 0.0f;
float pos_z = 0.0f;

char coords_message[256]; // position to the game matrix
char coords_message2[256]; // position relative to the map

// here is the function prototypes for my crafty work
void loadMap(void);
void loadSkyBox(void);
void loadMainCharacter(void);
void updateCamera(int MouseDiffX, int MouseDiffY);
void playerJump(void);
void controlCharacter(void);
void inputKeys(void);
void displayCoordsOfPlayer(void);

void DarkGDK(void)
{
	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn();
	dbSyncRate(60);

	SC_Start(); //starts sparkys
	dbBackdropOff();
	dbAutoCamOff(); //stops stupid ass objects from moving the camera when they are loaded
	dbSetDisplayMode(800, 600, 32);

	// switch to the media directory
	SetCurrentDirectory("media");

	// load all the beginning stuff
	loadMap();
	loadMainCharacter();
	loadSkyBox();

	// position the camera
	//dbPositionCamera(434, 42, -517);

	// position the player
	//dbPositionObject(character, dbObjectPositionX(map)+70, dbObjectPositionY(map)+120, dbObjectPositionZ(map)-110); //places player within map
	dbPositionObject(character, dbObjectPositionX(map), dbObjectPositionY(map)+120, dbObjectPositionZ(map)+60); //places player within map

	while (LoopGDK())
	{
		updateCamera(dbMouseMoveX(), dbMouseMoveY());
		controlCharacter();
		inputKeys();

		dbSync();
	}

	return;
}

void loadMap(void)
{
	dbLoadObject("test_level.x", map);
	dbSetObjectLight(map, 0);
	dbRotateObject(map, -90.0f, 0.0f, 0.0f);
	SC_SetupComplexObject(map, 1, 2);
	//SC_AllowObjectScaling(1);
	//dbScaleObject(map, 150, 100, 150);
	SC_UpdateObject(map); //updates the map's collision box
}

void loadSkyBox(void)
{
	// load a model for our sky
	dbLoadObject("skybox2.x", 2);
	dbSetObjectLight(2, 0);
	dbSetObjectTexture(2, 3, 2);
	dbScaleObject(2, 5000, 5000, 5000);
}

void loadMainCharacter(void)
{
	dbMakeObjectBox(character, 30, 150, 30);
//	dbPositionObject(character, (dbObjectPositionX(map)/2)+50, (dbObjectPositionY(map)/2)-200, (dbObjectPositionZ(map)/2)); //places player within map
	SC_SetupObject(character, 1, 2);//used to check collisions against the environment
	dbHideObject(character); //hides the main character as this is a FPS
	
	//make main characters camera, this is a sphere that will work as a camera
	dbMakeObjectSphere	(sphereCam, 20 );//make the object that follows the player, the camera follows this object
	dbScaleObject		(sphereCam, .0001, .0001, .0001 );//scale camera out of view .0001, .0001, .0001
	dbPositionObject	(sphereCam, dbObjectPositionX(character), dbObjectPositionY(character) + 10, dbObjectPositionZ(character) );//position it where it goes

	/*
		//add these after updateEnemyAnimations
		// sounds for when the soldier is hit
		dbLoadSound("sounds//soldier//groan1.wav", characterGroan1);
		dbLoadSound("sounds//soldier//groan2.wav", characterGroan2);
		dbLoadSound("sounds//soldier//groan3.wav", characterGroan3);
		dbLoadSound("sounds//soldier//groan4.wav", characterGroan4);
		dbLoadSound("sounds//soldier//groan5.wav", characterGroan5);
		//death sound
		dbLoadSound("sounds//soldier//death1.wav", characterDeathScream);
		//makes the collision hit box 
		dbMakeObjectBox(myCollisionHitBox, 30, 150, 30);
		SC_SetupObject(myCollisionHitBox, 1, 2);//used to check collisions against enemies
		dbHideObject(myCollisionHitBox);
	*/
}

void updateCamera(int MouseDiffX, int MouseDiffY)
{
	if (noClip == false) //if(noClip == false /* add this after updateEnemyAnimation*/&& gameOver == false)
	{
		static float CamSpeed = 0.07;
		float RotX;
		float RotY;
		RotX = dbObjectAngleX(3);
		RotY = dbObjectAngleY(3);
				
		RotX = dbWrapValue(RotX + float(MouseDiffY) * CamSpeed); //- because when u move the mouse frwd u want him to look up
		RotY = dbWrapValue(RotY + float(MouseDiffX) * CamSpeed); 
				
		//keeps camera from turning upside down and also keeps movement smooth

		dbPositionObject ( sphereCam, dbObjectPositionX(character), dbObjectPositionY(character) + 10, dbObjectPositionZ(character));
		//move the object that follows the character
		dbPositionCamera ( 0, dbObjectPositionX(sphereCam), dbObjectPositionY(sphereCam), dbObjectPositionZ(sphereCam) );//move the camera to the object that follows the character
		// code below makes sure the camera is within boundaries
		// limits downwards point
		if(RotX < 18.0)
		{
				dbRotateObject(3, RotX, RotY, 0);//allows for player to look up and down with the mouse
				dbRotateCamera	 ( dbObjectAngleX(3), dbObjectAngleY(3), dbObjectAngleZ(3) );//rotate the camera to the object that follows the character
				dbRotateObject(2, -RotX, RotY, 0);//allows for player to look up and down with the mouse	 
		}
		else if (RotX > 18.0 && RotX < 60.0)
		{
				dbRotateObject(3, 18.0, RotY, 0);//allows for player to look up and down with the mouse
				dbRotateCamera	 ( dbObjectAngleX(3), dbObjectAngleY(3), dbObjectAngleZ(3) );//rotate the camera to the object that follows the character
				dbRotateObject(2, -18.0, RotY, 0);//allows for player to look up and down with the mouse	
		}
		// limits upwards point
		if(RotX > 345.0 && RotX < 360.0)
		{
				dbRotateObject(3, RotX, RotY, 0);//allows for player to look up and down with the mouse
				dbRotateCamera	 ( dbObjectAngleX(3), dbObjectAngleY(3), dbObjectAngleZ(3) );//rotate the camera to the object that follows the character
				dbRotateObject(2, -RotX, RotY, 0);//allows for player to look up and down with the mouse	
		}
		else if (RotX > 200.0 && RotX < 345.0)
		{	
				dbRotateObject(3, 345.0, RotY, 0);//allows for player to look up and down with the mouse
				dbRotateCamera	 ( dbObjectAngleX(3), dbObjectAngleY(3), dbObjectAngleZ(3) );//rotate the camera to the object that follows the character
				dbRotateObject(2, -345.0, RotY, 0);//allows for player to look up and down with the mouse	
		}	
	}
	else //allows user to roam around the map (noclip)
	{
		// use my special function
		displayCoordsOfPlayer();

		static float CamSpeed = 0.1;
		float RotX = dbCameraAngleX();
		float RotY = dbCameraAngleY();

		RotX = dbWrapValue(RotX + float(MouseDiffY) * CamSpeed);
		RotY = dbWrapValue(RotY + float(MouseDiffX) * CamSpeed);
		//keeps camera from turning upside down
		
		if(RotX < 320 && RotX > 100)
		{
			RotX = 320;
		}
		if(RotX < 100 && RotX > 57)
		{
			RotX = 57;
		}
		
		dbRotateCamera(RotX, RotY, 0); //ROTATE CAMERA

		// move around with wasd
	   if (dbKeyState(17)) 
	   { // W Move Forward
		   dbMoveCamera(6);  
	   }
	   if (dbKeyState(31)) 
	   { // S Move Back
		   dbMoveCamera(-6);
	   }
	   if (dbKeyState(30))
	   {  // A strafe left
		   dbMoveCameraLeft(0,6);
	   }
	   if (dbKeyState(32))
	   {  // D strafe Right
		   dbMoveCameraRight(0,6);
	   }
	}
/*	//write AFTER updateEnemyAnimations
	handleDamage();
	//positions the collision box, this is used to receive damage from the enemy 
	dbPositionObject(myCollisionHitBox, dbObjectPositionX(character), dbObjectPositionY(character), dbObjectPositionZ(character));
	SC_UpdateObject(myCollisionHitBox);
 */
}

void playerJump(void)
{
	//if player is jumping or falling then apply 'normal' gravity
	//if not attempt to keep the player stuck to the floor
	if ( vy == 0 && jumptimer == 0 ) vy = vy + 10*gravity; 
	else vy = vy + gravity;

	if ( ground == 1 && jumptimer > 0 ) jumptimer--;
	//only jump if on ground, and a certain time after last jump
	if ( ground == 1 ) 
	{
		if ( dbSpaceKey() == 1 && jumptimer == 0 ) 
		{
			vy = vy + 3.3f; //what speed user moves up with jump
			jumptimer = 20;
		}
	}
}

//by using WASD the character can be controlled
void controlCharacter(void)
{
	playerJump(); //handles jumping
	if(noClip == false)
	{
		float oldx;
		float oldy;
		float oldz;

		oldx = dbObjectPositionX(character);
		oldy = dbObjectPositionY(character);
		oldz = dbObjectPositionZ(character);
		
			//if player is jumping or falling then apply 'normal' gravity
			//if not attempt to keep the player stuck to the floor
			if (vy == 0 && jumptimer == 0 )
			{
				vy = vy + 5*gravity;  //speed at which player falls down
			}
			else vy = vy + gravity;
			float angy;
			//apply gravity, and user changes to movement
			angy = dbObjectAngleY(2);
			
			vx = 0;
			vz = 0;
			// KEYS
			if (dbKeyState(30)) //LEFT A
			{
				//only shows forward animations if both are pressed
				 if(Moving == false) //moving is used because keystates work very badly e.g one within another screws up
				 {
					vx = (vx - dbCos(angy))*2; 
					vz = (vz + dbSin(angy))*2; 
				 }
				 else // if forward/backwards is being pressed aswell
				{
					vx = (vx - dbCos(angy))/2; 
					vz = (vz + dbSin(angy))/2; 
				}
			}
			if (dbKeyState(32)) //RIGHT D
				{
					if(Moving == false) //moving is used because keystates work very badly e.g one within another screws up
					{
						vx = (vx + dbCos(angy))*2; 
						vz = (vz - dbSin(angy))*2; 
					}
					else // if forward/backwards is being pressed aswell
					{
						vx = (vx + dbCos(angy))/2; 
						vz = (vz - dbSin(angy))/2; 
					 }
				}
			if (dbKeyState(17) && Running == false) //W FORWARD
				{
					Moving = true;
					//sends first final animation frame, time in millisecs between change of frame, and object to modify
					if(Running == false) //only walk if the player is not running
						{
						   vx = (vx + dbSin(angy))*2.5;
						   vz = (vz + dbCos(angy))*2.5;
						}
				}
				else if (dbKeyState(31)) //S BACKWARDS
				{
					Moving = true;
					//sends first final animation frame, time in millisecs between change of frame, and object to modify
					if(Running == false)
					{
						vx = (vx - dbSin(angy))*2.2;
						vz = (vz - dbCos(angy))*2.2;
					}
				}
				else 
				{
					if(Running == false)
					{
						Moving = false;
					}
				}
				//shift is used to toggle running
				if (dbKeyState(17) && dbKeyState(42))
					{
						 vx = (vx + dbSin(angy))*4.2;
						 vz = (vz + dbCos(angy))*4.2;
						 Running = true;
					}
					else
					{
						Running = false;
					}
					
		//this would be the player's final position without collision
		float x = oldx + vx;
		float y = oldy + vy;
		float z = oldz + vz;
		
		//first handle gravity - seperated from horizontal movement
		//to achieve a more realistic effect
		//Method: simple - cast a sphere vertically down, if it hits the level then
		//                 position the object there (sticky collision) then move 
		//                 on to horizontal movement
		//  more complex - if we were to only use the simple method the player would be 
		//                 allowed to climb almost vertical slopes. Alternative is to
		//                 get the normalY direction to work out how flat the gorund
		//                 below the player is, 0-slope# is flatter, slope#-1 is steeper.
		//                 if it's flat, use sticky collision, if it's steep slide the
		//                 player down the slope. Changing slope# determines how steep the 
		//                 player can climb. NOTE: this also effects stairs.
		int collide = SC_SphereCastGroup( 1, oldx,oldy,oldz, oldx,oldy+vy,oldz, radius,0 );
		
		if ( collide > 0 )
		{
			//how flat is this ground
			float ny = SC_GetCollisionNormalY();
			if ( dbAbs(ny) > slope )
			{
				//FLAT, stick
				oldy = SC_GetStaticCollisionY();
			}
			else
			{
				//STEEP, slide
				x = x - oldx; z = z - oldz;
				oldx = SC_GetCollisionSlideX();
				oldy = SC_GetCollisionSlideY();
				oldz = SC_GetCollisionSlideZ();
				x = x + oldx; z = z + oldz;
			}
			
			//ny#<0 means the player has hit a ceiling rather than a floor
			
			if ( ny > slope )
			{
				//only on ground if standing on flat ground
				ground = 1;
				vy = 0;
			}
			else 
			{
				ground = 0;
				//if player has hit a flat ceiling then stop vy# movement
				if ( ny < -slope ) vy = gravity;
			}
		}
		else
		{
			//nothing below player, not on ground, add vertical speed to player
			oldy = oldy + vy;
			ground = 0;
		}
		
		//jumptimer will decrease only when player is back on ground
		//creates a pause between two successive jumps
		if ( ground == 1 && jumptimer > 0 ) jumptimer--;
		
		//handle horizontal movement as sliding
		//player only collides with group 1 (level) objs and moves freely through others
		collide = SC_SphereSlideGroup( 1, oldx,oldy,oldz, x,oldy,z, radius,0 );
		
		if ( collide > 0 )
		{
			//if hit, reposition player, halt movement vector
			x = SC_GetCollisionSlideX();
			oldy = SC_GetCollisionSlideY();
			z = SC_GetCollisionSlideZ();
			vx = 0;
			vz = 0;
			
			//possible code for giving the player a jumping help up stairs...
			//might be useful if slope# is set very high but stairs are still required
			//dy = oldy - SC_GetStaticCollisionY()
			//if ( dy < slope && dy > 0 && ground == 1 ) vy = 0.5;
		}
			//position the character based on what the player pressed
			dbPositionObject( character,x,oldy,z );
			SC_UpdateObject( character );
	}
}

void inputKeys(void) //used to debug and see how things are going, also hook some events
{
	dbHideMouse(); 
	dbPositionMouse(dbScreenWidth()/2,dbScreenHeight()/2);
	//ALLOWS ME TO FLY AROUND THE MAP, made for debugging ...
	if(dbScanCode() == 59 && PressingF1 == false) //when f1 is pressed go into flying mode or get off it
	{
		PressingF1 = true;
		if(noClip == true)
		{
			noClip = false;
		}
		else //change back to character
		{
			noClip = true;
			//makes sure that the third person camera is correct
		}
	}
	//keeps mode from changing if button is held down
	if(dbScanCode() != 59 && PressingF1 == true)
	{
		PressingF1 = false;
	}

}

void displayCoordsOfPlayer(void)
{
	pos_x = dbCameraPositionX(0);
	pos_y = dbCameraPositionY(0);
	pos_z = dbCameraPositionZ(0);

	sprintf(coords_message, "X [%lg] Y [%lg] Z [%lg]", pos_x, pos_y, pos_z);

/*	pos_x = dbCameraPositionX() * dbObjectPositionX(map);
	pos_y = dbCameraPositionY() * dbObjectPositionY(map);
	pos_z = dbCameraPositionZ() * dbObjectPositionZ(map);

	sprintf(coords_message2, "X [%lg] Y [%lg] Z [%lg]", pos_x, pos_y, pos_z);
 */
	dbText(0, 0, "Your global position is:");
	dbText(0, 14, coords_message);
	//dbText(0, 24, "Your position relative to the map is:");
	//dbText(0, 34, coords_message2);
}
