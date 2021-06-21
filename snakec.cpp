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

void draw(S * s, F * f) {
	P t = {50,20};
	gotoxy(t);
	printf("d : %c", s->d);
	
	P p = {1,0};
	gotoxy(p);
	printf("%dÁ¡",s->point); 
	
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
	printf("¡Ü"); 
	
	P o = {50,10};
	gotoxy(o);
	printf("hN:%02d", s->h);
	
	if(s->xys[s->h].x == f->pos.x && s->xys[s->h].y == f->pos.y) {
		f->pos.x = (rand()%10)*2;
		f->pos.y = rand()%30;
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
	printf("¡Ü");
	gotoxy(s.xys[s.h]);
	printf("¡Ü");
	
	char k;
	char gameover = TRUE;
	
	while(gameover) {	
		Sleep(200);
		
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
		
		if((s.xys[s.h].y < 0 || s.xys[s.h].y > 29) || (s.xys[s.h].x < 0 || s.xys[s.h].x > 58)) {
			gameover = FALSE;
		}
		
		if(sbreak(s.t, &s)) {
			gameover = FALSE;
		}
	}
	
	system("cls");
	printf("GAME OVER");
	
	return 0;
}
