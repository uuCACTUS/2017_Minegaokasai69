#include "hoge.h"

int GameMain(int *score)
{
	int i, j, //カウンタ変数
		t = 0; //ループカウンタ
	double testX, testY; //試験用の座標(?)
	double w_cos = 0, w_sin = 0, //オブジェクト回転簡易化変数
		   h_cos = 0, h_sin = 0; //オブジェクト回転簡易化変数
	char KeyBuf[256]; //キー入力受付
	MULTI_POSI L_map[MAP_MAX] = {0}; //マップデータ(ロード)
	MULTI_POSI L_ene[ENE_MAX] = {0}; //敵データ(ロード)
	POSI map[MAP_MAX] = {0}; //マップデータ
	POSI enemy = {0}; //敵
	E_POSI enemies[E_DRAWMAX] = {0};
	int  e_rev = 0, e_drawwait[E_DRAWMAX] = {0};
	POSI player1 = {550, HEIGHT/2, P_WIDTH, P_HEIGHT, 0, 0, D_RIGHT}; //プレイヤー (キー:W,A,S,D)
	POSI player2 = {700, HEIGHT/2, P_WIDTH, P_HEIGHT, 0, 0, D_RIGHT}; //プレイヤー (キー:NUM8,4,5,6)
	POSI ball = {WIDTH/2, HEIGHT/2, 0, 0, B_RANGE, 0, 0}; //ボール (仮)
	POSI altn = {0};
	int J_count1 = 0, J_count2 = 0, //空中ジャンプ回数のカウンタ
		J_stop1 = 0, J_stop2 = 0,   //ジャンプ処理のためのストッパー
		catch_flag = 1, //ボールを持っているか否か
		needle_flag = 0, //針の攻撃判定の有無
		ela_time1 = 0, ela_time2 = 1000; //ボールの反発したタイミングを計測
	int cameraX = 0,  //カメラ左端のX座標
		camera_main = 1, //カメラがなるべく映そうとするプレイヤー番号
		camera_main_stop = 0, //カメラ動作処理のためのストッパー
		m_length = 0, //マップの横の広さ
		clock = 0,    //ゲーム内時計
		clock_max = 0,//ゲーム内時計の最大値
		exact_clock = 0, exact_start = 0; //正確な時間計測
	int clock_color = 0xFFFFFF,
		hp_color = 0xFFFFFF, hp = 5,
		damflash1 = 1, damwait1 = 0, //プレイヤー１の被ダメ後無敵判定の待機時間計測用
		damflash2 = 1, damwait2 = 0, //プレイヤー２の被ダメ後無敵判定の待機時間計測用
		ene_damwait[E_DRAWMAX] = {0};
	double ball_speed = 0, ball_CR = 0;
	int needle_mov = 0;//針のアニメーション : 前隙5 持続5 後隙15 (計25)
	int bgm, se_needle,se_ball,se_over,se_clear ;
	
	Init();
	
	Load(L_map, L_ene, &m_length, &clock_max);
	clock = clock_max;
	printfDx("Loading End.");
	WaitTimer(1000);
	
	srand( (unsigned int)time(NULL) );
	
	ChangePOSI(map, L_map);
	
	exact_start = GetNowCount();
	
	bgm=LoadSoundMem("Escape.mp3");
	se_needle=LoadSoundMem("針.mp3");
	se_ball=LoadSoundMem("push13.wav");
	se_over=LoadSoundMem("bell15a.wav");
	se_clear=LoadSoundMem("clear.WAV");
	ChangeVolumeSoundMem(230,se_needle);
	PlaySoundMem(bgm,DX_PLAYTYPE_LOOP,TRUE);
	
	while(1){
		/*初期化関数*/
		ClearDrawScreen();
		clsDx();
		
		/*キー入力◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆*/
		GetHitKeyStateAll(KeyBuf);
		
		KeyInputs(KeyBuf, &player1, &J_count1, &J_stop1,
				  &player2, &J_count2, &J_stop2,
				  &ball, &catch_flag, &needle_flag,
				  &camera_main, &camera_main_stop);
		
		/*計算◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆*/
		
		//ボールの色変化
		ball_speed = sqrt( pow(ball.h, 2) + pow(ball.w, 2) );
		if     (ball_speed >= BCRMAX) ball_CR = 1;
		else if(ball_speed <= BCRMIN) ball_CR = 0;
		else ball_CR = (ball_speed - BCRMIN) / (BCRMAX + BCRMIN); 
		
		//重力
		player1.y += player1.st;
		player2.y += player2.st;
		ball.y += ball.h;
		
		
		
		
		for(i = 0; i < E_DRAWMAX; i++){
			switch(enemies[i].ty){
				case 'w': case 'm':
					enemies[i].x += enemies[i].vx;
					enemies[i].y += enemies[i].vy;
					if(enemies[i].vy < FALL_MAX) enemies[i].vy++;
					break;
			}
		}
		
		//enemy.y += enemy.st;
		
		//敵の移動
		//enemy.x += enemy.t;
		
		//ボール移動
		ball.x += ball.w;
		
		//ボール減衰(摩擦)
		if(ball.tg) ball.w *= 1. - (1. - B_FRICT) / (double)FPS;
		
		//ボール停止(横方向)
		if(abs(ball.w) <= B_STOPX){
			ball.w = 0;
			ball.tg = 0;
		}
		
		//ボール停止(縦方向)
		if(ball.w == 0 && (ela_time2 - ela_time1) <= B_STOPY_FRAME){
			ball.h = 0;
			ela_time2 = GetNowCount();
		}
		
		//最高落下速度
		if(player1.st < FALL_MAX) player1.st++;
		if(player2.st < FALL_MAX) player2.st++;
		if(ball.h < FALL_MAX) ball.h++;
		//if(enemy.st < FALL_MAX) enemy.st++;
		
		//カメラ追尾
		cameraX = (player1.x + player2.x)/2 - WIDTH/2;
		if(camera_main == 1 && player1.x - cameraX < CM_ADJUST        ) cameraX = player1.x - CM_ADJUST;
		if(camera_main == 1 && player1.x - cameraX > WIDTH - CM_ADJUST) cameraX = player1.x - (WIDTH - CM_ADJUST);
		if(camera_main == 2 && player2.x - cameraX < CM_ADJUST        ) cameraX = player2.x - CM_ADJUST;
		if(camera_main == 2 && player2.x - cameraX > WIDTH - CM_ADJUST) cameraX = player2.x - (WIDTH - CM_ADJUST);
		if(cameraX < 0) cameraX = 0;
		if(cameraX > m_length - WIDTH) cameraX = m_length - WIDTH;
		
		if(catch_flag==1){
			ball.h = (player2.y - ball.y) * CATCH_SPEED;
			ball.w = (player2.x - ball.x) * CATCH_SPEED;
		}
		
		//敵の出現
		for(i = 0; i < ENE_MAX; i++){
			if(clock <= L_ene[i].w * 1000 && GetNowCount() > e_drawwait[i] + L_ene[i].t){
				e_drawwait[i] = GetNowCount();
				
				enemies[e_rev].x = L_ene[i].x;
				enemies[e_rev].y = L_ene[i].y;
				enemies[e_rev].hp = L_ene[i].st;
				enemies[e_rev].ty = L_ene[i].tg;
				enemies[e_rev].c = L_ene[i].c;
				enemies[e_rev].ff = L_ene[i].ff;
				
				switch(enemies[i].ty){
					case 'w':
						enemies[e_rev].vx = E_DATA_WALKS_SPEED * pow(-1, rand()%2);
						enemies[e_rev].vy = 0;
						enemies[e_rev].h = E_DATA_WALKS_SIZE * L_ene[i].h;
						enemies[e_rev].w = E_DATA_WALKS_SIZE * L_ene[i].h;
						break;
					case 'm':
						enemies[e_rev].vx = E_DATA_MINIS_SPEED * pow(-1, rand()%2);
						enemies[e_rev].vy = 0;
						enemies[e_rev].h = E_DATA_MINIS_SIZE * L_ene[i].h;
						enemies[e_rev].w = E_DATA_MINIS_SIZE * L_ene[i].h;
						break;
				}
				
				e_rev = (e_rev + 1) % E_DRAWMAX;
			}
		}
		
		/*判定◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆*/
		
		//物理判定
		for(i = 0; i < MAP_MAX; i++){
			
			TouchMap(&player1, &map[i], &J_count1);
			TouchMap(&player2, &map[i], &J_count2);
			for(j = 0; j < E_DRAWMAX; j++)
				switch(enemies[i].ty){
					case 'w': case 'm':
						TouchMapEnemy(&enemies[j], &map[i]);
						break;
				}
			TouchMapBall(&ball, &map[i], &ela_time1, &ela_time2, se_ball);
			
			if(map[i].tg == 0) break;
		}
		
		//敵と本体の接触
		for(i = 0; i < E_DRAWMAX; i++){
			enemy.x = enemies[i].x;
			enemy.y = enemies[i].y;
			enemy.h = enemies[i].h;
			enemy.w = enemies[i].w;
			
			if(enemies[i].hp > 0){
				if( CheckTouchAll(player1, enemy) && GetNowCount() > damwait1 + P_DWAIT){
					hp--;
					if(hp > 0) damwait1 = GetNowCount();	
				}
				if( CheckTouchAll(player2, enemy) && GetNowCount() > damwait2 + P_DWAIT){
					hp--;
					if(hp > 0) damwait2 = GetNowCount();	
				}
			}
		}
		
		/*
		if( CheckTouchAll(player1, enemy) && GetNowCount() > damwait1 + P_DWAIT){
			hp--;
			if(hp > 0) damwait1 = GetNowCount();	
		}
		if( CheckTouchAll(player2, enemy) && GetNowCount() > damwait2 + P_DWAIT){
			hp--;
			if(hp > 0) damwait2 = GetNowCount();	
		}
		*/
		
		//敵と針の接触
		altn.x = ( (player1.x +           N_BOTX  * pow(-1, player1.tg+1) )
		         + (player1.x + (N_LENGTH+N_BOTX) * pow(-1, player1.tg+1) ) ) / 2;
		altn.y = player1.y;
		altn.h = N_RANGE * 2;
		altn.w = N_LENGTH;
		
		if( needle_mov > NMOV_A && needle_mov <= NMOV_W + NMOV_A ){
			for(i = 0; i < E_DRAWMAX; i++){
				
				enemy.x = enemies[i].x;
				enemy.y = enemies[i].y;
				enemy.h = enemies[i].h;
				enemy.w = enemies[i].w;
				
				if( enemies[i].hp > 0 && CheckTouchAll(altn, enemy) && GetNowCount() > ene_damwait[i] + E_DWAIT ){
					
					ene_damwait[i] = GetNowCount();
					
					if( (player1.tg ==  D_LEFT && CheckTouchAll(altn, enemy) && enemies[i].x <= altn.x - altn.w + N_CRT )
					 && (player1.tg == D_RIGHT && CheckTouchAll(altn, enemy) && enemies[i].x >= altn.x + altn.w - N_CRT ) ){
					 	enemies[i].hp -= N_DAM * (N_DAMCRT + 100) / 100;
					 	switch(enemies[i].ty){
							case 'w':
								*score += N_DAM * E_DATA_WALKS_SCpHP * (N_DAMCRT + 100) / 100;
								break;
							case 'm':
								*score += N_DAM * E_DATA_MINIS_SCpHP * (N_DAMCRT + 100) / 100;
								break;
						}
					}else{
						enemies[i].hp -= N_DAM;
						switch(enemies[i].ty){
							case 'w':
								*score += N_DAM * E_DATA_WALKS_SCpHP;
								break;
							case 'm':
								*score += N_DAM * E_DATA_MINIS_SCpHP;
								break;
						}
					}
					
					switch(enemies[i].ty){
							case 'w': case 'm':
								enemies[i].vx *= -1;
								break;
					}
				}
			}
		}
		
		//ボールの判定
		altn.x = ball.x;
		altn.y = ball.y;
		altn.h = ball.t*2;
		altn.w = ball.t*2;
		
		if( !catch_flag && ball_speed>=BCRMIN&&ball_speed<=BCRMAX ){
			for(i = 0; i < E_DRAWMAX; i++){
				
				enemy.x = enemies[i].x;
				enemy.y = enemies[i].y;
				enemy.h = enemies[i].h;
				enemy.w = enemies[i].w;
				
				if( enemies[i].hp > 0 && CheckTouchAll(altn, enemy) && GetNowCount() > ene_damwait[i] + E_DWAIT ){
					
					ene_damwait[i] = GetNowCount();
					
					if(ball_speed>=BCRMID&&ball_speed<=BCRMAX){
					 	enemies[i].hp -= B_DAM * (B_DAMCRT + 100) / 100;
					 	switch(enemies[i].ty){
							case 'w':
								*score += B_DAM * E_DATA_WALKS_SCpHP * (B_DAMCRT + 100) / 100;
								break;
							case 'm':
								*score += B_DAM * E_DATA_MINIS_SCpHP * (B_DAMCRT + 100) / 100;
								break;
						}
					}else{
						enemies[i].hp -= B_DAM;
						switch(enemies[i].ty){
							case 'w':
								*score += B_DAM * E_DATA_WALKS_SCpHP;
								break;
							case 'm':
								*score += B_DAM * E_DATA_MINIS_SCpHP;
								break;
						}
					}
					
					switch(enemies[i].ty){
							case 'w': case 'm':
								enemies[i].vx *= -1;
								break;
					}
				}
			}
		}
		
		//敵の被ダメ状態
		
		for(i = 0; i < E_DRAWMAX; i++){
			if(enemies[i].ty == 'w'){
				if(GetNowCount() <= ene_damwait[i] + E_DATA_WALKS_DESC){
					if( abs(enemy.x - player1.x) < abs(enemy.x - player2.x) )
						enemies[i].vx = E_DATA_WALKS_SPEED * 2 * pow(-1, ( player1.x > enemies[i].x));
					else
						enemies[i].vx = E_DATA_WALKS_SPEED * 2 * pow(-1, ( player2.x > enemies[i].x));
				}
				else{
					if(enemies[i].vx < 0) enemies[i].vx = -E_SPEED;
					else                  enemies[i].vx = E_SPEED;
				}
			}
		}
		
		/*描画◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆*/
		
		//背景用の仮座標軸
		for(i = 0; i < ceil(HEIGHT / BGL_GRID); i++){
			
			j = (int)(HEIGHT/2 + (ceil(i/2.) * pow(-1, i)) * BGL_GRID);
			
			DrawLine(-10, j, WIDTH+10, j, C_BGL);
		}
		
		for(i = 0; i < ceil(m_length / BGL_GRID); i++){
			
			j = (int)(m_length/2 + (ceil(i/2.) * pow(-1, i)) * BGL_GRID);
			
			DrawLine(j - cameraX * BGL_CDEL, -10, j - cameraX * BGL_CDEL, HEIGHT+10, C_BGL);
		}
		
		//マップオブジェクト
		for(i = 0; i < MAP_MAX; i++){
			if(map[i].tg == 'o')
				DrawOvalAAplus(map[i].x, map[i].y, map[i].w/2, map[i].h/2, map[i].t, POSNUM_def, L_map[i].c, L_map[i].ff);
			else{
				
				w_cos = map[i].w * cos(rad(map[i].t)) / 2;
				w_sin = map[i].w * sin(rad(map[i].t)) / 2;
				h_cos = map[i].h * cos(rad(map[i].t)) / 2;
				h_sin = map[i].h * sin(rad(map[i].t)) / 2;
				if(map[i].tg == 's' || map[i].tg == 'g'){
					DrawQuadrangleAA(map[i].x - w_cos - h_sin - cameraX, map[i].y - w_sin + h_cos,
								     map[i].x + w_cos - h_sin - cameraX, map[i].y + w_sin + h_cos,
								     map[i].x + w_cos + h_sin - cameraX, map[i].y + w_sin - h_cos,
								     map[i].x - w_cos + h_sin - cameraX, map[i].y - w_sin - h_cos,
								     L_map[i].c, L_map[i].ff);
					DrawCrossAA(map[i].x - cameraX, map[i].y, map[i].t, 10, L_map[i].c);
				}
				if(map[i].tg == 'r'){
					DrawTriangleAA(map[i].x - w_cos - h_sin - cameraX, map[i].y - w_sin + h_cos,
								   map[i].x + w_cos - h_sin - cameraX, map[i].y + w_sin + h_cos,
								   map[i].x + w_cos + h_sin - cameraX, map[i].y + w_sin - h_cos,
								   L_map[i].c, L_map[i].ff);
					DrawCircleAA(map[i].x - cameraX, map[i].y, 10, POSNUM_def, L_map[i].c, FALSE);
				}
				if(map[i].tg == 'i'){
					DrawTriangleAA(map[i].x - w_cos - h_sin - cameraX, map[i].y - w_sin + h_cos,
								   map[i].x + w_cos - h_sin - cameraX, map[i].y + w_sin + h_cos,
								   map[i].x + h_sin - cameraX, map[i].y - h_cos,
								   L_map[i].c, L_map[i].ff);
					DrawCrossAA(map[i].x - cameraX, map[i].y, map[i].t+45, 10, L_map[i].c);
				}
			}
			//printMULTI_POSI(map[i]);
			
			if(map[i].tg == 0) break;
		}
		
		//プレイヤー1
		if(GetNowCount() > damwait1 + P_DWAIT || damflash1){
			DrawBoxAA(player1.x - player1.w/2                        - cameraX, player1.y - player1.h/2    ,
					  player1.x + player1.w/2                        - cameraX, player1.y + player1.h/2    , C_PL1, FALSE);
			DrawBoxAA(player1.x - player1.w/2 * (1.-P_INNBOX) - cameraX, player1.y - player1.h/2 * (1.-P_INNBOX),
					  player1.x + player1.w/2 * (1.-P_INNBOX) - cameraX, player1.y + player1.h/2 * (1.-P_INNBOX), C_PL1, FALSE);
			
			DrawEQTriangle(player1.x - cameraX, player1.y, 180 * (!player1.tg), 20, C_PL1, FALSE);
		}
		damflash1 ^= 1;
		
		//針
		if( (needle_flag > 0 && needle_flag <= 25) || needle_mov > 0){
			if(needle_mov <= 0){
				needle_mov = 25;
				PlaySoundMem(se_needle,DX_PLAYTYPE_BACK,TRUE);
			}
			
			//◆◆前隙◆◆
			if(needle_mov > NMOV_W + NMOV_A){
				if(player1.tg) DrawTriangleAA(player1.x + N_BOTX - cameraX, player1.y - N_RANGE/(NMOV_B+1) * (NMOV_TOTAL+1 - needle_mov),
											  player1.x + N_BOTX - cameraX, player1.y + N_RANGE/(NMOV_B+1) * (NMOV_TOTAL+1 - needle_mov),
											  player1.x + N_BOTX + N_LENGTH/(NMOV_B+1) * (NMOV_TOTAL+1 - needle_mov) - cameraX, player1.y, C_PL1, FALSE);
				else           DrawTriangleAA(player1.x - N_BOTX - cameraX, player1.y - N_RANGE/(NMOV_B+1) * (NMOV_TOTAL+1 - needle_mov),
											  player1.x - N_BOTX - cameraX, player1.y + N_RANGE/(NMOV_B+1) * (NMOV_TOTAL+1 - needle_mov),
											  player1.x - N_BOTX - N_LENGTH/(NMOV_B+1) * (NMOV_TOTAL+1 - needle_mov) - cameraX, player1.y, C_PL1, FALSE);
			}
			//◆◆持続◆◆
			else if(needle_mov > NMOV_A){
				if(player1.tg) DrawTriangleAA(player1.x + N_BOTX            - cameraX, player1.y - N_RANGE,
											  player1.x + N_BOTX            - cameraX, player1.y + N_RANGE,
											  player1.x + N_BOTX + N_LENGTH - cameraX, player1.y, 0xFFFFFF, FALSE);
				else           DrawTriangleAA(player1.x - N_BOTX            - cameraX, player1.y - N_RANGE,
											  player1.x - N_BOTX            - cameraX, player1.y + N_RANGE,
											  player1.x - N_BOTX - N_LENGTH - cameraX, player1.y, 0xFFFFFF, FALSE);
			}
			//◆◆後隙◆◆
			else if(needle_mov > 0) {
				if(player1.tg) DrawTriangleAA(player1.x + N_BOTX - cameraX, player1.y - N_RANGE/(NMOV_A+NMOV_E) * (needle_mov-1 + NMOV_E),
											  player1.x + N_BOTX - cameraX, player1.y + N_RANGE/(NMOV_A+NMOV_E) * (needle_mov-1 + NMOV_E),
											  player1.x + N_BOTX + N_LENGTH - cameraX, player1.y, C_PL1, FALSE);
				else           DrawTriangleAA(player1.x - N_BOTX - cameraX, player1.y - N_RANGE/(NMOV_A+NMOV_E) * (needle_mov-1 + NMOV_E),
											  player1.x - N_BOTX - cameraX, player1.y + N_RANGE/(NMOV_A+NMOV_E) * (needle_mov-1 + NMOV_E),
											  player1.x - N_BOTX - N_LENGTH - cameraX, player1.y, C_PL1, FALSE);
			}
			
			needle_mov--;
		}
		
		if(!needle_flag && needle_mov <= NMOV_A) needle_mov = 0;
		
		if(needle_mov < 0) WaitTimer(1000);
		
		//プレイヤー2
		if(GetNowCount() > damwait2 + P_DWAIT || damflash2){
			DrawBoxAA(player2.x - player2.w/2                        - cameraX, player2.y - player2.h/2    ,
					  player2.x + player2.w/2                        - cameraX, player2.y + player2.h/2    , C_PL2, FALSE);
			DrawBoxAA(player2.x - player2.w/2 * (1.-P_INNBOX) - cameraX, player2.y - player2.h/2 * (1.-P_INNBOX),
					  player2.x + player2.w/2 * (1.-P_INNBOX) - cameraX, player2.y + player2.h/2 * (1.-P_INNBOX), C_PL2, FALSE);
					  
			DrawEQTriangle(player2.x - cameraX, player2.y, 180 * (!player2.tg), 20, C_PL2, FALSE);
		}
		damflash2 ^= 1;
		
		//ボール
		DrawCircleAA(ball.x - cameraX, ball.y, ball.t, POSNUM_def, MixColor(C_BLN, C_BLH, 1 - ball_CR, ball_CR), FALSE);
		
		//敵
		
		for(i = 0; i < E_DRAWMAX; i++){
			if(enemies[i].hp > 0){
				DrawBoxAA(enemies[i].x - enemies[i].w/2 - cameraX, enemies[i].y - enemies[i].h/2,
						  enemies[i].x + enemies[i].w/2 - cameraX, enemies[i].y + enemies[i].h/2, enemies[i].c, enemies[i].ff);
				//敵のHP
				SetFontSize(EHP_FSIZE);
				DrawFormatString(enemies[i].x - GetDrawFormatStringWidth("%d", enemies[i].hp)/2 - cameraX,
				                 enemies[i].y - EHP_FSIZE/2, enemies[i].c, "%d", enemies[i].hp);
			}else{
				if( GetNowCount() <= ene_damwait[i] + E_CLEAR ){
					
					j = ene_damwait[i] + E_CLEAR - GetNowCount();
					
					if(enemies[i].ty == 'w') *score += E_DATA_WALKS_SCDST;
					
					SetFontSize( EHP_FSIZE * j/E_CLEAR );
					DrawFormatString(enemies[i].x - GetDrawFormatStringWidth("%d", enemies[i].hp)/2 - cameraX,
				                     enemies[i].y - EHP_FSIZE/2*(float)j/E_CLEAR, enemies[i].c, "%d", enemies[i].hp);
					DrawBoxAA(enemies[i].x - enemies[i].w/2 * j/E_CLEAR - cameraX, enemies[i].y - enemies[i].h/2 * j/E_CLEAR,
						      enemies[i].x + enemies[i].w/2 * j/E_CLEAR - cameraX, enemies[i].y + enemies[i].h/2 * j/E_CLEAR,
							  MixColor(enemies[i].c, 0xFFFFFF, (float)j/E_CLEAR, 1-(float)j/E_CLEAR ), enemies[i].ff);
					DrawCircleAA(enemies[i].x - cameraX, enemies[i].y, (enemies[i].w + enemies[i].h)/4 * (1-(float)j/E_CLEAR),
								 POSNUM_def, MixColor(0xFFFFFF, 0x000000, (float)j/E_CLEAR, 1-(float)j/E_CLEAR ), FALSE);
				}
			}
		}
		
		
		/*
		
		if(enemy.tg > 0){
			DrawBoxAA(enemy.x - enemy.w/2 - cameraX, enemy.y - enemy.h/2,
					  enemy.x + enemy.w/2 - cameraX, enemy.y + enemy.h/2, C_ENE, FALSE);
			//敵のHP
			SetFontSize(EHP_FSIZE);
			DrawFormatString(enemy.x - GetDrawFormatStringWidth("%d", enemy.tg)/2 - cameraX, enemy.y - EHP_FSIZE/2, C_ENE, "%d", enemy.tg);
		}else{
			if( GetNowCount() <= ene_damwait + E_CLEAR ){
				
				j = ene_damwait + E_CLEAR - GetNowCount();
				
				DrawBoxAA(enemy.x - enemy.w/2 * j/E_CLEAR - cameraX, enemy.y - enemy.h/2 * j/E_CLEAR,
					      enemy.x + enemy.w/2 * j/E_CLEAR - cameraX, enemy.y + enemy.h/2 * j/E_CLEAR,
						  MixColor(C_ENE, 0xFFFFFF, (float)j/E_CLEAR, 1-(float)j/E_CLEAR ), FALSE);
				DrawCircleAA(enemy.x - cameraX, enemy.y, (enemy.w + enemy.h)/4 * (1-(float)j/E_CLEAR), POSNUM_def,
				             MixColor(0xFFFFFF, 0x000000, (float)j/E_CLEAR, 1-(float)j/E_CLEAR ), FALSE);
			}
		}
		
		*/
		
		/*ウェイト◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆*/
		
		SetFontSize(OPT_FSIZE);
		
		//スコアの表示
		DrawFormatString(0, 0, 0xFFFFFF, "score %06d", *score);
		
		//ＨＰの表示
		for(i = 0;i < LIFE_NUM;i++){
			if(i < hp) DrawFormatString(i * OPT_FSIZE, OPT_FSIZE, hp_color, "■");
			else       DrawFormatString(i * OPT_FSIZE, OPT_FSIZE, hp_color, "□");
		}
		if (hp <= LIFE_NUM/2) hp_color = 0xFFFF1E;
		if (hp == 1) hp_color = 0xFF0000;
		if (hp <= 0){
			StopSoundMem(bgm);
			WaitTimer(GAMEOVER_WAIT);
			PlaySoundMem(se_over, DX_PLAYTYPE_BACK,TRUE);
			return STATE_GAMEOVER;
		}
		
		//残り時間の表示
		DrawFormatString(0, OPT_FSIZE * 2, clock_color, "time %02d:%02d:%02d", clock/60000, clock/1000%60, clock/10%100);
		
		if      (clock >= CLOCK_YEL * 1000) clock_color = 0xFFFFFF;
		else if (clock >= CLOCK_RED * 1000) clock_color = C_CYEL;
		else if (clock >= 0)                clock_color = C_CRED;
		else {
			StopSoundMem(bgm);
			WaitTimer(CLEAR_WAIT);
			PlaySoundMem(se_clear, DX_PLAYTYPE_BACK,TRUE);
			return STATE_ENDING;
		}
  
		
		 //回転テスト
		//testX = 500; testY = 500;
		//Rotation(450, 300, &testX, &testY, 30+t);
		//DrawCrossAA(200, HEIGHT/2, t, 10, 0xFFFFFF);
		//DrawOvalAAplus(200, HEIGHT/2, 200, 150, t, 20, 0xFFFFFF, FALSE);
		//printfDx("testX : %lf \ntestY : %lf \n", testX, testY);
		clsDx();
		/*
		printfDx("                    X : %lf \n", ball.x);
		printfDx("                    Y : %lf \n", ball.y);
		printfDx("                    vx : %lf \n", ball.w);
		printfDx("                    vy : %lf \n", ball.h);
		printfDx("                    sp : %lf  \n", ball_speed);
		printfDx("                    st : %d  \n", ball.st);
		printfDx("                    tg : %d  \n", ball.tg);
		printfDx("                    Nflag : %d \n", needle_flag);
		printfDx("                    NM : %+d \n", needle_mov);
		
		printfDx("                    E.x  : %lf \n",  enemies[0].x);
		printfDx("                    E.y  : %lf \n",  enemies[0].y);
		printfDx("                    E.vx : %lf \n",  enemies[0].vx);
		printfDx("                    E.vy : %lf \n",  enemies[0].vy);
		printfDx("                    E.h  : %lf \n",  enemies[0].h);
		printfDx("                    E.w  : %lf \n",  enemies[0].w);
		printfDx("                    E.c  : %06x \n", enemies[0].c);
		printfDx("                    E.ff : %d \n",   enemies[0].ff);
		printfDx("                    E.ty : %c \n",   enemies[0].ty);
		printfDx("                    E.hp : %d \n",   enemies[0].hp);
		
		printfDx("                    LE.x  : %lf \n",  L_ene[0].x);
		printfDx("                    LE.y  : %lf \n",  L_ene[0].y);
		printfDx("                    LE.h  : %lf \n",  L_ene[0].h);
		printfDx("                    LE.w  : %lf \n",  L_ene[0].w);
		printfDx("                    LE.t  : %lf \n",  L_ene[0].t);
		printfDx("                    LE.c  : %06x \n",  L_ene[0].c);
		printfDx("                    LE.ff  : %d \n",  L_ene[0].ff);
		printfDx("                    LE.tg  : %c \n",  L_ene[0].tg);
		printfDx("                    LE.st  : %d \n",  L_ene[0].st);
		*/
		WaitTimer(1000/FPS);
		t++;
		exact_clock = GetNowCount();
		clock = clock_max - (exact_clock - exact_start);
		
		if(ProcessMessage() == -1) break;
	}
	
	DxLib_End();
	return 0;
}

void ChangePOSI(POSI *map, MULTI_POSI *L_map){
	int i;
	
	for(i = 0; i < MAP_MAX; i++){
		(map + i)->x  = (L_map + i)->x;
		(map + i)->y  = (L_map + i)->y;
		(map + i)->h  = (L_map + i)->h;
		(map + i)->w  = (L_map + i)->w;
		(map + i)->t  = (L_map + i)->t;
		(map + i)->tg = (L_map + i)->tg;
		(map + i)->st = (L_map + i)->st;
	}
}