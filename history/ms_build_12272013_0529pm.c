#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define refresh() system("cls")
#define pause() system("pause")
int bomb[12][12], count[12][12], bomb_n = -1;
char display[12][12];

void display_grids() {
	int i, j; // i->y j->x
	printf("%25s\n", "Minesweeper - gamming");
	for (i = 0; i < 15; ++i) {
		if (i < 4)
			putchar(' ');
		else if (i > 4)
			printf("%d", i - 5);
	}
	printf(" (X)\n   +");
	for (i = 0; i < 10; ++i) putchar('-');
	printf("+\n");
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 11; ++j) {
			if (!j)
				printf(" %d |", i);
			else
				putchar(display[i][j - 1]);
		}
		printf("|\n");
	}
	printf("(Y)+");
	for (i = 0; i < 10; ++i) putchar('-');
	printf("+\n");
}

void init_bomb() {
	srand((int)time(NULL));
	memset(bomb, 0, sizeof(bomb));
	int t = bomb_n;
	while (t--) {
		int x = rand() % 10, y = rand() % 10;	// rand() % 11 => [0, 10)
		if (!bomb[y][x])
			bomb[y][x] = 1;
		else ++t;
	}
}

void init_count() {
	memset(count, 0, sizeof(count));
	int i, j, d;
	const int dx[] = {0, 0, 1, -1, -1, 1, -1, 1}, dy[] = {1, -1, 0, 0, -1, -1, 1, 1};
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			if (bomb[i][j] == 1) for (d = 0; d < 8; ++d)
				++count[i + dx[d]][j + dy[d]];
		}
	}
}

void init_display() {
	memset(display, '#', sizeof(display));
}

void init() {
	init_display();
	init_bomb();
	init_count();
}

void dig_grid(int x, int y) {
	if (bomb[x][y] == 1 && display[x][y] != '!')
		display[x][y] = '*';
	else if (bomb[x][y] == 0 && display[x][y] != ' ' && display[x][y] != '!' && !(display[x][y] >= '0' && display[x][y] <= '8')) {
		display[x][y] = ' ';
		const int dx[] = { 0, 0, 1, -1, -1, 1, -1, 1 }, dy[] = { 1, -1, 0, 0, -1, -1, 1, 1 };
		int d;
		for (d = 0; d < 8; ++d) {
			int m = x + dx[d], n = y + dy[d];
			if (m > -1 && m < 10 && n > -1 && n < 10 && !bomb[m][n] && display[m][n] != '!') {
				display[m][n] = count[m][n] ? (char)count[m][n] + '0' : ' ';
			}
		}
	}
}

void sign_grid(int x, int y) {
	if (display[x][y] == '!')
		display[x][y] = '#';
	else if (!(display[x][y] >= '0' && display[x][y] <= '8') && display[x][y] != ' ')
		display[x][y] = '!';
}

int check_game_state() {
	int i, j, cnt = 0, tot = 0;
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			switch (display[i][j]) {
			case '#': ++tot; break;
			case '!': if (bomb[i][j]) ++cnt; break;
			case '*': return 2;	// lose! dig a bomb.
			}
		}
	}
	if (cnt == bomb_n && tot == 0) return 1;	// win! all bombs have been sweept.
	else return 0;	// not finished! continue.
}

int main(int argc, char *argv[]) {
	while (!(bomb_n >= 1 && bomb_n <= 99)) {
		refresh();
		printf("%25s\n", "Minesweeper - setting");
		printf("Before beginning, set the number of bomb.\n>> ");
		scanf("%d", &bomb_n);
	}
	printf("The number of bomb is %d. Gook luck!\n", bomb_n);
	pause();
	refresh();
	init();
	display_grids();
	// following valables makes up a collection of commandes.
	char cmd;
	int x, y, ok = 1, i, j;
	while (1) {
		printf("Please type command to play. \n\"d x y\" dig (x,y)  \"s x y\" sign (x,y)\n\"r\" restart \"e\" exit\n>> ");
		if (ok)
			cmd = getchar();
		else {
			cmd = 'r';
			ok = 1;
		}
		switch (cmd) {
		case 'd':
			scanf("%d %d", &x, &y);
			dig_grid(y, x);
			break; 
		case 's':
			scanf("%d %d", &x, &y);
			sign_grid(y, x);
			break;
		case 'r':
			init();
			break;
		case 'q':
		case 'e':
			refresh();
			printf("%23s\n", "Minesweeper - about"); 
			puts("Spix Mojo is the only developer.\nMore information, visit http://www.cppblog.com/mjsz-cppblog.\n");
			pause();
			return 0;
		}
		refresh();
		display_grids();
		switch (check_game_state()) {
		case 1:
			printf("Successed!\nPress any key to play again.\n");
			ok = 0;
			pause();
			break;
		case 2:
			for (i = 0; i < 10; ++i) {
				for (j = 0; j < 10; ++j) {
					if (bomb[i][j] && display[i][j] != '!')
						display[i][j] = '*';
					else if (!bomb[i][j] && display[i][j] == '!')
						display[i][j] = 'X';
				}
			}
			refresh();
			display_grids();
			printf("Failed!\nPress any key to restart.\n");
			ok = 0;
			pause();
			break;
		case 0:
		default:
			continue;
		}
	}

	return 0;
}
