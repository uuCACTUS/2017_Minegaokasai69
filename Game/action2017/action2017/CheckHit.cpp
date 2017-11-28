#include "hoge.h"

/*
			//天井
			else if( (player1.x + player1.w/2 >= map[i].x - map[i].w/2) && (player1.x - player1.w/2 <= map[i].x + map[i].w/2)
				  && (player1.y - player1.h/2 <= map[i].y + map[i].h/2) && (player1.y - player1.h/2 >= map[i].y + map[i].h/2 - WALL_DEPTH)
				  && player1.st < 0)
			{
				player1.y = map[i].y	+ map[i].h/2 + player1.h/2;
				player1.st = 0;
			}
			//接地
			if( (player1.x + player1.w/2 >= map[i].x - map[i].w/2) && (player1.x - player1.w/2 <= map[i].x + map[i].w/2)
			 && (player1.y + player1.h/2 >= map[i].y - map[i].h/2) && (player1.y + player1.h/2 <= map[i].y - map[i].h/2 + WALL_DEPTH)
			 && player1.st > 0)
			{
				player1.y = map[i].y	- map[i].h/2 - player1.h/2;
				player1.st = 0;
				J_count = 0;
			}
			//壁(右側)
			else if( (player1.y + player1.h/2 >= map[i].y - map[i].h/2) && (player1.y - player1.h/2 <= map[i].y + map[i].h/2)
				  && (player1.x + player1.w/2 >= map[i].x - map[i].w/2) && (player1.x + player1.w/2 <= map[i].x - map[i].w/2 + WALL_DEPTH) )
			{
				player1.x = map[i].x	- map[i].w/2 - player1.w/2;
			}
			//壁(左側)
			else if( (player1.y + player1.h/2 >= map[i].y - map[i].h/2) && (player1.y - player1.h/2 <= map[i].y + map[i].h/2)
				  && (player1.x - player1.w/2 <= map[i].x + map[i].w/2) && (player1.x - player1.w/2 >= map[i].x + map[i].w/2 - WALL_DEPTH) )
			{
				player1.x = map[i].x	+ map[i].w/2 + player1.w/2;
			}
*/

int CheckTouchUp(POSI a, POSI b)
{
 if ((a.x + a.w/2 >= b.x - b.w/2) && (a.x - a.w/2 <= b.x + b.w/2)
  && (a.y - a.h/2 <= b.y + b.h/2) && (a.y - a.h/2 >= b.y + b.h/2 - WALL_DEPTH))
  return 1;
 return 0;
}

int CheckTouchDown(POSI a, POSI b)
{
 if ((a.x + a.w/2 >= b.x - b.w/2) && (a.x - a.w/2 <= b.x + b.w/2)
  && (a.y + a.h/2 >= b.y - b.h/2) && (a.y + a.h/2 <= b.y - b.h/2 + WALL_DEPTH))
  return 1;
 return 0;
}

int CheckTouchRight(POSI a, POSI b)
{
 if ((a.y + a.h/2 >= b.y - b.h/2) && (a.y - a.h/2 <= b.y + b.h/2)
  && (a.x + a.w/2 >= b.x - b.w/2) && (a.x + a.w/2 <= b.x - b.w/2 + WALL_DEPTH))
  return 1;
 return 0;
}

int CheckTouchLeft(POSI a, POSI b)
{
 if ((a.y + a.h/2 >= b.y - b.h/2) && (a.y - a.h/2 <= b.y + b.h/2)
  && (a.x - a.w/2 <= b.x + b.w/2) && (a.x - a.w/2 >= b.x + b.w/2 - WALL_DEPTH))
  return 1;
 return 0;
}

int CheckTouchAll(POSI a, POSI b)
{
 if ((a.y - a.h/2 <= b.y + b.h/2) && (a.y + a.h/2 >= b.y - b.h/2)
  && (a.x + a.w/2 >= b.x - b.w/2) && (a.x - a.w/2 <= b.x + b.w/2))
  return 1;
 return 0;
}

