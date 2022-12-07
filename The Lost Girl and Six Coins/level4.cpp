#include "header.h"
#include "functions.h"

void lvl4_resetPlayerPosition() { 									// this function is for reseting player position to the top-left of the screen
	IMAGE src;
	loadimage(&src, _T("resources/image/char_left2.png")); 			// load character image char_left2 to IMAGE variable "src"
	transparentImage(NULL, 300, 90, &src, 0xffc4c4);				// load IMAGE variable "src" with transparent background to 300, 90
}

void loadLevel4(int livesLeft, int coinCounter) {
	
	// OPEN & PLAY MUSIC RESOURCES
	mciSendString(_T("open resources/sfx/background4.wav alias background4"), NULL, 0, NULL);	
	mciSendString(_T("play background4"), NULL, 0, NULL);
	
	// LOAD DIALOGUE
	loadDialogue(4);

	// LEVEL TUTORIAL
	loadLevelTutorial(4);
	
	// INITIALIZE LEVEL
	loadimage(NULL, _T("resources/image/level4_background.jpg")); 
	
	// ITEMS VARIABLE
	int item1PositionX = 100;
	int item1PositionY = 110;
	int item2PositionX = 100;
	int item2PositionY = 335;
	int item3PositionX = 100;
	int item3PositionY = 550;
	
	bool item1IsCollected = false;
	bool item2IsCollected = false;
	bool item3IsCollected = false;
	
	bool item1 = false;
	bool item2 = false;
	bool item3 = false;
	int itemCounter = 0;
	
	// LOAD ITEM IMAGE
	IMAGE imgitem1;
	loadimage(&imgitem1, _T("resources/image/item1.png"));
	transparentImage(NULL, item1PositionX, item1PositionY, &imgitem1, 0xffc4c4);
	
	IMAGE imgitem2;
	loadimage(&imgitem2, _T("resources/image/item2.png"));
	transparentImage(NULL, item2PositionX, item2PositionY, &imgitem2, 0xffc4c4);
	
	IMAGE imgitem3;
	loadimage(&imgitem3, _T("resources/image/item3.png"));
	transparentImage(NULL, item3PositionX, item3PositionY, &imgitem3, 0xffc4c4);
	
	// LOAD COUNTERS
	loadLivesCounter(livesLeft);      							// load lives counter based on the remaining lives from level 3         
	loadCoinCounter(coinCounter);								// load coin counter based on the coins collected in level 3
	loadItemCounter(itemCounter);								// player starts with 0 item collected
	
	// PLAYER POSITION VARIABLES
	int playerPositionX = 300;									// current player position in x-index
	int playerPositionY = 90;									// current player position in y-index
	int playerMovementCount = 0; 								// number of times the player has moved	
	bool movement = false;										// movement false = player facing left
	int playerStep = 5;											// distance traveled (in pixel) for each player movement
	lvl4_resetPlayerPosition();									// load player in the starting position
	
	// DROP POSITION VARIABLE
	int dropPositionX = 1045;
	int dropPositionY = 485;
	
	// BOSS VARIABLES
	int bossStep = 4;											// distance traveled (in pixel) by boss for each player movement
	int bossX = 1100;											// current boss position in x-index
	int bossY = 450;											// current boss position in y-index
	bool isFacingLeft = true;									
	IMAGE bossModel;											
	loadimage(&bossModel, _T("resources/image/boss_left.png"));
	transparentImage(NULL, bossX, bossY, &bossModel, 0xffc4c4);	// load boss image
	
	// LASER VARIABLES
	time_t seconds;
	int laser1posX = 0;
	int laser1posY = 500;
	int laser2posX = 0;
	int laser2posY = 280;
	int laser3posX = 700;
	int laser3posY = 0;
	int laser4posX = 500;
	int laser4posY = 0;
	bool showLaserHorizontal = false;
	bool showLaserVertical = false;
	bool hitByLaser = false;
	
	while(1) {
		
		// LOADING LASERS
		seconds = time(NULL); 										// update second stored for every while loop		
		
		if(seconds % 3 == 0){ 										// load horizontal laser for every 3 seconds
			loadHorizontalLaser(laser1posX,laser1posY);										
			loadHorizontalLaser(laser2posX,laser2posY);									
			showLaserHorizontal = true;
		}
		else showLaserHorizontal = false;
			
		if(seconds % 4 == 0){ 										// load vertical laser for every 4 seconds
			loadVerticalLaser(laser3posX, laser3posY);
			loadVerticalLaser(laser4posX, laser4posY);
			showLaserVertical = true;
		}
		else showLaserVertical = false;	            
		
		if (_kbhit()) { 											// check for keyboard input
			char input = _getch();									// store keyboard input in variable "input"
			playerMovementCount++;									// increment playerMovementCount
			
			// LASER CONDITIONS
			if((playerPositionY + 70 > laser1posY && laser1posY +  18 > playerPositionY) || (playerPositionY + 70 > laser2posY && laser2posY +  18 > playerPositionY)) { 	// player - horizontal laser collison
				if(showLaserHorizontal == true) {
					mciSendString(_T("open resources/sfx/dead.wav alias dead"), NULL, 0, NULL);	
					mciSendString(_T("play dead"), NULL, 0, NULL);
					livesLeft--;
					hitByLaser = true;	
				}
			}
			
			if((playerPositionX + 70 > laser3posX && laser3posX +  18 > playerPositionX) || (playerPositionX + 70 > laser4posX && laser4posX +  18 > playerPositionX)) {	// player - vertical laser collison
				if(showLaserVertical == true) {
					mciSendString(_T("open resources/sfx/dead.wav alias dead"), NULL, 0, NULL);	
					mciSendString(_T("play dead"), NULL, 0, NULL);
					livesLeft--;
					hitByLaser = true;
				}
			}
			
			// LOSE CONDITIONS
			if(livesLeft == 0)																		// if no more lives remaining
			{
				mciSendString(_T("close all"), NULL, 0, NULL);										// close all sounds
				cleardevice();
				while(1) {

					loadEndMenu(0);																	// load lose menu
				}
				break;
			}
			
			// SPEED BOOST CONDITIONS
			if(playerPositionX + 70 > 960 && playerPositionY + 80 > 330 && 960 + 60 > playerPositionX && 330 + 65 > playerPositionY){	// player - speed boost collision
				playerStep = 7;	
			}
				
			// ITEM CONDITIONS	
			if(item1IsCollected == false){									// if item1IsCollected is false
				if(playerPositionX + 70 > item1PositionX && playerPositionY + 80 > item1PositionY && item1PositionX + 70 > playerPositionX && item1PositionY + 70 > playerPositionY) {
					if(item2 == false && item3 == false){					// if both item 2 and item 3 false, can take item 1 (can only bring 1 item) 
						item1 = true;										// set item1 to true
						item1PositionX = playerPositionX - 5;				// follow position of player in x coordinate
						item1PositionY = playerPositionY - 5;				// follow position of player in y coordinate
					}
				}
			}
			
			if(item2IsCollected == false){
				if(playerPositionX + 70 > item2PositionX && playerPositionY + 80 > item2PositionY && item2PositionX + 80 > playerPositionX && item2PositionY + 65 > playerPositionY) {
					if(item1 == false && item3 == false){
						item2 = true;
						item2PositionX = playerPositionX - 5;
						item2PositionY = playerPositionY - 5;
					}
				}
			}	
			
			
			if(item3IsCollected == false){
				if(playerPositionX + 70 > item3PositionX && playerPositionY + 80 > item3PositionY && item3PositionX + 75 > playerPositionX && item3PositionY + 75 > playerPositionY) {
					if(item1 == false && item2 == false){
						item3 = true;
						item3PositionX = playerPositionX - 5;
						item3PositionY = playerPositionY - 5;
					}
				}
			}
			
			// DROP CONDITIONS
			if(item1 == true){												// if item1 true, if in drop position
				if(playerPositionX + 70 > dropPositionX && playerPositionY + 80 > dropPositionY && dropPositionX + 225 > playerPositionX && dropPositionY + 55 > playerPositionY){
					item1IsCollected = true;								// set item1IsCollected to true
					item1PositionX = 1060;									// put item1 position x to drop position
					item1PositionY = 480;									// put item1 position y to drop position
					item1 = false;											// set item1 to false to take other item
					itemCounter++;
				}
			}
			if(item2 == true){
				if(playerPositionX + 70 > dropPositionX && playerPositionY + 80 > dropPositionY && dropPositionX + 225 > playerPositionX && dropPositionY + 55 > playerPositionY){
					item2IsCollected = true;	
					item2PositionX = 1110;
					item2PositionY = 480;
					item2 = false;
					itemCounter++;
				}
			}
			if(item3 == true){
			
				if(playerPositionX + 70 > dropPositionX && playerPositionY + 80 > dropPositionY && dropPositionX + 225 > playerPositionX && dropPositionY + 55 > playerPositionY){
					item3IsCollected = true;	
					item3PositionX = 1180;
					item3PositionY = 470;
					item3 = false;
					itemCounter++;
				}
			}
			
			// WIN CONDITION
			if(itemCounter == 3){															// if all items have been collected
				mciSendString(_T("close all"), NULL, 0, NULL);
				cleardevice();
				loadDialogue(5);
				cleardevice();
				while(1) {

					loadEndMenu(1);
				}
				break;
			}
			
			// LEVEL HELP CONDITIONS
			if(playerPositionX + 50 > 5 && playerPositionY + 70 > 130 && 5 + 15 > playerPositionX && 130 + 135 > playerPositionY){ //player - level help collison
				settextstyle(24, 0, _T("Consolas"));
				outtextxy(80, 180, _T("Move each item to the circle. Avoid the boss and the laser"));	
			}
			
			// PLAYER INPUT CONDITIONS
			if (input == 's' || input == 'S') {                          	// if the user press 's' / 'S'            
				if(playerPositionY + playerStep < 650) {					// if the player position after moving is still inside the window,	
					playerPositionY += playerStep;							// increment player position in y-index by "playerStep" amount 
												
					//BOSS MOVEMENT
					if(playerPositionX < bossX-bossStep) {					// if the player is on the left of the boss (x-index)
						bossX -= bossStep;									// move the boss to the left by "bossStep" amount
						isFacingLeft = true;
					}
					else if(playerPositionX > bossX+bossStep) {
						bossX += bossStep;
						isFacingLeft = false;
					}
					else {
						if(playerPositionY < bossY-bossStep) {				// if the player is on the top of the boss (y-index)
							bossY -= bossStep;								// move the boss to the top by "bossStep" amount
						}
						else if(playerPositionY > bossY-bossStep) {
							bossY += bossStep;
						}
					}
				
					playerWalkLevel4(input, playerPositionX, playerPositionY, playerMovementCount, coinCounter, livesLeft, movement, item1PositionX, item1PositionY, item2PositionX, item2PositionY, item3PositionX, item3PositionY, itemCounter, bossX, bossY, isFacingLeft);	
					if(hitByLaser == true) {						
						outtextxy(750, 600, _T("You got hit by the laser! -1 life."));
						Sleep(2000);
						playerPositionX = 300;
						playerPositionY = 90;
						hitByLaser = false;	
						item1 = false;
						item2 = false;
						item3 = false;
						mciSendString(_T("close dead"), NULL, 0, NULL);						
					}	
				}
			}
			else if (input == 'w' || input == 'W') {
				if(playerPositionY - playerStep >= -20) {
					playerPositionY -= playerStep;
					
					//BOSS MOVEMENT
					if(playerPositionX < bossX-bossStep) {
						bossX -= bossStep;
						isFacingLeft = true;
					}
					else if(playerPositionX > bossX+bossStep) {
						bossX += bossStep;
						isFacingLeft = false;
					}
					else {
						if(playerPositionY < bossY-bossStep) {
							bossY -= bossStep;
						}
						else if(playerPositionY > bossY-bossStep) {
							bossY += bossStep;
						}
					}
				
					playerWalkLevel4(input, playerPositionX, playerPositionY, playerMovementCount, coinCounter, livesLeft, movement, item1PositionX, item1PositionY, item2PositionX, item2PositionY, item3PositionX, item3PositionY, itemCounter, bossX, bossY, isFacingLeft);
					if(hitByLaser == true) {					
						outtextxy(750, 600, _T("You got hit by the laser! -1 life."));
						Sleep(2000);
						playerPositionX = 300;
						playerPositionY = 90;
						hitByLaser = false;	
						playerPositionX = 300;
						playerPositionY = 90;
						hitByLaser = false;	
						item1 = false;
						item2 = false;
						item3 = false;
						mciSendString(_T("close dead"), NULL, 0, NULL);									
					}		
				}
			}
			else if (input == 'a' || input == 'A') {	
				if(playerPositionX - playerStep >= - 25) {
					playerPositionX -= playerStep;
					
					//BOSS MOVEMENT
					if(playerPositionX < bossX-bossStep) {
						bossX -= bossStep;
						isFacingLeft = true;
					}
					else if(playerPositionX > bossX+bossStep) {
						bossX += bossStep;
						isFacingLeft = false;
					}
					else {
						if(playerPositionY < bossY-bossStep) {
							bossY -= bossStep;
						}
						else if(playerPositionY > bossY-bossStep) {
							bossY += bossStep;
						}
					}
				
					playerWalkLevel4(input, playerPositionX, playerPositionY, playerMovementCount, coinCounter, livesLeft, movement, item1PositionX, item1PositionY, item2PositionX, item2PositionY, item3PositionX, item3PositionY, itemCounter, bossX, bossY, isFacingLeft);	
					movement = false;
					if(hitByLaser == true) {	
						outtextxy(750, 600, _T("You got hit by the laser! -1 life."));
						Sleep(2000);				
						playerPositionX = 300;
						playerPositionY = 90;
						hitByLaser = false;		
						playerPositionX = 300;
						playerPositionY = 90;
						hitByLaser = false;	
						item1 = false;
						item2 = false;
						item3 = false;
						mciSendString(_T("close dead"), NULL, 0, NULL);							
					}	
				}
			}
			
			else if (input == 'd' || input == 'D') {
				if(playerPositionX + playerStep < 1220) {
					playerPositionX += playerStep;
					
					//BOSS MOVEMENT
					if(playerPositionX < bossX-bossStep) {
						bossX -= bossStep;
						isFacingLeft = true;
					}
					else if(playerPositionX > bossX+bossStep) {
						bossX += bossStep;
						isFacingLeft = false;
					}
					else {
						if(playerPositionY < bossY-bossStep) {
							bossY -= bossStep;
						}
						else if(playerPositionY > bossY-bossStep) {
							bossY += bossStep;
						}
					}
				
					playerWalkLevel4(input, playerPositionX, playerPositionY, playerMovementCount, coinCounter, livesLeft, movement, item1PositionX, item1PositionY, item2PositionX, item2PositionY, item3PositionX, item3PositionY, itemCounter, bossX, bossY, isFacingLeft);	
					movement = true;
					if(hitByLaser == true) {
						outtextxy(750, 600, _T("You got hit by the laser! -1 life."));
						Sleep(2000);							
						playerPositionX = 300;
						playerPositionY = 90;
						hitByLaser = false;		
						playerPositionX = 300;
						playerPositionY = 90;
						hitByLaser = false;	
						item1 = false;
						item2 = false;
						item3 = false;
						mciSendString(_T("close dead"), NULL, 0, NULL);							
					}	
				}
			}

			else if(input == VK_ESCAPE){
				mciSendString(_T("pause background3"), NULL, 0, NULL);	
				bool isPausing = true;
				while(1){
				isPausing = pause();
					if(isPausing == false){
						mciSendString(_T("resume background3"), NULL, 0, NULL);	
						playerWalkLevel4(input, playerPositionX, playerPositionY, playerMovementCount, coinCounter, livesLeft, movement, item1PositionX, item1PositionY, item2PositionX, item2PositionY, item3PositionX, item3PositionY, itemCounter, bossX, bossY, isFacingLeft);	
						break;
					}
				}
			}
	
		
			
			// BOSS HIT CONDITION
			if(playerPositionX + 70 > bossX && playerPositionY + 80 > bossY && bossX + 70 > playerPositionX && bossY + 80 > playerPositionY) { //player - boss collision
				mciSendString(_T("open resources/sfx/dead.wav alias dead"), NULL, 0, NULL);	
				mciSendString(_T("play dead"), NULL, 0, NULL);
				outtextxy(750, 600, _T("You got caught by the boss! -1 life."));
				Sleep(2000);		
				livesLeft--;
				playerPositionX = 300; 											
				playerPositionY = 90;
				playerPositionX = 300;
				playerPositionY = 90;
				hitByLaser = false;	
				item1 = false;
				item2 = false;
				item3 = false;
				bossX = 1100;
				bossY = 450; 	
				mciSendString(_T("close dead"), NULL, 0, NULL);
			}	
		}
	}
	_getch();
}