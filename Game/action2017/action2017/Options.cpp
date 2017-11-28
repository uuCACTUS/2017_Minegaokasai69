#include "hoge.h"
//#define HP 2

int Options(){
 int score1 = 0;
 int time = 100;
 int GetHitKeyStateAll(char*KeyStateBuf);
 char key[256];
 //int tairyoku = HP;
 int stock = 2;
 int color = 0xFFFFFF;

 Init();
 SetFontSize(30);

 while (1) {
  /*‰Šú‰»*/
  ClearDrawScreen();
  clsDx();
  /*ƒL[“ü—Íó•t*/
  
  
  
  /*ŒvZ*/
  
  /*•`‰æ*/
  
  DrawFormatString(0, 0, color, "%d", score1);

  //‰¼ˆÄ
  DrawFormatString(0,30,color," ~%d", stock);

  /*if (tairyoku == 2)
  {
   unsigned int color;
   color = GetColor(255, 255, 30);
   DrawFormatString(0, 30, color, "~%d", tairyoku);
  }
  
  if (tairyoku == 1)
  {
   unsigned int color;
   color = GetColor(255, 0, 0);
   DrawFormatString(0, 30, color, "~%d", tairyoku);
  }
  */
  if (stock <= -1)
   break;
  
  
  DrawFormatString(0,60,color,"c‚è%3d•b", time);

  if (time > 30 && time <= 50) {
   unsigned int color;
   color = GetColor(255, 255, 30);
   DrawFormatString(0, 60, color, "c‚è%3d•b", time);
  }
  
  if (time <= 30) {
   unsigned int color;
   color = GetColor(255, 0, 0);
   DrawFormatString(0, 60, color, "c‚è%3d•b", time);
  }
  if (time <= 0) {
   stock--;
   time = 100;
  }
  
  time--;

  if (time == 90)
  {
   score1=score1+time * 50+stock*15000;
   
  }

  

  /*”»’è*/

  /*ƒEƒFƒCƒg*/WaitTimer(1000);
  if (ProcessMessage() == -1)break;
 }

 DxLib_End();
 return 0;
}