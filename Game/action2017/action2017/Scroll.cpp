#include"hoge.h"

int function_status = STATE_TITLE;
unsigned int White;
char KeyBuf[256];


//タイトル画面
int title(int *score) {
	char mes1[] = "squive";
	
 DrawBox(0, 0, WIDTH, HEIGHT, GetColor(100,100,255), TRUE);
 SetFontSize(100);
 DrawString(WIDTH/2-GetDrawStringWidth(mes1, strlen(mes1))/2, 200, mes1, GetColor(255,100,100));
 SetFontSize(32);
 DrawFormatString(WIDTH/2-GetDrawFormatStringWidth("last score:%d",*score)/2, 350, 0xFFFFFF,"last score:%d",*score);
 DrawString(300, 500," スタート Spaceキー\n 終了   Escキー ", 0xFFFFFF);
 if (KeyBuf[KEY_INPUT_SPACE] == 1)
  return STATE_MAIN;
 if (KeyBuf[KEY_INPUT_ESCAPE] == 1)
  return STATE_END;
 return STATE_TITLE;
}
//ゲーム中
/*int gameMain() {
 int cameraX=0;
 int playerX=WIDTH/2;
 int realX = 300;
 char KeyBuf2[256];
 while (1) {
  ClearDrawScreen();
  
  GetHitKeyStateAll(KeyBuf2);

  if (KeyBuf2[KEY_INPUT_A]) playerX -= 10;
  if (KeyBuf2[KEY_INPUT_D]) playerX += 10;

  cameraX = playerX - WIDTH / 2; //プレイヤーを画面中央に配置

  DrawBoxAA(playerX - cameraX - 10, HEIGHT / 2 - 10, playerX - cameraX + 10, HEIGHT / 2 + 10, White, TRUE);
  
  DrawLineAA(WIDTH / 2 - cameraX, - 10, WIDTH / 2 - cameraX, HEIGHT + 10, 0x444444);
  DrawLineAA(-10, HEIGHT / 2, WIDTH + 10, HEIGHT/2, 0x444444);
  DrawBoxAA(realX - cameraX - 10, 200 - 10, realX - cameraX + 10, 200 + 10, 0xFF6666, TRUE);

  WaitTimer(100);
  if (ProcessMessage() == -1) break;
 }

 return STATE_MAIN;
}*/
//クリア画面
int ending(int *score) {
	char mes1[] = "SQUIVE!";
	char mes2[] = "タイトルに戻る T";
	
 SetFontSize(64);
 DrawString(WIDTH / 2 - GetDrawStringWidth(mes1, strlen(mes1)) / 2, 200, mes1, GetColor(255, 255, 30));
 SetFontSize(32);
 DrawFormatString(WIDTH/2-GetDrawFormatStringWidth("your score:%d",*score)/2, 350, 0xFFFFFF,"your score:%d",*score);
 DrawString(WIDTH / 2 - GetDrawStringWidth(mes2, strlen(mes2)) / 2, 500, mes2, GetColor(255, 255, 255));
 if (KeyBuf[KEY_INPUT_T] == 1)
  return STATE_TITLE;
 return STATE_ENDING;
}
//ゲームオーバー
int gameover(int *score){
	char mes1[] = "GAME OVER";
	char mes2[] = "タイトルに戻る T";
	
 SetFontSize(64);
 DrawString(WIDTH / 2 - GetDrawStringWidth(mes1, strlen(mes1)) / 2, 200, mes1, GetColor(255, 0, 0));
 SetFontSize(32);
 DrawFormatString(WIDTH/2-GetDrawFormatStringWidth("your score:%d",*score)/2, 350, 0xFFFFFF,"your score:%d",*score);
 DrawString(WIDTH / 2 - GetDrawStringWidth(mes2, strlen(mes2)) / 2, 500, mes2, GetColor(255, 255, 255));
 if (KeyBuf[KEY_INPUT_T] == 1)
  return STATE_TITLE;
 return STATE_GAMEOVER;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	int score = 0;
	
 	ChangeWindowMode(TRUE);
 
	if (DxLib_Init() == -1) return -1;
	
	White = GetColor(255, 255, 255);
 
	SetDrawScreen(DX_SCREEN_BACK);
 	SetGraphMode(WIDTH, HEIGHT, 32);

 	while (1) {
 		ClearDrawScreen();
		GetHitKeyStateAll(KeyBuf);
		
		switch (function_status) {
  			case STATE_TITLE   : function_status = title(&score);
								 break;
			case STATE_MAIN    : function_status = GameMain(&score);
								 break;
			case STATE_ENDING  : function_status = ending(&score);
								 break;
			case STATE_GAMEOVER: function_status = gameover(&score);
								 break;
		}
	 	if (ProcessMessage() == -1)break;
	 	ScreenFlip;
	}
	
	DxLib_End();
	return 0;
	
}