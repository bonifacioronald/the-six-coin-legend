#include "header.h"
#include "level1.h"
#include "main.h"

void transparentImage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor) {	// this function is used to generate an image with transparent background
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

bool pause() {															// pause function
	
	ExMessage m;

	m = getmessage(EM_MOUSE | EM_KEY);									// get mouse click input
	
		IMAGE pause;
		loadimage(&pause, _T("resources/image/pause_menu.png")); 		// load pause menu image
		transparentImage(NULL, 0, 0, &pause, 0xffc4c4);
	
	switch(m.message)						
	{
		case WM_LBUTTONDOWN:
			
		if(m.x >= 475 && m.x <= 805 && m.y >= 285 && m.y <= 340)		// resume button coordinate
		{
			return false;												// the game is no longer pausing
		}
		if(m.x >= 475 && m.x <= 805 && m.y >= 360 && m.y <= 420)		// restart button coordinate
		{
			mciSendString(_T("close all"), NULL, 0, NULL);
			main();														// run main menu 
		}
		if(m.x >= 475 && m.x <= 805 && m.y >= 445 && m.y <= 500)		// exit button coordinate	
		{
			mciSendString(_T("close all"), NULL, 0, NULL);
			closegraph();												// close game window
		}
	}
}

void loadEndMenu(int winlose) {											// end menu function
	ExMessage mouse;

	mouse = getmessage(EM_MOUSE | EM_KEY);								// get mouse click input
	
	IMAGE endMenu;
	if(winlose == 0)
	{
		mciSendString(_T("open resources/sfx/lose.wav alias lose"), NULL, 0, NULL);		
		mciSendString(_T("play lose"), NULL, 0, NULL);					// play lose sound effect
		loadimage(NULL, _T("resources/image/lose_menu.jpg"));			// load lose menu
	}
	else if(winlose == 1)
	{
		mciSendString(_T("open resources/sfx/win.wav alias win"), NULL, 0, NULL);	
		mciSendString(_T("play win"), NULL, 0, NULL);					// play win sound effect
		loadimage(NULL, _T("resources/image/win_menu.jpg"));			// load win menu
	}
	
	switch(mouse.message)						
	{
		case WM_LBUTTONDOWN:
			
		if(mouse.x >= 838 && mouse.x <= 1197 && mouse.y >= 435 && mouse.y <= 523)		// main meny button coordinate
		{
			mciSendString(_T("close all"), NULL, 0, NULL);
			main();												
		}
		if(mouse.x >= 838 && mouse.x <= 1197 && mouse.y >= 569 && mouse.y <= 660)		// exit button coordinate	
		{
			mciSendString(_T("close all"), NULL, 0, NULL);
			closegraph();																// close game window
		}
	}
}


void loadCoin(int coinPosX, int coinPosY, bool coin_isCollected) {                      // function to load coin image
	IMAGE coinImage;
	if(coin_isCollected == false)														// check coin is not yet collected
	{
		loadimage(&coinImage, _T("resources/image/coin.png"));
		transparentImage(NULL, coinPosX, coinPosY, &coinImage, 0xffc4c4);
	}
}

void loadLivesCounter(int livesLeft){													// function to load the lives left counter
	IMAGE lives;
	if(livesLeft == 5)
	{
		loadimage(&lives, _T("resources/image/LivesLeft_5.png"));
		transparentImage(NULL, 20, 20, &lives, 0xffc4c4);
	}
	else if(livesLeft == 4)
	{
		loadimage(&lives, _T("resources/image/LivesLeft_4.png"));
		transparentImage(NULL, 20, 20, &lives, 0xffc4c4);
	}
	else if(livesLeft == 3)
	{
		loadimage(&lives, _T("resources/image/LivesLeft_3.png"));
		transparentImage(NULL, 20, 20, &lives, 0xffc4c4);
	}
	else if(livesLeft == 2)
	{
		loadimage(&lives, _T("resources/image/LivesLeft_2.png"));
		transparentImage(NULL, 20, 20, &lives, 0xffc4c4);
	}
	else if(livesLeft == 1)
	{
		loadimage(&lives, _T("resources/image/LivesLeft_1.png"));
		transparentImage(NULL, 20, 20, &lives, 0xffc4c4);
	}
}
	
void loadCoinCounter(int counter){														// function to load coin counter
	IMAGE lives;
	IMAGE coinCounter;
	loadimage(&coinCounter, _T("resources/image/coin_collected.png"));  
	transparentImage(NULL, 1030, 20, &coinCounter, 0xffc4c4);
	
	settextstyle(20, 0, _T("Consolas"));
	if(counter  == 0)
	{
		outtextxy(1090, 37, _T("Coins collected: 0"));	
	}
	else if(counter == 1)
	{
		outtextxy(1090, 37, _T("Coins collected: 1"));	
	}
	else if(counter == 2)
	{
		outtextxy(1090, 37, _T("Coins collected: 2"));	
	}
	else if(counter == 3)
	{
		outtextxy(1090, 37, _T("Coins collected: 3"));	
	}
	else if(counter == 4)
	{
		outtextxy(1090, 37, _T("Coins collected: 4"));	
	}
	else if(counter == 5)
	{
		outtextxy(1090, 37, _T("Coins collected: 5"));	
	}
	else if(counter == 6)
	{
		outtextxy(1090, 37, _T("Coins collected: 6"));	
	}
}

void loadHorizontalLaser(int x, int y) {												// function to load horizontal laser
	IMAGE laser;
	loadimage(&laser, _T("resources/image/laserHorizontal.png"));
	putimage(x,y, &laser);	
}

void loadVerticalLaser(int x, int y) {													// function to load vertical laser
	IMAGE laser;
	loadimage(&laser, _T("resources/image/laserVertical.png"));
	putimage(x,y, &laser);	
}

void loadLevelTutorial(int level) {														// function to load level tutorial cutscenes
	
	if(level == 0) {
		loadimage(NULL, _T("resources/tutorial/main-1.jpg"));
		_getch();
		loadimage(NULL, _T("resources/tutorial/main-2.jpg"));
		_getch();
		loadimage(NULL, _T("resources/tutorial/main-3.jpg"));
		_getch();
		cleardevice();
	}
	
	if(level == 1) {
		loadimage(NULL, _T("resources/tutorial/level1-1.jpg"));
		_getch();
		loadimage(NULL, _T("resources/tutorial/level1-2.jpg"));
		_getch();
		cleardevice();
	}
	
	else if(level == 2) {
		loadimage(NULL, _T("resources/tutorial/level2-1.jpg"));
		_getch();
		loadimage(NULL, _T("resources/tutorial/level2-2.jpg"));
		_getch();
		cleardevice();
	}
	
	else if(level == 3) {
		loadimage(NULL, _T("resources/tutorial/level3-1.jpg"));
		_getch();
		loadimage(NULL, _T("resources/tutorial/level3-2.jpg"));
		_getch();
		cleardevice();
	}
	
	else if(level == 4) {
		loadimage(NULL, _T("resources/tutorial/level4-1.jpg"));
		_getch();
		loadimage(NULL, _T("resources/tutorial/level4-2.jpg"));
		_getch();
		cleardevice();
	}
}

void loadDialogue(int level) {															// function to load dialogue cutscenes
	
	if(level == 1) {
		loadimage(NULL, _T("resources/dialogue/level1-1.jpg"));
		Sleep(1000);
		_getch();
		_getch();
		loadimage(NULL, _T("resources/dialogue/level1-2.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level1-3.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level1-4.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level1-5.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level1-6.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level1-7.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level1-8.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level1-9.jpg"));
		_getch();
		cleardevice();
	}
	
	else if(level == 2) {
		loadimage(NULL, _T("resources/dialogue/level2-1.jpg"));
		Sleep(1000);
		_getch();
		_getch();
		loadimage(NULL, _T("resources/dialogue/level2-2.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level2-3.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level2-4.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level2-5.jpg"));
		_getch();
		cleardevice();
	}
	
	else if(level == 3) {
		loadimage(NULL, _T("resources/dialogue/level3-1.jpg"));
		Sleep(1000);
		_getch();
		_getch();
		loadimage(NULL, _T("resources/dialogue/level3-2.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level3-3.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level3-4.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level3-5.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level3-6.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level3-7.jpg"));
		_getch();
		cleardevice();
	}
	
	else if(level == 4) {
		loadimage(NULL, _T("resources/dialogue/level4-1.jpg"));
		Sleep(1000);
		_getch();
		_getch();
		loadimage(NULL, _T("resources/dialogue/level4-2.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level4-3.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level4-4.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level4-5.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level4-6.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level4-7.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level4-8.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level4-9.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/level4-10.jpg"));
		_getch();
		cleardevice();
	}
	
	else if(level == 5) {
		mciSendString(_T("open resources/sfx/ending.wav alias ending"), NULL, 0, NULL);	
		mciSendString(_T("play ending"), NULL, 0, NULL);
		loadimage(NULL, _T("resources/dialogue/ending-1.jpg"));
		Sleep(1000);
		_getch();
		_getch();
		loadimage(NULL, _T("resources/dialogue/ending-2.jpg"));
		_getch();
		loadimage(NULL, _T("resources/dialogue/ending-3.jpg"));
		_getch();
		mciSendString(_T("close ending"), NULL, 0, NULL);
	}
}

char getKeyboardInput() {															// get keyboard input from user function
	char kbInput;
	if (_kbhit) { 													
		kbInput = _getch();												
		return kbInput;												
	}
}

void playerWalk(char input, int playerPositionX, int playerPositionY, int movementCount, bool coin1_isCollected, int coinCounter, bool movement, bool coin2_isCollected, int livesLeft, char backgroundName[]) { 

	if(movementCount % 15 == 0) { 													// clear device and image stack for every 15 movements
		cleardevice();
	}	
	
	IMAGE playerModel;     
	loadimage(NULL, _T(backgroundName));  											// load level background image
	
	loadLivesCounter(livesLeft);
	loadCoinCounter(coinCounter);
	
	// coin1 position
	int coin1PosX; 
	int coin1PosY;	

	// coin2 position
	int coin2PosY;	
	int coin2PosX;	
	
	if(strcmp(backgroundName, "resources/image/level1_background.jpg") == 0) { 		// shows that is currently loading level 1
		coin1PosX = 20; 																
		coin1PosY = 440;
		coin2PosX = 370;
		coin2PosY = 250;
	}
	
	else if(strcmp(backgroundName, "resources/image/level2_background.jpg") == 0) { // shows that is currently loading level 2
		coin1PosX = 1200; 
		coin1PosY = 640;
		coin2PosX = 50;
		coin2PosY = 100;
	}
	
	else if(strcmp(backgroundName, "resources/image/level3_background.jpg") == 0) { // shows that is currently loading level 3
		coin1PosX = 2000; 															// make the coin not visible
		coin1PosY = 2000;
		coin2PosX = 2000;
		coin2PosY = 2000;
	}
	
	else if(strcmp(backgroundName, "resources/image/level4_background.jpg") == 0) {	// shows that is currently loading level 4
		coin1PosX = 2000; 															// make the coin not visible
		coin1PosY = 2000;
		coin2PosX = 2000;
		coin2PosY = 2000;
	}
	
	if(coin1_isCollected == false) { 									// if false, load coin1 image based on the predefined variables 
		loadCoin(coin1PosX, coin1PosY, coin1_isCollected);
	}   
	if(coin2_isCollected == false) { 									// if false, load coin1 image based on the predefined variables 
		loadCoin(coin2PosX, coin2PosY, coin2_isCollected);
	}                                                                                                       

	if (input == 's' || input == 'S') {									// if the user input s
		if(movement == false)											// if movement == false, means that the player is facing left in the previous movement
		{
			loadimage(&playerModel, _T("resources/image/char_left2.png"));
			transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
		}	
		else																
		{
			loadimage(&playerModel, _T("resources/image/char_right2.png"));			
			transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
		}
	
	}
	else if (input == 'w' || input == 'W') {
		if(movement == false)
		{
			loadimage(&playerModel, _T("resources/image/char_left2.png"));
			transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
		}
		else
		{
			loadimage(&playerModel, _T("resources/image/char_right2.png"));
			transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
		}
	}
	else if (input == 'a' || input == 'A') {
		loadimage(&playerModel, _T("resources/image/char_left2.png"));
		transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
	}
	else if (input == 'd' || input == 'D') {
		loadimage(&playerModel, _T("resources/image/char_right2.png"));
		transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
	}
	else if(input == VK_ESCAPE){
		loadimage(&playerModel, _T("resources/image/char_right2.png"));
		transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
	}
}

void item1Move(int item1X, int item1Y) {								// item move function for level 4
	IMAGE item1;
	loadimage(&item1, _T("resources/image/item1.png"));
	transparentImage(NULL, item1X, item1Y, &item1, 0xffc4c4);
}

void item2Move(int item2X, int item2Y) {
	IMAGE item2;
	loadimage(&item2, _T("resources/image/item2.png"));
	transparentImage(NULL, item2X, item2Y, &item2, 0xffc4c4);
}

void item3Move(int item3X, int item3Y) {
	IMAGE item3;
	loadimage(&item3, _T("resources/image/item3.png"));
	transparentImage(NULL, item3X, item3Y, &item3, 0xffc4c4);
}

void loadItemCounter(int itemCounter) {									// item counter function for level 4
	if(itemCounter == 0){
		outtextxy(1080, 550, _T("Items Collected: 0"));	
	}
	else if(itemCounter == 1){
		outtextxy(1080, 550, _T("Items Collected: 1"));	
	}
	else if(itemCounter == 2){
		outtextxy(1080, 550, _T("Items Collected: 2"));	
	}
	else if(itemCounter == 3){
		outtextxy(1080, 550, _T("Items Collected: 3"));	
	}
}

void bossMove(int bossX, int bossY, bool isFacingLeft) {				// boss move function for level 4
	
	IMAGE bossModel;
	if(isFacingLeft == true) {
		loadimage(&bossModel, _T("resources/image/boss_left.png"));
	}
	else {
		loadimage(&bossModel, _T("resources/image/boss_right.png"));
	}
	transparentImage(NULL, bossX, bossY, &bossModel, 0xffc4c4);	
}

void playerWalkLevel4(char input, int playerPositionX, int playerPositionY, int movementCount, int coinCounter, int livesLeft, bool movement, int item1X, int item1Y, int item2X, int item2Y, int item3X, int item3Y, int itemCounter, int bossX, int bossY, bool bossFacingLeft){
	
	if(movementCount % 20 == 0) { 									
		cleardevice();
	}	
	
	IMAGE playerModel;     
	loadimage(NULL, _T("resources/image/level4_background.jpg")); 

	loadLivesCounter(livesLeft);
	loadCoinCounter(coinCounter);
	loadItemCounter(itemCounter);
	
	item1Move(item1X, item1Y);
	item2Move(item2X, item2Y);
	item3Move(item3X, item3Y);
	
	if (input == 's' || input == 'S') {								
		if(movement == false)									
		{
			loadimage(&playerModel, _T("resources/image/char_left2.png"));
			transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
		}	
		else																
		{
			loadimage(&playerModel, _T("resources/image/char_right2.png"));			
			transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
		}
	
	}
	
	else if (input == 'w' || input == 'W') {													
		if(movement == false)																				
		{
			loadimage(&playerModel, _T("resources/image/char_left2.png"));
			transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);	
		}
		else					
		{
			loadimage(&playerModel, _T("resources/image/char_right2.png"));
			transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);	
		}
	}
	
	else if (input == 'a' || input == 'A') {
		loadimage(&playerModel, _T("resources/image/char_left2.png"));
		transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
	}
	
	else if (input == 'd' || input == 'D') {
		loadimage(&playerModel, _T("resources/image/char_right2.png"));
		transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
	}
	
	else if(input == VK_ESCAPE){
		loadimage(&playerModel, _T("resources/image/char_right2.png"));
		transparentImage(NULL, playerPositionX, playerPositionY, &playerModel, 0xffc4c4);
	}
	
	bossMove(bossX, bossY, bossFacingLeft);
}