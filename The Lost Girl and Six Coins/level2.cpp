#include "header.h"
#include "functions.h"
#include "level3.h"

void lvl2_resetPlayerPosition() { 												// this function is for reseting player position to the middle left of the screen
	IMAGE src;
	loadimage(&src, _T("resources/image/char_left2.png")); 						// load character image char_left2 to IMAGE variable "src"
	transparentImage(NULL, 20, 350, &src, 0xffc4c4);							// load IMAGE variable "src" with transparent background to 20, 350
}

void loadLevel2(int livesLeft, int coinCounter) {
	
	// OPEN & PLAY MUSIC RESOURCES
	mciSendString(_T("open resources/sfx/background2.wav alias background2"), NULL, 0, NULL);	
	mciSendString(_T("play background2"), NULL, 0, NULL);
	
	// LOAD DIALOGUE
	loadDialogue(2);
	
	// LOAD TUTORIAL
	loadLevelTutorial(2);
	
	// INITIALIZE LEVEL
	loadimage(NULL, _T("resources/image/level2_background.jpg"));   			// load background 2 image
	loadLivesCounter(livesLeft);												// load lives counter based on the remaining lives from level 1
	
	// COINS VARIABLES															
	int coin1PosX = 1200;														
	int coin1PosY = 640;		                                                
	int coin2PosX = 50;		
	int coin2PosY = 100;	
	bool coin1_isCollected = false;          									
	bool coin2_isCollected = false;      
	loadCoin(coin1PosX, coin1PosY, coin1_isCollected);							// load coin1 image with the predefined variables
	loadCoin(coin2PosX, coin2PosY, coin2_isCollected);	              			// load coin2 image with the predefined variables
	loadCoinCounter(coinCounter);												// load coin counter based on the coins collected in level 1
	
	// PLAYER POSITION VARIABLES
	int playerPositionX = 20; 													// current player position in x-index
	int playerPositionY = 350; 													// current player position in y-index
	int playerMovementCount = 0; 												// number of times the player has moved	
	bool movement = false;														// movement false = player facing left
	int move = 5;																// distance traveled (in pixel) for each player movement	
	lvl2_resetPlayerPosition(); 												// load player in the starting position
	
	// TELEPORT POSITION VARIABLES
	int teleport1PosX = 585;
	int teleport1PosY = 10;
	
	// BACKGROUND FILE NAME
	char backgroundName[50] = "resources/image/level2_background.jpg";			
	
	// ROOM VARIABLES															
	bool room1 = false;
	bool room2 = true;
	bool room3 = false;
	bool room4 = false;
	bool room5 = false;
	bool room6 = false;
	bool room7 = false;
	bool room8 = false;
	bool room9 = false;
	bool room10 = false;
	
	// SPEED BOOST VARIABLE
	bool speedboost = false;													

	// HOLE COUNTER VARIABLE
	int holeCounter = 0;

	while (1) {                                                                 
																				
		if (_kbhit()) { 														// check for keyboard input
			char input = _getch();												// store keyboard input in variable "input"
			playerMovementCount++;												// increment playerMovementCount
			
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
			
			// COIN CONDITIONS
			if(playerPositionX + 70 > coin1PosX && playerPositionY + 80 > coin1PosY && coin1PosX + 30 > playerPositionX && coin1PosY + 35 > playerPositionY) { // player - coin1 collision
				if(coin1_isCollected == false){
					mciSendString(_T("open resources/sfx/coin3.wav alias coin3"), NULL, 0, NULL);	
					mciSendString(_T("play coin3"), NULL, 0, NULL);
					coinCounter++;	
				 }
				 coin1_isCollected = true;
			}
			
			if(playerPositionX + 70 > coin2PosX && playerPositionY + 80 > coin2PosY && coin2PosX + 30 > playerPositionX && coin2PosY + 35 > playerPositionY) { // player - coin2 collision
				if(coin2_isCollected == false){
					mciSendString(_T("open resources/sfx/coin4.wav alias coin4"), NULL, 0, NULL);	
					mciSendString(_T("play coin4"), NULL, 0, NULL);
				 	coinCounter++;
				 }
				 coin2_isCollected = true;
			}
			
			// TELEPORT CONDITIONS
			if(playerPositionX + 70 > teleport1PosX && playerPositionY + 80 > teleport1PosY && teleport1PosX + 30 > playerPositionX && teleport1PosY + 60 > playerPositionY) { // player - teleport collision
				if(coinCounter == 4){										// all coins have been collected, the player can proceed to the next level
					mciSendString(_T("close all"), NULL, 0, NULL);
					loadLevel3(livesLeft, coinCounter);
					break;
				}
				else if(coinCounter == 2){									// no coin has been collected
					outtextxy(660, 47, _T("Remaining coin: 2"));
				}
				else if(coinCounter == 3){									// only one coin has been collected
				outtextxy(660, 47, _T("Remaining coin: 1"));	
			}
		}
			
			// ROOM CONDITIONS (ROOM COLUMNS) (NOT BASED ON THE PICTURE)
			
			// ROOM 2
			if(playerPositionX + 20 > 70 && playerPositionY + 80 > 40 && 70 + 100 > playerPositionX && 40 + 65 > playerPositionY) {				// if player move toward this hole, teleport the player into the new x and y position
				playerPositionX = 455;																											
				playerPositionY = 330;
				room1 = true;																													// this condition makes the player can only move into certain position in different rooms
				room2 = false;
				holeCounter++;
				
			}
			if(playerPositionX + 20 > 70 && playerPositionY + 80 > 650 && 70 + 100 > playerPositionX && 650 + 65 > playerPositionY) {
				playerPositionX = 920;
				playerPositionY = 330;
				room1 = false;
				room2 = false;
				room3 = true;
				holeCounter++;
			}
		
			// ROOM 1
			if(playerPositionX + 20 > 400 && playerPositionY + 80 > 40 && 400 + 100 > playerPositionX && 40 + 65 > playerPositionY) {
				playerPositionX = 450;
				playerPositionY = 330;
				room1 = false;
				room2 = false;
				room3 = false;
				room4 = true;
				holeCounter++;
			}
			if(playerPositionX + 20 > 400 && playerPositionY + 80 > 650 && 400 + 100 > playerPositionX && 650 + 65 > playerPositionY) {
				playerPositionX = 290;
				playerPositionY = 330;
				room1 = false;
				room2 = false;
				room3 = false;
				room4 = false;
				room5 = true;
				holeCounter++;
			}
			
			// ROOM 3
			if(playerPositionX + 20 > 850 && playerPositionY + 80 > 40 && 850 + 100 > playerPositionX && 40 + 65 > playerPositionY) {
				playerPositionX = 920;
				playerPositionY = 330;
				room1 = false;
				room2 = false;
				room3 = false;
				room4 = false;
				room5 = false;
				room6 = true;
				holeCounter++;
			}
			if(playerPositionX + 20 > 850 && playerPositionY + 80 > 650 && 850 + 100 > playerPositionX && 650 + 65 > playerPositionY) {
				playerPositionX = 1090;
				playerPositionY = 330;
				room1 = false;
				room2 = false;
				room3 = false;
				room4 = false;
				room5 = false;
				room6 = false;
				room7 = true;
				holeCounter++;
			}
			
			// ROOM 4
			if(playerPositionX + 20 > 230 && playerPositionY + 80 > 40 && 230 + 100 > playerPositionX && 40 + 65 > playerPositionY) {
				playerPositionX = 100;
				playerPositionY = 330;
				room1 = false;
				room2 = true;
				room3 = false;
				room4 = false;
				room5 = false;
				room6 = false;
				room7 = false;
				room8 = false;
				holeCounter++;
			}
			if(playerPositionX + 20 > 230 && playerPositionY + 80 > 650 && 230 + 100 > playerPositionX && 650 + 65 > playerPositionY) {
				playerPositionX = 750;
				playerPositionY = 330;
				room1 = false;
				room2 = false;
				room3 = false;
				room4 = false;
				room5 = false;
				room6 = false;
				room7 = false;
				room8 = false;
				room9 = true;
				holeCounter++;
			}
			
			// ROOM 5
			if(playerPositionX + 20 > 1030 && playerPositionY + 80 > 40 && 1030 + 100 > playerPositionX && 40 + 65 > playerPositionY) {
				playerPositionX = 100;
				playerPositionY = 330;
				room1 = false;
				room2 = true;
				room3 = false;
				room4 = false;
				room5 = false;
				room6 = false;
				room7 = false;
				room8 = false;
				room9 = false;
				holeCounter++;
			}
			if(playerPositionX + 20 > 1030 && playerPositionY + 80 > 650 && 1030 + 100 > playerPositionX && 650 + 65 > playerPositionY){
				playerPositionX = 920;
				playerPositionY = 330;
				room1 = false;
				room2 = false;
				room3 = true;
				room4 = false;
				room5 = false;
				room6 = false;
				room7 = false;
				room8 = false;
				room9 = false;
				holeCounter++;
			}
			
			// ROOM 6
			if(playerPositionX + 20 > 700 && playerPositionY + 80 > 40 && 700 + 100 > playerPositionX && 40 + 65 > playerPositionY) {
				playerPositionX = 600;
				playerPositionY = 400;
				room1 = false;
				room2 = false;
				room3 = false;
				room4 = false;
				room5 = false;
				room6 = false;
				room7 = false;
				room8 = false;
				room9 = false;
				room10 = true;
				holeCounter++;
			}
			if(playerPositionX + 20 > 700 && playerPositionY + 80 > 650 && 700 + 100 > playerPositionX && 650 + 65 > playerPositionY){
				playerPositionX = 100;
				playerPositionY = 330;
				room1 = false;
				room2 = true;
				room3 = false;
				room4 = false;
				room5 = false;
				room6 = false;
				room7 = false;
				room8 = false;
				room9 = false;
				room10 = false;
				holeCounter++;
			}
			
			if(playerPositionX + 20 > 600 && playerPositionY + 80 > 600 && 600 + 100 > playerPositionX && 600 + 65 > playerPositionY){
				playerPositionX = 100;
				playerPositionY = 330;
				room1 = false;
				room2 = true;
				room3 = false;
				room4 = false;
				room5 = false;
				room6 = false;
				room7 = false;
				room8 = false;
				room9 = false;
				room10 = false;
				holeCounter++;
			}
			
			if(holeCounter == 15)														// if the player has jumped 15 times, -1 live, and back to the starting position
			{
				mciSendString(_T("open resources/sfx/dead.wav alias dead"), NULL, 0, NULL);	
				mciSendString(_T("play dead"), NULL, 0, NULL);
				livesLeft--;
				
				settextstyle(24, 0, _T("Consolas"));
				outtextxy(400, 360, _T("You've jumped into 15 holes! -1 life."));
				Sleep(2000);
				mciSendString(_T("close dead"), NULL, 0, NULL);
				playerPositionX = 20; 											
				playerPositionY = 350;
				holeCounter = 0;
				room1 = false;															// reset all room variables
				room2 = true;
				room3 = false;
				room4 = false;
				room5 = false;
				room6 = false;
				room7 = false;
				room8 = false;
				room9 = false;
				room10 = false;
				
			}
			
			// SPEED BOOST CONDITIONS
			if(playerPositionX + 70 > 1200 && playerPositionY + 80 > 285 && 1200 + 60 > playerPositionX && 285 + 65 > playerPositionY){ 	// player - speedboost collision
				move = 7;
			}
			
			// LEVEL HELP CONDITIONS
			if(playerPositionX + 50 > 20 && playerPositionY + 70 > 250 && 20 + 60 > playerPositionX && 250 + 60 > playerPositionY){			// player - level help collision
				settextstyle(24, 0, _T("Consolas"));
				outtextxy(100, 285, _T("Use the hole to move between rows. Collect all coins and proceed under 15 moves!"));
				outtextxy(100, 310, _T("Tip: Speedboost can increase your speed"));	
			}
			
			// PLAYER INPUT CONDITIONS
			if (input == 's' || input == 'S') {               			// if the user press 's' / 'S'                       
				if(playerPositionY + move < 650) {						// if the player position after moving is still inside the window,
					playerPositionY += move;							// increment player position in y-index by "move" amount 
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	 // run the playerWalk() function		
				}
			}
			
			else if (input == 'w' || input == 'W') {
				if(playerPositionY - move >= -20) {
					playerPositionY -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	
				}
			}
			
			else if (input == 'a' || input == 'A') { 	
				if(room2 == true){																					
					if(playerPositionX - move >= 0) {                                                        // if player is in room 2 (the left-most room), the player can only move to the left when x position is >= 0
					playerPositionX -= move;																
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName); 	// call playerwalk in function.cpp
					movement = false;
					}
				}	
				if(room1 == true){
					if(playerPositionX - move >= 410){
					playerPositionX -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;
					}
				}
				if(room3 == true){
					if(playerPositionX - move >= 880){
					playerPositionX -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;
					}
				}
				if(room4 == true){
					if(playerPositionX - move >= 410){
					playerPositionX -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;
					}
				}
				if(room5 == true){
					if(playerPositionX - move >= 245){
					playerPositionX -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;
					}
				}
				if(room6 == true){
					if(playerPositionX - move >= 880){
					playerPositionX -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;
					}
				}
				if(room7 == true){
					if(playerPositionX - move >= 1045){
					playerPositionX -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;
					}
				}
				if(room8 == true){
					if(playerPositionX - move >= 245){
					playerPositionX -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;	
					}
				}
				if(room9 == true){
					if(playerPositionX - move >= 705){
					playerPositionX -= move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;		
					}
				}
			}
			
			else if (input == 'd' || input == 'D') {
				if(room2 == true){																		// if player is in room 2 (the left-most room), player can only move to the right when x position is < 165
					if(playerPositionX + move < 165){															
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = true;
					}
				}
				if(room1 == true){
					if(playerPositionX + move < 495){
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = true;
					}	
				}
				if(room3 == true){
					if(playerPositionX + move < 960){
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = true;
					}
				}
				if(room4 == true){
					if(playerPositionX + move < 495){
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = true;
					}	
				}
				if(room5 == true){
					if(playerPositionX + move < 330){
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = true;
					}
				}
				if(room6 == true){
					if(playerPositionX + move < 960){
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = true;	
					}
				}
				if(room7 == true){
					if(playerPositionX + move < 1200){
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = true;
					}
				}
				if(room8 == true){
					if(playerPositionX + move < 330){
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = true;
					}
				}
				if(room9 == true){
					if(playerPositionX + move < 795){
					playerPositionX += move;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = true;
					}
				}
			}
						
			else if(input == VK_ESCAPE){											// if the user press 'ESC'
				mciSendString(_T("pause background2"), NULL, 0, NULL);
				bool isPausing = true;
				while(1){
				isPausing = pause();												// get the return value from the function
					if(isPausing == false){											// if is pausing is now false, resume the game
						mciSendString(_T("resume background2"), NULL, 0, NULL);
						playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	
						break;
					}
				}
			} 
		}
	}
	_getch();
}
