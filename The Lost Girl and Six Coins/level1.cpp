#include "header.h"
#include "functions.h"
#include "level2.h"

void lvl1_resetPlayerPosition() { 										// this function is for reseting player position to the middle bottom of the screen
	IMAGE src;
	loadimage(&src, _T("resources/image/char_left2.png")); 				// load character image char_left2 to IMAGE variable "src"
	transparentImage(NULL, 580, 630, &src, 0xffc4c4);					// load IMAGE variable "src" with transparent background to 580, 630
}

void loadLevel1() {
	
	// OPEN & PLAY MUSIC RESOURCES
	mciSendString(_T("open resources/sfx/background1.wav alias background1"), NULL, 0, NULL);	
	mciSendString(_T("play background1"), NULL, 0, NULL);

	// LOAD DIALOGUE
	loadDialogue(1);
	
	// LOAD TUTORIAL
	loadLevelTutorial(1);
	
	// INITIALIZE LEVEL
	loadimage(NULL, _T("resources/image/level1_background.jpg"));   	// load level 1 background
	int livesLeft = 5;													
	loadLivesCounter(livesLeft);										// player starts with 5 lives
	
	// COINS VARIABLES
	int coin1PosX = 20;
	int coin1PosY = 440;
	int coin2PosX = 370;
	int coin2PosY = 250;
	bool coin1_isCollected = false;          
	bool coin2_isCollected = false;      
	loadCoin(coin1PosX, coin1PosY, coin1_isCollected);					// load coin1 image with the predefined variables
	loadCoin(coin2PosX, coin2PosY, coin2_isCollected);	                // load coin2 image with the predefined variables
	int coinCounter = 0;
	loadCoinCounter(coinCounter);										// player starts with 0 coin collected
	
	// PLAYER POSITION VARIABLES
	int playerPositionX = 580; 															// current player position in x-index
	int playerPositionY = 630; 															// current player position in y-index
	int playerMovementCount = 0; 														// number of times the player has moved		
	bool movement = false;																// movement false = player facing left
	int move = 5;																		// distance traveled (in pixel) for each player movement	
	lvl1_resetPlayerPosition(); 														// load player in the starting position

	// TELEPORT POSITION VARIABLES
	int teleport1PosX = 585;
	int teleport1PosY = 10;
	
	// LASER VARIABLES
	time_t seconds;
	int laser1posX = 0;
	int laser1posY = 500;
	int laser2posX = 0;
	int laser2posY = 200;
	int laser3posX = 330;
	int laser3posY = 0;
	int laser4posX = 430;
	int laser4posY = 0;
	bool showLaserHorizontal = false;
	bool showLaserVertical = false;
	bool hitByLaser = false;
	
	// BACKGROUND FILE NAME
	char backgroundName[50] = "resources/image/level1_background.jpg";

	// LOAD GAME TUTORIAL
	loadLevelTutorial(0);
	playerWalk('w', playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);

	while (1) {   
		
		// LOAD LASERS
		seconds = time(NULL); 											// update second stored for every while loop	
		
		if(seconds % 3 == 0) { 											// load horizontal laser for every 3 seconds
			loadHorizontalLaser(laser1posX,laser1posY);					
			loadHorizontalLaser(laser2posX,laser2posY);
			showLaserHorizontal = true;
		}
		else showLaserHorizontal = false;
			
		if(seconds % 4 == 0) { 											// load vertical laser for every 4 seconds
			loadVerticalLaser(laser3posX, laser3posY);
			loadVerticalLaser(laser4posX, laser4posY);
			showLaserVertical = true;
		}
		else showLaserVertical = false;	            
	                  
					               		                     	  				
		if (_kbhit()) { 												// check for keyboard input
			char input = _getch();										// store keyboard input in variable "input"
			playerMovementCount++;										// increment playerMovementCount
			
			// LASER CONDITIONS
			if((playerPositionY + 70 > laser1posY && laser1posY +  18 > playerPositionY) || (playerPositionY + 70 > laser2posY && laser2posY +  18 > playerPositionY)) { // player - horizontal laser collison
				if(showLaserHorizontal == true) {
					mciSendString(_T("open resources/sfx/dead.wav alias dead"), NULL, 0, NULL);	
					mciSendString(_T("play dead"), NULL, 0, NULL);		// play dead sound effect
					livesLeft--;										// decrement player lives
					hitByLaser = true;	
				}
			}
			
			if((playerPositionX + 70 > laser3posX && laser3posX +  18 > playerPositionX) || (playerPositionX + 70 > laser4posX && laser4posX +  18 > playerPositionX)) { //player - vertical laser collison
				if(showLaserVertical == true) {
					mciSendString(_T("open resources/sfx/dead.wav alias dead"), NULL, 0, NULL);	
					mciSendString(_T("play dead"), NULL, 0, NULL);		// play dead sound effect
					livesLeft--;										// decrement player lives
					hitByLaser = true;
				}
			}
			
			// LOSE CONDITIONS
			if(livesLeft == 0) {																	// if no more lives remaining				
				mciSendString(_T("close all"), NULL, 0, NULL);								
				cleardevice();
				while(1) {

					loadEndMenu(0);																	// load lose menu
				}
				break;
			}
			
			// COIN CONDITIONS
			if(playerPositionX + 70 > coin1PosX && playerPositionY + 80 > coin1PosY && coin1PosX + 30 > playerPositionX && coin1PosY + 35 > playerPositionY) { // player - coin1 collision
				if(coin1_isCollected == false) {
					mciSendString(_T("open resources/sfx/coin1.wav alias coin1"), NULL, 0, NULL);	
					mciSendString(_T("play coin1"), NULL, 0, NULL);
					coinCounter++;	
				 }
				 coin1_isCollected = true;
			}
			if(playerPositionX + 70 > coin2PosX && playerPositionY + 80 > coin2PosY && coin2PosX + 30 > playerPositionX && coin2PosY + 35 > playerPositionY) { // player - coin2 collision
				if(coin2_isCollected == false) {
					mciSendString(_T("open resources/sfx/coin2.wav alias coin2"), NULL, 0, NULL);	
					mciSendString(_T("play coin2"), NULL, 0, NULL);
					coinCounter++;
				 }
				 coin2_isCollected = true;
			}
			
			// TELEPORT CONDITIONS
			if(playerPositionX + 70 > teleport1PosX && playerPositionY + 80 > teleport1PosY && teleport1PosX + 30 > playerPositionX && teleport1PosY + 60 > playerPositionY) { // player - teleport collision
				if(coinCounter == 2){									// all coins have been collected, the player can proceed to the next level
					mciSendString(_T("close all"), NULL, 0, NULL);
					loadLevel2(livesLeft, coinCounter);
					break;
				}
				else if(coinCounter == 0){								// no coin has been collected
					outtextxy(660, 47, _T("Remaining coin: 2"));		
				}
				else if(coinCounter == 1){								// only one coin has been collected
					outtextxy(660, 47, _T("Remaining coin: 1"));	
				}
			}
				
			// LEVEL HELP CONDITIONS
			if(playerPositionX + 50 > 1200 && playerPositionY + 70 > 600 && 1200 + 70 > playerPositionX && 600 + 100 > playerPositionY) {	// player - level help collision
				settextstyle(24, 0, _T("Consolas"));	
				outtextxy(530, 610, _T("Collect all coins, avoid the lasers, and jump into the portal!"));
				outtextxy(530, 635, _T("Tip: Speedboost can increase your speed"));
			}
			
			// SPEEDBOOST CONDITIONS
			if(playerPositionX + 70 > 960 && playerPositionY + 80 > 330 && 960 + 60 > playerPositionX && 330 + 65 > playerPositionY) {		// player - speedboost collision	
				move = 7;	
			}
			
			// PLAYER INPUT CONDITIONS
			if (input == 's' || input == 'S') {                             // if the user press 's' / 'S'
				if(playerPositionY + move < 650) {							// if the player position after moving is still inside the window,
					playerPositionY += move;								// increment player position in y-index by "move" amount 
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	// run the playerWalk() function
					if(hitByLaser == true) {								// if player is hit by the laser
						outtextxy(750, 600, _T("You got hit by the laser! -1 life."));
						Sleep(2000);										// delay for 2 seconds
						playerPositionX = 580;								// reset player position to x = 580, and y = 590
						playerPositionY = 590;
						hitByLaser = false;									// reset hitByLaser to false
						mciSendString(_T("close dead"), NULL, 0, NULL);
					}				
				}
			}
			else if (input == 'w' || input == 'W') {
				if(playerPositionY - move >= -20) {
					playerPositionY -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	
					if(hitByLaser == true) {
						outtextxy(750, 600, _T("You got hit by the laser! -1 life."));
						Sleep(2000);
						playerPositionX = 580;
						playerPositionY = 590;
						hitByLaser = false;
						mciSendString(_T("close dead"), NULL, 0, NULL);
					}	
				}
			}
			else if (input == 'a' || input == 'A') {	
				if(playerPositionX - move >= - 25) {
					playerPositionX -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;
					if(hitByLaser == true) {
						outtextxy(750, 600, _T("You got hit by the laser! -1 life."));
						Sleep(2000);
						playerPositionX = 580;
						playerPositionY = 590;
						hitByLaser = false;
						mciSendString(_T("close dead"), NULL, 0, NULL);
					}
				}
			}
			
			else if (input == 'd' || input == 'D') {
				if(playerPositionX + move < 1220) {
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	
					movement = true;
					if(hitByLaser == true) {
						outtextxy(750, 600, _T("You got hit by the laser! -1 life."));
						Sleep(2000);
						playerPositionX = 580;
						playerPositionY = 590;
						hitByLaser = false;
						mciSendString(_T("close dead"), NULL, 0, NULL);
					}
				}
			}
			
			else if(input == VK_ESCAPE){										// if the user press 'ESC'
				mciSendString(_T("pause background1"), NULL, 0, NULL);			
				bool isPausing = true;											
				while(1){
				isPausing = pause();											// get the return value from the function
					if(isPausing == false){										// if is pausing is now false, resume the game
						mciSendString(_T("resume background1"), NULL, 0, NULL);
						playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	
						break;
					}	
				}
			}  
		}
	}
	_getch();
}
