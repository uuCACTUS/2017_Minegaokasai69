#include "hoge.h"

int KeyInputs(char *KeyBuf,
			  POSI *player1, int *J_count1, int *J_stop1,
			  POSI *player2, int *J_count2, int *J_stop2,
			  POSI *ball, int *catch_flag, int *needle_flag,
			  int *camera_main, int *camera_main_stop)
{
	/*
	int box_x = 0, box_y = 300;
	int ball_x = box_x += 30;
	int ball_y = box_y;
	int ball_r = 15;
	*/
	
	 	//全てのキーの押下状態を検知する
		//GetHitKeyStateAll(KeyBuf);
		
		//プレイヤー１◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
		
		//特定のキーが押されているときに特定の処理を行う
		if ( *(KeyBuf + KEY_INPUT_A) ){
			player1->x -= PlayerSpeed;
			player1->tg = D_LEFT;
		}
		if ( *(KeyBuf + KEY_INPUT_D) ){
			player1->x += PlayerSpeed;
			player1->tg = D_RIGHT;
		}
		//if ( KeyBuf->KEY_INPUT_UP    || KeyBuf->KEY_INPUT_W ) player->y -= PlayerSpeed;
		//if ( KeyBuf->KEY_INPUT_DOWN  || KeyBuf->KEY_INPUT_S ) player->y += PlayerSpeed;
		
		//ジャンプ
		if ( *(KeyBuf + KEY_INPUT_W) && *J_count1 < 2 ){
			
			if(*J_stop1 == 0){
				*J_count1 += 1;
				player1->st = JumpPower;
			}
			*J_stop1 += 1;
		}
		else *J_stop1 = 0;
		
		//しゃがむ
		if ( *(KeyBuf + KEY_INPUT_S) ){
			if(player1->h > P_HEIGHT / 2) player1->y += player1->h / 4;
			player1->h = P_HEIGHT / 2; 
		}
		else{
			if(player1->h == P_HEIGHT / 2) player1->y -= player1->h / 2;
			player1->h = P_HEIGHT;
		}
		
		//Qを押したら針を出す
		if ( *(KeyBuf + KEY_INPUT_Q) ) *needle_flag += 1;
		else *needle_flag = 0;
		
		//プレイヤー２◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
		
		if ( *(KeyBuf + KEY_INPUT_K) ){
			player2->x -= PlayerSpeed;
			player2->tg = D_LEFT;
		}
		if ( *(KeyBuf + KEY_INPUT_SEMICOLON) ){
			player2->x += PlayerSpeed;
			player2->tg = D_RIGHT;
		}
		
		//ジャンプ
		if ( *(KeyBuf + KEY_INPUT_O) && *J_count2 < 2 ){
			
			if(*J_stop2 == 0){
				*J_count2 += 1;
				player2->st = JumpPower;
			}
			*J_stop2 += 1;
		}
		else *J_stop2 = 0;
		
		//しゃがむ
		if ( *(KeyBuf + KEY_INPUT_L) ){
			if(player2->h > P_HEIGHT / 2) player2->y += player2->h / 4;
			player2->h = P_HEIGHT / 2; 
		}
		else{
			if(player2->h == P_HEIGHT / 2) player2->y -= player2->h / 2;
			player2->h = P_HEIGHT;
		}
		//Pを押したらボールが飛ぶ
		if ( *(KeyBuf + KEY_INPUT_P) ){
			if(ball->st==0){
				if(*catch_flag==1){
					ball->h += ThrowVY;
					ball->w += ThrowVX * pow(-1, player2->tg);
					*catch_flag = 0;
				}
				else if( sqrt( pow(player2->x - ball->x, 2) + pow(player2->y - ball->y, 2) ) <= CATCH_RANGE ) *catch_flag = 1;
			}
			ball->st++;
		}else ball->st=0;
		
		//その他◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆
		if ( *(KeyBuf + KEY_INPUT_SPACE) ){
			
			if(*camera_main_stop == 0){
				if(*camera_main == 1) *camera_main = 2;
				else				  *camera_main = 1;
			}
			*camera_main_stop += 1;
		}
		else *camera_main_stop = 0;
		
		
		/*	
	  	// 落下処理
		player->y -= player->st;
	
		// 落下加速度を加える
		player->st -= 1;
	
		// もし地面についていたら止まる
		if (box_y > 300){
			player->y = 300;
			player->st = 0;
		}
		*/
		
		/*
		//白く塗りつぶされた四角形を描画する（下またはSを押してるときは半分になる）
		if (KeyBuf[KEY_INPUT_DOWN] == 1 || KeyBuf[KEY_INPUT_S] == 1)
			DrawBox(box_x, box_y + 30, box_x + 60, box_y + 60, 0xFFFFFF, TRUE);
		else DrawBox(box_x, box_y, box_x + 60, box_y + 60, 0xFFFFFF, TRUE);
		
		//スペースキーを押すと、三角形が現れる
		if ((KeyBuf[KEY_INPUT_SPACE] == 1 && KeyBuf[KEY_INPUT_DOWN] == 1)
		 || (KeyBuf[KEY_INPUT_SPACE] == 1 && KeyBuf[KEY_INPUT_S] == 1))
			DrawTriangle(box_x + 60, box_y + 40, box_x + 60, box_y + 50, box_x + 110, box_y + 45, 0xFFFFFF, TRUE);
		
		else if (KeyBuf[KEY_INPUT_SPACE] == 1)
			DrawTriangle(box_x + 60, box_y + 15, box_x + 60, box_y + 45, box_x + 110, box_y + 30, 0xFFFFFF, TRUE);
		
		
		// 落下処理
		ball_y -= V_y;
	
		// 落下加速度を加える
		V_y -= 1;
	
		// もし地面についていたら止まる
		if (ball_y > 360) { JumpCount2++; }
	
		//地面についたのが１回目なら290の高さの位置に
		if ((ball_y > 360) && JumpCount2 == 1){
			ball_y = 290;
			V_y = 0;
		}
	
	  	//地面についたのが２回目なら330の高さに
		if ((ball_y > 360) && JumpCount2 == 2){
			ball_y = 330;
			V_y = 0;
		}
	
		//地面につくのが3回目以上なら止まる
		if ((ball_y > 360) && JumpCount2 >= 3){
	
			ball_y = 360;
	
			// 横移動処理
			ball_x++;
		}
		*/
		
		/*
		int m;
	
		if (KeyBuf[KEY_INPUT_P] || KeyBuf[KEY_INPUT_Q]){
	
	   		if (m == 0) flag ^= 1;
			
			m = 1;
		}
		else m = 0;
	
		if (flag) DrawCircle(ball_x, ball_y, ball_r, 0xFF0000, TRUE);
		*/
}