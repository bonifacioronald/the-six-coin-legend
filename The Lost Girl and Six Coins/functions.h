void transparentImage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);
void loadCoin(int coinPosX, int coinPosY, bool coin_isCollected);
void loadCoinCounter(int counter);
char getKeyboardInput();
void playerWalk(char input, int playerPositionX, int playerPositionY, int movementCount, bool coin1_isCollected, int coinCounter, bool movement, bool coin2_isCollected, int livesLeft, char backgroundName[]);
void loadLivesCounter(int livesLeft);
void loadHorizontalLaser(int x, int y);
void loadVerticalLaser(int x, int y);
bool pause();
void playerWalkLevel4(char input, int playerPositionX, int playerPositionY, int movementCount, int coinCounter, int livesLeft, bool movement, int item1X, int item1Y, int item2X, int item2Y, int item3X, int item3Y, int itemCounter, int bossX, int bossY, bool bossFacingLeft);
void loadItemCounter(int itemCounter);
void loadLevelTutorial(int level);
void loadDialogue(int level);
void loadEndMenu(int winlose);