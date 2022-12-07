#include "header.h"
#include "functions.h"
#include "level4.h"

void lvl3_resetPlayerPosition() { 								// this function is for reseting player position to the middle bottom of the screen
	IMAGE src;
	loadimage(&src, _T("resources/image/char_left2.png")); 		// load character image char_left2 to IMAGE variable "src"
	transparentImage(NULL, 580, 630, &src, 0xffc4c4);			// load IMAGE variable "src" with transparent background to 580, 630
}

void resetPuzzle() {											// this function is for resetting the puzzle (load all lamp_off images)
	IMAGE lamp_off;												// load lamp_off image
	loadimage(&lamp_off, _T("resources/image/lamp_off.jpg"));	
	
	transparentImage(NULL, 306, 296, &lamp_off, 0xffc4c4);		// load lamp_off image in position 1
	transparentImage(NULL, 447, 296, &lamp_off, 0xffc4c4);		// load lamp_off image in position 2
	transparentImage(NULL, 588, 296, &lamp_off, 0xffc4c4);		// load lamp_off image in position 3
	transparentImage(NULL, 729, 296, &lamp_off, 0xffc4c4);		// load lamp_off image in position 4
	transparentImage(NULL, 870, 296, &lamp_off, 0xffc4c4);		// load lamp_off image in position 5
}

bool loadPuzzleBox(int round) {												// take round argument, and output true/false depending on the user's input
	
	IMAGE puzzleBox;
	loadimage(&puzzleBox, _T("resources/image/level3_puzzlebox.jpg"));		// load puzzle box image
	transparentImage(NULL, 280, 207, &puzzleBox, 0xffc4c4);
	resetPuzzle();															// call the resetPuzzle() function	

	Sleep(1000);															// wait for one second
	outtextxy(500, 480, _T("Press any key to start the sequence"));			// output text
	_getch();	
	
	// PLAYER INPUT STORAGE VARIABLES
	char round1_input[10];
	char round2_input[10];
	
	if(round == 1) {																							// for round 1												
		mciSendString(_T("open resources/video/Round_1.avi type MPEGVideo alias round1"), NULL, 0, NULL);		
		mciSendString(_T("play round1"), NULL, 0, NULL);														// play round 1 puzzle video
		Sleep(7000);																							// wait for 7 seconds
		mciSendString(_T("close round1"), NULL, 0, NULL);														// close round 1 p
											
		InputBox(_T(round1_input), 10, _T("Enter Round 1 Sequence"));		// load input box and store the input in round1_input variable
		int round1_answer = atoi(round1_input);								// convert string to integer
	
		if(round1_answer == 15342) {										// check whether user's input is correct
			return true;													
		}
		else {
			return false;
		}	
	}
	
	if(round == 2) {																							// for round 2
													
		mciSendString(_T("open resources/video/Round_2.avi type MPEGVideo alias round2"), NULL, 0, NULL);
		mciSendString(_T("play round2"), NULL, 0, NULL);
		Sleep(7000);
		mciSendString(_T("close round2"), NULL, 0, NULL);	
							
		InputBox(_T(round2_input), 10, _T("Enter Round 2 Sequence"));	
		int round2_answer = atoi(round2_input);
	
		if(round2_answer == 54132) {
			return true;
		}
		else {
			return false;
		}	
	}
}

