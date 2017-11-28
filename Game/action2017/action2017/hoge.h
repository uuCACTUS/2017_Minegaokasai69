#include "DxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

/*�������V�X�e���֘A������*/
//#define M_PI acos(-1)
#define ATAN_FILTER 10000
#define POSNUM_def 50

#define FPS			60
#define WIDTH		900
#define HEIGHT		600

#define OPT_FSIZE 30
#define CLOCK_YEL 50 //(s)
#define C_CYEL 0xFFFF1E
#define CLOCK_RED 30 //(s)
#define C_CRED 0xFF0000

#define CLEAR_WAIT 2000
#define GAMEOVER_WAIT 2000

/*�������S�I�u�W�F�N�g���ʁ�����*/
#define MAP_MAX		1000
#define FALL_MAX 20
#define WALL_DEPTH FALL_MAX+1

/*�������v���C���[���ʁ�����*/
#define P_HEIGHT 100
#define P_WIDTH 100
#define P_INNBOX 0.2
#define PlayerSpeed 3
#define JumpPower (-1) * 20
#define LIFE_NUM 5
#define P_DWAIT 3000

#define CM_ADJUST 200

/*�������v���C���[1������*/
#define C_PL1 0x00FFFF

#define N_BOTX 40
#define N_LENGTH 110
#define N_RANGE 10
#define N_CRT 20
#define NMOV_B 5.
#define NMOV_W 5.
#define NMOV_A 15.
#define NMOV_TOTAL NMOV_B+NMOV_W+NMOV_A
#define NMOV_E 5.
#define N_DAM 120
#define N_DAMCRT 25 // 0 <= x <= 100

/*�������v���C���[2������*/
#define C_PL2 0xFF00FF

#define C_BLN 0xFF0000
#define C_BLH 0xFFFFFF
#define BCRMAX 20
#define BCRMID 10
#define BCRMIN 5
#define B_RANGE 15
#define B_FRICT 0.05 // 0 <= x <= 1
#define B_STOPX 0.001
#define B_ELAST 0.6 // 0 <= x <= 1
#define B_STOPY_FRAME 120
#define B_DAM 180
#define B_DAMCRT 25 // 0 <= x <= 100

#define ThrowPower (-1) * 20
#define ThrowAngle 45 // 0 <= �� <= 90
#define ThrowVX ThrowPower * cos(M_PI * ThrowAngle / 180)
#define ThrowVY ThrowPower * sin(M_PI * ThrowAngle / 180)
#define CATCH_RANGE 100
#define CATCH_SPEED 0.3 // 0 <= x <= 1

/*�������G�I�u�W�F�N�g������*/
#define ENE_MAX 20
#define C_ENE 0x00FF00
#define EHP_FSIZE 30
#define E_SPEED 1
#define E_DWAIT 500
#define E_DESC 2000
#define E_CLEAR 300
#define E_DRAWMAX 100

#define E_DATA_WALKS_SIZE 100
#define E_DATA_WALKS_SPEED 1
#define E_DATA_WALKS_DESC 2000
#define E_DATA_WALKS_SCpHP 0.3
#define E_DATA_WALKS_SCDST 600

#define E_DATA_MINIS_SIZE 100
#define E_DATA_MINIS_SPEED 2
#define E_DATA_MINIS_DESC 1300
#define E_DATA_MINIS_SCpHP 0.7
#define E_DATA_MINIS_SCDST 800

/*�������w�i�̍��W��������*/
#define BGL_GRID 100
#define BGL_CDEL 0.5 // 0 <= x <= 1
#define C_BGL 0x555555


// �S�I�u�W�F�N�g�̓���K��\����
typedef struct{
	double x, y, // ���S�̍��W
		   h, w, // ����̏c���A����
		   t;	 // ��]�p
	int tg; // �ŗL�^�O
	int st;  // �ŗL�X�e�[�^�X
}POSI;

//�G�I�u�W�F�N�g�p�\����
typedef struct{
	double x, y,
		   h, w,
	       vx, vy;
	unsigned int c;
	int ff;
	char ty;
	int hp;
}E_POSI;

// ���@�\POSI�^
typedef struct{
	double x, y, // ���S�̍��W
		   h, w, // ����̏c���A����
		   t;	 // ��]�p
	unsigned int c; // �F
	int ff; // �t�B���t���O
	char tg; // �ŗL�^�O
	int st;  // �ŗL�X�e�[�^�X
}MULTI_POSI;

// �������֐�
void Init(){
	ChangeWindowMode(TRUE);
	SetGraphMode(WIDTH, HEIGHT, 32);
	if(DxLib_Init() == -1) exit(-1);
}

// ���@�\POSI�^�̒��g����ׂĕ\������֐�
void printMULTI_POSI(MULTI_POSI a){
	printfDx("x : %.0lf, ", a.x);
	printfDx("y : %.0lf, ", a.y);
	printfDx("h : %.0lf, ", a.h);
	printfDx("w : %.0lf, ", a.w);
	printfDx("t : %.0lf, ", a.t);
	printfDx("c : %06x, ", a.c);
	printfDx("t : %d, ", a.ff);
	printfDx("tg: %c ( %d ), ", a.tg, (int)(a.tg));
	printfDx("st: %d\n\n", a.st);
}

// �p�x�����W�A���ɕϊ�����֐� ( rad(180) = �� )
double rad(double angle){
	return M_PI * angle / 180;
}

