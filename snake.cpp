#include <stdio.h>
#include <windows.h>
#include <conio.h>

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
};

void gotoxy(P p) {
	COORD Pos={p.x, p.y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw(S * s) {
	gotoxy(s->xys[s->t]);
	printf("  ");
	s->t++;
	
	s->xys[s->h+1].x = s->xys[s->h].x+2;
	s->xys[s->h+1].y = s->xys[s->h].y;
	s->h++;
	
	gotoxy(s->xys[s->h]);
	printf("¡Ü"); 
}

int main() {
	system("mode con: cols=60 lines=30");
	system("COLOR F0");
	
	P p1={2,15}, p2={4,15};
	S s;
	s.d = 'R';
	s.h = 1;
	s.t = 0;
	s.xys[s.t] = p1;
	s.xys[s.h] = p2;
	
	gotoxy(s.xys[s.t]);
	printf("¡Ü");
	gotoxy(s.xys[s.h]);
	printf("¡Ü");
	
	while(1) {	
		Sleep(200);
	
		draw(&s);
	}
	
	return 0;
}