void loadLevel3(int livesLeft, int coinCounter) {
	
	// OPEN & PLAY MUSIC RESOURCES
	mciSendString(_T("open resources/sfx/background3.wav alias background3"), NULL, 0, NULL);	
	mciSendString(_T("play background3"), NULL, 0, NULL);
	
	// LOAD DIALOGUE
	loadDialogue(3);
	
	// LOAD TUTORIAL
	loadLevelTutorial(3);
	
	// INITIALIZE LEVEL
	loadimage(NULL, _T("resources/image/level3_background.jpg"));   		// load background 3 image
	loadLivesCounter(livesLeft);											// load lives counter based on the remaining lives from level 2
	
	// COINS VARIABLES	
	bool coin1_isCollected = false;          
	bool coin2_isCollected = false;                  
	loadCoinCounter(coinCounter);											// load coin counter based on the coins collected in level 2
	
	// PLAYER POSITION VARIABLES
	int playerPositionX = 580; 												// current player position in x-index
	int playerPositionY = 630; 												// current player position in y-index
	int playerMovementCount = 0; 											// number of times the player has moved
	bool movement = false;													// movement false = player facing left
	lvl3_resetPlayerPosition(); 											// load player in the starting position
	
	// TELEPORT POSITION VARIABLES
	int teleport1PosX = 585;
	int teleport1PosY = 10;
	
	// PUZZLE VARIABLES
	int keyPositionX = 550;
	int keyPositionY = 300;
	bool showPuzzleBox = false;
	bool puzzleCompleted = false;
	
	// BACKGROUND FILE NAME
	char backgroundName[50] = "resources/image/level3_background.jpg";

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
			
			// TELEPORT CONDITIONS
			if(playerPositionX + 70 > teleport1PosX && playerPositionY + 80 > teleport1PosY && teleport1PosX + 56 > playerPositionX && teleport1PosY + 88 > playerPositionY) { // player - teleport collision
				if(puzzleCompleted == true){									// if the puzzle has been completed, the player can proceed to the next level
					mciSendString(_T("close all"), NULL, 0, NULL);
					loadLevel4(livesLeft, coinCounter);
					break;
				}
				else {
					outtextxy(660, 47, _T("You need to complete the puzzle first!"));
				}
			}
			
			// LEVEL HELP CONDITIONS
			if(playerPositionX + 50 > 1250 && playerPositionY + 70 > 575 && 1250 + 15 > playerPositionX && 575 + 135 > playerPositionY){ //player - level help collison
				settextstyle(24, 0, _T("Consolas"));
				outtextxy(675, 610, _T("Finish the puzzle to collect the key and coins!"));	
			}
			
			// PLAYER INPUT CONDITIONS
			if (input == 's' || input == 'S') {									// if the user press 's' / 'S'  
				if(playerPositionY + 5 < 650) {									// if the player position after moving is still inside the window,
					playerPositionY += 5;										// increment player position in y-index by 5 pixel
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName); 	// run the playerWalk() function	
				}
			}
			
			else if (input == 'w' || input == 'W') {
				if(playerPositionY - 5 >= -20) {
					playerPositionY -= 5;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	
				}
			}
		
			else if (input == 'a' || input == 'A') {	
				if(playerPositionX -5 >= - 25) {
					playerPositionX -= 5;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);
					movement = false;
				}
			}
			
			else if (input == 'd' || input == 'D') {
				if(playerPositionX + 5 < 1220) {
					playerPositionX += 5;
					playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	
					movement = true;
				}
			}
			
			else if(input == VK_ESCAPE){												// if the user press 'ESC'
				mciSendString(_T("pause background3"), NULL, 0, NULL);
				bool isPausing = true;
				while(1){
				isPausing = pause();													// get the return value from the function
					if(isPausing == false){												// if is pausing is now false, resume the game
						mciSendString(_T("resume background3"), NULL, 0, NULL);
						playerWalk(input, playerPositionX, playerPositionY, playerMovementCount, coin1_isCollected, coinCounter, movement, coin2_isCollected, livesLeft, backgroundName);	
						break;
					}
				}
			} 
			
			// PUZZLE KEY CONDITIONS
			if(playerPositionX + 70 > keyPositionX && playerPositionY + 80 > keyPositionY && keyPositionX + 135 > playerPositionX && keyPositionY + 71 > playerPositionY) { // player - key collision
				if(showPuzzleBox == false && puzzleCompleted == false) {		// check if player is not currently doing the puzzle and the puzzle has not been completed
					bool output1 = loadPuzzleBox(1);							// run loadPuzzleBox function and pass round 1, store return value in output1
					showPuzzleBox = true;										// player is currently doing the puzzle
					
					if(output1 == true) {																			// player completed round 1
						outtextxy(500, 480, _T("Corret input! Time for the round 2! "));							// output text
						Sleep(2000);																				// wait for 2 seconds
						bool output2 = loadPuzzleBox(2);															// load loadPuzzleBox function for round 2
						
						if(output2 == true) {																		// player completed round 2
							puzzleCompleted = true;																	// puzzle is now completed and teleport is available
							mciSendString(_T("open resources/sfx/coin5-6.wav alias coin5-6"), NULL, 0, NULL);	
							mciSendString(_T("play coin5-6"), NULL, 0, NULL);
							coinCounter = 6;			  															// player get another 2 coins
							outtextxy(420, 480, _T("Corret input! You get another 2 coins, you can proceed! "));
							Sleep(2000);
						}
						
						else if(output2 == false) {																	// player failed round 2
							mciSendString(_T("open resources/sfx/dead.wav alias dead"), NULL, 0, NULL);	
							mciSendString(_T("play dead"), NULL, 0, NULL);
							outtextxy(450, 650, _T("Wrong sequence, -1 life! Press any key to restart"));			// output text
							livesLeft--;																			// -1 lives
							playerPositionX = 580; 																	// reset player position X to the initial starting position
							playerPositionY = 630; 																	// reset player position X to the initial starting position
							showPuzzleBox = false;																	// player is no longer doing the puzzle
							_getch();
							mciSendString(_T("close dead"), NULL, 0, NULL);
						}
					}
					
					else if(output1 == false) {																		// player failed round 1
						mciSendString(_T("open resources/sfx/dead.wav alias dead"), NULL, 0, NULL);	
						mciSendString(_T("play dead"), NULL, 0, NULL);
						outtextxy(450, 650, _T("Wrong sequence, -1 life! Press any key to restart"));				// output text
						livesLeft--;																				// -1 lives
						playerPositionX = 580; 																		// reset player position X to the initial starting position
						playerPositionY = 630; 																		// reset player position X to the initial starting position
						showPuzzleBox = false;																		// player is no longer doing the puzzle
						_getch();
						mciSendString(_T("close dead"), NULL, 0, NULL);
					}
				}
			}	 
		}
	}

	_getch();
}