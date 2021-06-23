#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

typedef struct point P;

struct point {
	int x;
	int y;
};

typedef struct snake S;

struct snake {
	char d;
	int h;
	int t;
	P xys[100];
	int point;
};

typedef struct frog F;

struct frog {
	P pos;
	char shape;
};

void gotoxy(P p) {
	COORD Pos={p.x, p.y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void map() {
	P xy = {0,1};
	gotoxy(xy);
	printf("旨");
	xy.x += 2; 
	
	for(int i = 0; i < 28; i++) {
		gotoxy(xy);
		printf("收");
		xy.x += 2;
	}
	gotoxy(xy);
	printf("旬");
	xy.y += 1;
	
	for(int j = 0; j < 27; j++) {
		gotoxy(xy);
		printf("早");
		xy.y += 1; 
	}
	
	gotoxy(xy);
	printf("旭");
	xy.x -= 2;
	
	for(int k = 0; k < 28; k++) {
		gotoxy(xy);
		printf("收");
		xy.x -= 2;
	}
	
	gotoxy(xy);
	printf("曲");
	xy.y -= 1;
	
	for(int l = 0; l < 27; l++) {
		gotoxy(xy);
		printf("早");
		xy.y -= 1; 
	}
}

void draw(S * s, F * f) {
	P t = {10,0};
	gotoxy(t);
	printf("d : %c", s->d);
	
	P p = {1,0};
	gotoxy(p);
	printf("%d薄",s->point);
	
	map(); 
	
	gotoxy(f->pos);
	printf("%c", f->shape);
	
	switch(s->d) {
		case 'R':
			s->xys[s->h+1].x = s->xys[s->h].x+2;
			s->xys[s->h+1].y = s->xys[s->h].y;
			break;
		
		case 'L':
			s->xys[s->h+1].x = s->xys[s->h].x-2;
			s->xys[s->h+1].y = s->xys[s->h].y;
			break;
			
		case 'U':
			s->xys[s->h+1].x = s->xys[s->h].x;
			s->xys[s->h+1].y = s->xys[s->h].y-1;
			break;
			
		case 'D':
			s->xys[s->h+1].x = s->xys[s->h].x;
			s->xys[s->h+1].y = s->xys[s->h].y+1;
			break;
	}
	
	s->h++;
	gotoxy(s->xys[s->h]);
	printf("≒"); 
	
	if(s->xys[s->h].x == f->pos.x && s->xys[s->h].y == f->pos.y) {
		f->pos.x = ((rand()%28) * 2) + 2;
		f->pos.y = (rand()%26) + 3;
		s->point += 1;
	}
	
	else {
		gotoxy(s->xys[s->t]);
		printf("  ");
		s->t++;
	}
}

char sbreak(int s, S * ss) {
	int n = 0;
	
	for(int i = s; ; i++) {
		n = i % 99;
		if(ss->h == n) {
			return FALSE;
		}
		if(ss->xys[ss->h].x == ss->xys[n].x && ss->xys[ss->h].y == ss->xys[n].y) {
			return TRUE;
		}
	}
}

int main() {
	system("mode con: cols=60 lines=30");
	system("COLOR F0");
	
	CONSOLE_CURSOR_INFO cursorInfo = {0,};
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	
	srand(time(NULL));
	
	P p1={2,15}, p2={4,15};
	S s={'R',1,0,p1,p2,0};
	F f={{30,10}, '@'};
	
	gotoxy(s.xys[s.t]);
	printf("≒");
	gotoxy(s.xys[s.h]);
	printf("≒");
	
	char k;
	char gameover = TRUE;
	
	while(gameover) {	
		Sleep(100);
		
		if(kbhit()) {
			k = getch();
			switch(k) {
				case 'w':
					if(s.d != 'D') {
						s.d='U'; 
					}
					break;
					
				case 'd':
					if(s.d != 'L') {
						s.d='R'; 
					}
					break;
					
				case 'a':
					if(s.d != 'R') {
						s.d='L'; 
					}
					break;
					
				case 's':
					if(s.d != 'U') {
						s.d='D'; 
					}
					break;
			}
		}
	
		draw(&s, &f);
		
		s.h = s.h % 99;
		s.t = s.t % 99;
		
		if(s.h == 0 || s.t == 0) {
			s.xys[0] = s.xys[99];
		}
		
		if((s.xys[s.h].y < 2 || s.xys[s.h].y > 28) || (s.xys[s.h].x < 2 || s.xys[s.h].x > 56)) {
			gameover = FALSE;
		}
		
		if(sbreak(s.t, &s)) {
			gameover = FALSE;
		}
		
		if(s.point > 99) {
			gameover = FALSE;
		}
			
	}
	
	system("cls");
	if(s.point > 99) {
		printf("GAME CLEAR!");
	}
	else {
		printf("GAME OVER");
	}
	
	return 0;
}
