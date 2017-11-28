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
		
		if(mode == '!') break; //�ǂݍ��ݏI��
		
		if(mode == '?') continue; //�ǂݔ�΂�
		
		if(mode == 'o'){ //�I�v�V����
			*m_length = obj.w;
			*clock_max = obj.t * 1000;
		}
		
		if(mode == 'a'){ //�X�e�[�W�I�u�W�F�N�g�̒ǉ�
			/*
			
			mode, x, y, h, w, t, c, ff, s, p
			
			mode ... (���[�h)
			x  ... ���SX���W(�����l)
			y  ... ���SY���W(�����l)
			h  ... �c��(���̎����l)
			w  ... ����(���̎����l)
			t  ... ��]�p(�E������0�A���v��肪�{�̎����l(���W�A��))
			c  ... �F(16�i��0xXXXXXX)
			ff ... �t�B���t���O(0, 1)
			s  ... �`��(s:�����` o:�ȉ~ r:���p�O�p�` i:�񓙕ӎO�p�`)
			p  ... ���S���W�̒���(0�`9�̐����l)
			
		 	*/
			obj.st = atoi(s);
			n = atoi(s);
			
			if(obj.tg == 'g' && (n != 5 || n != 0)){ //�O���E���h(�v)
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
		
		if(mode == 'e'){ //�G�I�u�W�F�N�g�̐ݒ�
			/*
			
			mode, x, y, s, t, fr, c, ff, ty, hp
			
			mode ... (���[�h)
			x  ... �o��X���W(�����l)
			y  ... �o��Y���W(�����l)
			s  ... �T�C�Y�{��(0�łȂ����̎����l)
			t  ... �o���J�n����(0�łȂ����R��(s))
			fr ... �o���p�x(0�łȂ����R��(f))
			c  ... �F(16�i��0xXXXXXX)
			ff ... �t�B���t���O(0, 1)
			ty ... �`��(w:���s�^�C�v)
			hp ... HP(���R��)
			
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