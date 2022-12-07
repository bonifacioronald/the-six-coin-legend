#include "header.h"
#include "functions.h"
#include "level1.h"

int main() {
	
	initgraph(1280, 720); 																					// initialize graphic window with width = 1280, height = 720
	
	mciSendString(_T("open resources/video/game_intro.avi type MPEGVideo alias menuvideo"), NULL, 0, NULL); // open game intro video
	mciSendString(_T("open resources/sfx/mainmenu.wav alias mainmenu"), NULL, 0, NULL);						// open music menu
	
	loadimage(NULL, _T("resources/image/menu_background.png"));												// load menu image
	mciSendString(_T("play mainmenu"), NULL, 0, NULL);														// play music menu	
	
	while (!_kbhit()) { 																					// keep looping until a keyboard key has been hit
		char input = getKeyboardInput(); 																	// store keyboard input in variable "input"
		if (input != NULL) { 																				// final check if "input" is not empty
			cleardevice();	
			mciSendString(_T("close mainmenu"), NULL, 0, NULL);												// close music menu
			mciSendString(_T("play menuvideo"), NULL, 0, NULL);												// load game intro video
			settextstyle(24, 0, _T("Consolas"));															// set text font 
			outtextxy(0, 0, _T("press any key in this window to skip the video"));							// output text in main window screen
			outtextxy(760, 690, _T("press any key in this window to skip the video"));		
			_getch();																						// press any key to skip the video
			mciSendString(_T("close menuvideo"), NULL, 0, NULL);											// close game intro video
			
			loadLevel1();																					// start level 1																						
			break;
		}
	}

	_getch();
	closegraph();
}