#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define ROW 20
#define COLUMN 40
int i, j, t, x, y, dir, d, tail, head, r1, r2;
int game = 0;
int snake[ROW][COLUMN];
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void Field()
{
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			if (i == 0)
			{
				if (j == 0)
					printf("ùÝ");
				else if (j == COLUMN - 1)
					printf("ùß");  
				else
					printf("ùù");
			}
			else if (i == ROW - 1)
			{
				if (j == 0)
					printf("ùã");
				else if (j == COLUMN - 1)
					printf("ùå");
				else
					printf("ùù");
			}
			else
			{
				if (j == 0 || j == COLUMN - 1)
					printf("ùø");
				else if(snake[i][j]>0){
					if(snake[i][j]==head)
						printf("O");
					else
						printf("o",snake[i][j]);
				}
				else if(snake[i][j]==-1)
					printf("*");
				else
					printf(" ",snake[i][j]);
			}
		}
		printf("\n");
	}
}
int getch_noblock(){
	if(_kbhit())
		return _getch();
	else 
		return -1;
}
void random(){
	while(snake[r1][r2] > 0 || snake[r1][r2] != -1){
		srand(time(NULL));
		r1 = rand()%(ROW-2)+1;
		srand(time(NULL));
		r2 = rand()%(COLUMN-2)+1;
		snake[r1][r2] = -1;
	}
}
void refresh(){
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut,Position);
}
void Movement(){
	t = tolower(getch_noblock());
	switch(t){
		case 'd':
			if(dir == 3)
				break;
			else
				dir = 1;
			break;
		case 's':
			if(dir == 4)
				break;
			else
				dir = 2;
			break;
		case 'a':
			if(dir == 1)
				break;
			else
				dir = 3;
			break;
		case 'w':
			if(dir == 2)
				break;
			else
				dir = 4;
			break;
	}
	switch(dir){
		case 1:
			head++;
			y++;
			if(y == COLUMN - 1)
				y = 1;
			else if(snake[x][y] > 0)
				game = 1;
			snake[x][y] = head;
			break;
		case 2:
			head++;
			x++;
			if(x == ROW - 1)
				x = 1;
			else if(snake[x][y] > 0)
				game = 1;
			snake[x][y] = head;
			break;
		case 3:
			head++;
			y--;
			if(y == 0)
				y = COLUMN-2;
			else if(snake[x][y] > 0)
				game = 1;
			snake[x][y] = head;
			break;
		case 4:
			head++;
			x--;
			if(x == 0)
				x = ROW - 2;
			else if(snake[x][y] > 0)
				game = 1;
			snake[x][y] = head;
			break;
		}
}
void invisible(){
	for(i = 0; i < ROW; i++)
		for(j = 0; j < COLUMN; j++){
			if(snake[i][j] == tail)
				snake[i][j] = 0;
		}
	tail++;
}
void initial()
{
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			snake[i][j] = 0;
		}
	}
	x = ROW/2;
	y = COLUMN/2;
	tail = 1;
	r1 = 0;
	r2 = 0;
	head = 5;
	game = 0;
	for(i = 0; i < head; i++){
		snake[x][y+i+1-head] = i+1;
	}
}
int main(int argc, char *argv[])
{	
	while(1){
	initial();
	random();
	Field();
	printf("Press SPACE to start\n");
	printf("Using W,A,S,D to control it");
	while(1){
		if(_kbhit() && _getch()==32)
			break;
		Sleep(100);
	}
	system("cls");
	dir = 1;
	while(game == 0){
		while(snake[x][y] == snake[r1][r2]){
			random();
			tail--;
		}
		Movement();
		invisible();
		Field();
		refresh();
		Sleep(60);
	}
	}
	
	
	return 0;
}
