#include "hoge.h"

int Load(MULTI_POSI *map, MULTI_POSI *ene, int *m_length, int *clock_max){
	FILE *fp;
	char c;
	char s[10] = {'\0'};
	int i = 0, j = 0,
		n = 0;
	char mode;
	MULTI_POSI obj = {0};
	double angle = 0;
	int ground_size = 0;
	
	if(WIDTH >= HEIGHT)
		 ground_size = WIDTH * 2;
	else ground_size = HEIGHT * 2;
	
	fp = fopen("tests\\4grounds.txt", "r");
	while(1){
		ClearDrawScreen();
		/*
		if(j==0){mode='o'; obj.x=0; obj.y=0; obj.h=2000; obj.w=0; obj.t=600; obj.c=0; obj.ff=0; obj.tg=0; strcpy(s,"0");}
		if(j==1){mode='a'; obj.x=1000; obj.y=550; obj.h=200; obj.w=4200; obj.t=0; obj.c=0xFF8F00; obj.ff=0; obj.tg='s'; strcpy(s,"8");}
		if(j==2){mode='a'; obj.x=50; obj.y=300; obj.h=0; obj.w=0; obj.t=0; obj.c=0xFF8F00; obj.ff=0; obj.tg='g'; strcpy(s,"6");}
		if(j==3){mode='a'; obj.x=1950; obj.y=300; obj.h=0; obj.w=0; obj.t=0; obj.c=0xFF8F00; obj.ff=0; obj.tg='g'; strcpy(s,"4");}
		if(j==4){mode='a'; obj.x=700; obj.y=500; obj.h=200; obj.w=400; obj.t=0; obj.c=0xFF8F00; obj.ff=0; obj.tg='s'; strcpy(s,"5");}
		if(j==5){mode='a'; obj.x=900; obj.y=300; obj.h=400; obj.w=200; obj.t=0; obj.c=0; obj.c=0xFF8F00; obj.ff=0; obj.tg='s'; strcpy(s,"5");}
		if(j==6){mode='a'; obj.x=1120; obj.y=340; obj.h=100; obj.w=100; obj.t=0; obj.c=0; obj.c=0xFF8F00; obj.ff=0; obj.tg='s'; strcpy(s,"5");}
		if(j==7){mode='!'; obj.x=0; obj.y=0; obj.h=0; obj.w=0; obj.t=0; obj.c=0; obj.ff=0; obj.tg=0; strcpy(s,"0");}
		j++;
		*/
		
		fscanf(fp, "%c, %lf, %lf, %lf, %lf, %lf, %x, %d, %c, %s\n",
			&mode, &obj.x, &obj.y, &obj.h, &obj.w, &obj.t, &obj.c, &obj.ff, &obj.tg, s);
		
		if(mode == '!') break; //読み込み終了
		
		if(mode == '?') continue; //読み飛ばし
		
		if(mode == 'o'){ //オプション
			*m_length = obj.w;
			*clock_max = obj.t * 1000;
		}
		
		if(mode == 'a'){ //ステージオブジェクトの追加
			/*
			
			mode, x, y, h, w, t, c, ff, s, p
			
			mode ... (モード)
			x  ... 中心X座標(実数値)
			y  ... 中心Y座標(実数値)
			h  ... 縦幅(正の実数値)
			w  ... 横幅(正の実数値)
			t  ... 回転角(右向きが0、時計回りが＋の実数値(ラジアン))
			c  ... 色(16進数0xXXXXXX)
			ff ... フィルフラグ(0, 1)
			s  ... 形状(s:長方形 o:楕円 r:直角三角形 i:二等辺三角形)
			p  ... 中心座標の調整(0～9の整数値)
			
		 	*/
			obj.st = atoi(s);
			n = atoi(s);
			
			if(obj.tg == 'g' && (n != 5 || n != 0)){ //グラウンド(没)
				obj.w = ground_size;
				obj.h = ground_size;
			}
			angle = rad(obj.t);
			
			if(n != 0){
				obj.x += (  obj.w          * cos(angle) * (double)(P_Maker('d', n-1))
					     +  obj.w          * sin(angle) * (double)(P_Maker('l', n-1))
					     + (obj.w - obj.h) * sin(angle) * (double)(P_Maker('r', n-1)) ) / 2;
				obj.y += (  obj.w          * cos(angle) * (double)(P_Maker('r', n-1))
					     +  obj.w          * sin(angle) * (double)(P_Maker('d', n-1))
					     + (obj.w - obj.h) * cos(angle) * (double)(P_Maker('l', n-1)) ) / 2;
			}
			
			(map + i)->x  = obj.x;
			(map + i)->y  = obj.y;
			(map + i)->h  = obj.h;
			(map + i)->w  = obj.w;
			(map + i)->t  = obj.t;
			(map + i)->c  = obj.c;
			(map + i)->ff = obj.ff;
			(map + i)->tg = obj.tg;
			(map + i)->st = obj.st;
			i++;
		}
		
		if(mode == 'e'){ //敵オブジェクトの設定
			/*
			
			mode, x, y, s, t, fr, c, ff, ty, hp
			
			mode ... (モード)
			x  ... 出現X座標(実数値)
			y  ... 出現Y座標(実数値)
			s  ... サイズ倍率(0でない正の実数値)
			t  ... 出現開始時刻(0でない自然数(s))
			fr ... 出現頻度(0でない自然数(f))
			c  ... 色(16進数0xXXXXXX)
			ff ... フィルフラグ(0, 1)
			ty ... 形状(w:歩行タイプ)
			hp ... HP(自然数)
			
		 	*/
			
			obj.st = atoi(s);
			
			(ene + j)->x  = obj.x;
			(ene + j)->y  = obj.y;
			(ene + j)->h  = obj.h;
			(ene + j)->w  = obj.w;
			(ene + j)->t  = obj.t;
			(ene + j)->c  = obj.c;
			(ene + j)->ff = obj.ff;
			(ene + j)->tg = obj.tg;
			(ene + j)->st = obj.st;
			j++;
		}
		
		printfDx("mode : %c\n", mode);
		printMULTI_POSI(obj);
		WaitTimer(10);
		
		if(ProcessMessage() == -1) break;
	}
	
	fclose(fp);
}