//a:player, b:何かの物
int CheckTouch(POSI a, POSI b, char n)
{
 int touch_flag = 0;
 int cu, cd, cl, cr, ca;

 cu = CheckTouchUp(a, b);
 cd = CheckTouchDown(a, b);
 cl = CheckTouchLeft(a, b);
 cr = CheckTouchRight(a, b);
 ca = CheckTouchAll(a, b);

 switch (n) {
 case 'u': touch_flag = cu;
  break;
 case 'd': touch_flag = cd;
  break;
 case 'r': touch_flag = cr;
  break;
 case 'l': touch_flag = cl;
  break;
 case 'a': touch_flag = ca;

  return touch_flag;

 }
}

TouchMap(POSI *player, POSI *map, int *J_count){
	//接地
	if( CheckTouchDown(*player, *map) && player->st > 0)
	{
		player->y = map->y - map->h/2 - player->h/2;
		player->st = 0;
		*J_count = 0;
	}
	//壁(左側)
	else if( CheckTouchLeft(*player, *map) )
	{
		player->x = map->x + map->w/2 + player->w/2;
	}
	//壁(右側)
	else if( CheckTouchRight(*player, *map) )
	{
		player->x = map->x - map->w/2 - player->w/2;
	}
	//天井
	else if( CheckTouchUp(*player, *map) && player->st < 0)
	{
		player->y = map->y + map->h/2 + player->h/2;
		player->st = 0;
	}
	
}

TouchMapEnemy(E_POSI *enemy, POSI *map){
	POSI fuge;
	
	fuge.x = enemy->x;
	fuge.y = enemy->y;
	fuge.h = enemy->h;
	fuge.w = enemy->w;
	
	//接地
	if( CheckTouchDown(fuge, *map) && enemy->vy > 0)
	{
		enemy->y = map->y - map->h/2 - enemy->h/2;
		enemy->vy = 0;
	}
	//壁(左側)
	else if( CheckTouchLeft(fuge, *map) )
	{
		enemy->x = map->x + map->w/2 + enemy->w/2;
		enemy->vx *= -1;
	}
	//壁(右側)
	else if( CheckTouchRight(fuge, *map) )
	{
		enemy->x = map->x - map->w/2 - enemy->w/2;
		enemy->vx *= -1;
	}
	//天井
	else if( CheckTouchUp(fuge, *map) && enemy->vy < 0)
	{
		enemy->y = map->y + map->h/2 + enemy->h/2;
		enemy->vy = 0;
	}
	
}

TouchMapBall(POSI *ball, POSI *map, int *e_time1, int *e_time2, int se){
	POSI some;
	double speed;
	
	speed = sqrt( pow(ball->h, 2) + pow(ball->w, 2) );
	
	some.x = ball->x;
	some.y = ball->y;
	some.h = ball->t * 2;
	some.w = ball->t * 2;
	
	//接地
	if( CheckTouchDown(some, *map) && ball->h > 0)
	{
		if(speed>=BCRMIN)
		PlaySoundMem(se, DX_PLAYTYPE_BACK,TRUE);
		ball->y = map->y - map->h/2 - ball->t;
		ball->h *= -1 * B_ELAST;
		*e_time1 = *e_time2;
		*e_time2 = GetNowCount();
		ball->tg = 1;
	}
	//壁(左側)
	if( CheckTouchLeft(some, *map) )
	{
		if(speed>=BCRMIN)
		PlaySoundMem(se, DX_PLAYTYPE_BACK,TRUE);
		ball->x = map->x + map->w/2 + ball->t;
		ball->w = -1 * ball->w;
	}
	//壁(右側)
	if( CheckTouchRight(some, *map) )
	{
		if(speed>=BCRMIN)
		PlaySoundMem(se, DX_PLAYTYPE_BACK,TRUE);
		ball->x = map->x - map->w/2 - ball->t;
		ball->w = -1 * ball->w;
	}
	//天井
	if( CheckTouchUp(some, *map) && ball->h < 0)
	{
		if(speed>=BCRMIN)
		PlaySoundMem(se, DX_PLAYTYPE_BACK,TRUE);
		ball->y = map->y + map->h/2 + ball->t;
		ball->h = 0;
	}
	
}