/*�p�^�[�����[�J�[*/
// r:  0<= | ---000+++ | <=8
// l:  0<= | +++000--- | <=8
// u:  0<= | -0+-0+-0+ | <=8
// d:  0<= | +0-+0-+0- | <=8
int P_Maker(char c, int n){ // n = 0 �` 8
	if(c == 'r') return         n / 3 - 1 ;
	if(c == 'l') return (-1) * (n / 3 - 1);
	if(c == 'u') return         n % 3 - 1 ;
	if(c == 'd') return (-1) * (n % 3 - 1);/*
	if(c == 's') return        (n % 3 - 1) * ((((n / 3) % 2) * 2 - 1) * (-1));
	if(c == 'z') return (-1) * (n % 3 - 1) * ((((n / 3) % 2) * 2 - 1) * (-1));*/
}

// �΂�u�~�v��`�悷��֐�
void DrawCrossAA(double x, double y, //���S�̍��W
				 double a,   //�X���p�x
				 double r,   //���a
				 int color){
	r /= sqrt(2);
	a = rad(a + 45);
	DrawLineAA(x - r * cos(a), y - r * sin(a), x + r * cos(a), y + r * sin(a), color);
	DrawLineAA(x + r * sin(a), y - r * cos(a), x - r * sin(a), y + r * cos(a), color);
}

// ����̕������������O�p�`��`�悷��֐�
void DrawEQTriangle(double x, double y, //���S�̍��W
					double a, //�����p�x
					double len, //�ӂ̒���
					int color, int FillFlag){
	int n = M_PI * 2/3;
	
	len /= sqrt(3);
	a = rad(a);
	DrawTriangleAA(x + len * cos(a)  , y + len * sin(a),
				   x + len * cos(a+n), y + len * sin(a+n),
				   x + len * cos(a-n), y + len * sin(a-n),
				   color, FillFlag);
}

// ��]�֐�
void Rotation(double px, double py,   // ��]�̒��S
			  double *tx, double *ty, // ��]�Ώ�
			  double a){ //��]�p�x
	double d, t;
	
	d = sqrt(pow(px - *tx, 2) + pow(py - *ty, 2));
	t = atan2(*ty - py, *tx - px);
	if(*ty - py / *tx - px > ATAN_FILTER) t = rad(90);
	if(*ty - py / *tx - px > ATAN_FILTER) t = rad(-90);
	
	*tx = px + d * cos(t + rad(a));
	*ty = py + d * sin(t + rad(a));
}

// �p�x�t���ȉ~�`��֐�
void DrawOvalAAplus(float x, float y, float rx, float ry, double angle, int posnum, unsigned int color, int FillFlag){
	int i;
	double *nx, *ny;
	nx = (double*)malloc(sizeof(double) * posnum);
	ny = (double*)malloc(sizeof(double) * posnum);
	for(i = 0; i < posnum; i++){
		nx[i] = rx * cos(2. * M_PI * i / posnum);
		ny[i] = ry * sin(2. * M_PI * i / posnum);
		Rotation(0, 0, &nx[i], &ny[i], angle);
	}
	for(i = 0; i < posnum; i++){
		DrawLineAA(x + nx[i % posnum], y + ny[i % posnum], x + nx[(i + 1) % posnum], y + ny[(i + 1) % posnum], color);
		if(FillFlag){
			DrawQuadrangle(x + nx[ i      % posnum], y + ny[ i      % posnum],
					       x + nx[(i + 1) % posnum], y + ny[(i + 1) % posnum],
						   x + nx[(i + 2) % posnum], y + ny[(i + 2) % posnum],
						   x, y, color, TRUE);
		}
	}
	free(nx); free(ny);
}

int MixColor(int c1, int c2,
			 double r1, double r2 //�F1:�F2�̊��� ex) 1:4
			 ){
	int r, g, b;
	double mr1, mr2;
	
	mr1 = r1 / (r1 + r2);
	mr2 = r2 / (r1 + r2);
	
	r = (int)(c1 / 0x010000            * mr1 + c2 / 0x010000            * mr2);
	g = (int)(c1 % 0x010000 / 0x000100 * mr1 + c2 % 0x010000 / 0x000100 * mr2);
	b = (int)(c1            % 0x000100 * mr1 + c2            % 0x000100 * mr2);
	
	return GetColor(r, g, b);
}

enum DIRECTION{ //�����w��
	D_LEFT, D_RIGHT
};

enum {
 STATE_TITLE,
 STATE_MAIN,
 STATE_ENDING,
 STATE_END,
 STATE_GAMEOVER,
};

// �f�[�^�ǂݍ��݊֐�
int Load(MULTI_POSI *map, MULTI_POSI *ene, int *m_length, int *clock_max);

int GameMain(int *score);

int KeyInputs(char *KeyBuf,
			  POSI *player1, int *J_count1, int *J_stop1,
			  POSI *player2, int *J_count2, int *J_stop2,
			  POSI *ball, int *catch_flag, int *needle_flag,
			  int *camera_main, int *camera_main_stop);

int CheckTouchUp(POSI a, POSI b);
int CheckTouchDown(POSI a, POSI b);
int CheckTouchRight(POSI a, POSI b);
int CheckTouchLeft(POSI a, POSI b);
int CheckTouchAll(POSI a, POSI b);

//a:player, b:�����̕�
int CheckTouch(POSI a, POSI b, char n);

void ChangePOSI(POSI *map, MULTI_POSI *L_map);

int Options();

TouchMap(POSI *player, POSI *map, int *J_count);
TouchMapEnemy(E_POSI *enemy, POSI *map);
TouchMapBall(POSI *ball, POSI *map, int *e_time1, int *e_time2 ,int se);