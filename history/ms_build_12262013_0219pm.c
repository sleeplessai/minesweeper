#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define refresh() system("cls")
int bomb[12][12], count[12][12], ok = 1;
const int bomb_n = 15;
char display[12][12];

void display_grids() {
	int i, j; // i->y j->x
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j)
			putchar(display[i][j]);
		putchar('\n');
	}
}

void init_bomb() {
	memset(bomb, 0, sizeof(bomb));
	int t = bomb_n;
	while (--t) {
		int x = rand() % 10, y = rand() % 10;
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
			if (bomb[i][j] == 1) for (d = 0; d < 8; ++d) {
					int m = i + dx[d], n = j + dy[d];
					++count[m][n];
			}
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
	if (bomb[x][y] == 1) {
		display[x][y] = '*';
		ok = 0;
	}
}

void sign_grid(int x, int y) {
	display[x][y] = display[x][y] == '!' ? '#' : '!';
}

int check_game_state() {
	if (bomb_n == 0) return 1;
	if (!ok) return 2;
	else return 0;
}

void print() {
	int i, j;
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j)
			printf("%d", bomb[i][j]);
		putchar('\n');
	}
}

int main(int argc, char *argv[]) {
	refresh();
	init();
	display_grids();
	// print();
	// following valables makes up a collection of commandes.
	char cmd;
	int x, y;
	while (1) {
		printf("please input the next command \n(\n\"d x y\" dig (x,y);\n\"s x y\" sign (x,y);\n\"e\" exit game\n)::");
		cmd = getchar();
		switch (cmd) {
		case 'd':
			scanf("%d %d", &x, &y);
			dig_grid(y, x);
			break;
		case 's':
			scanf("%d %d", &x, &y);
			sign_grid(y, x);
			break;
		case 'q':
		case 'e':
			refresh();
			printf("Game ended!\n");
			system("pause");
			return 0;
		}
		refresh();
		display_grids();
		int situ = check_game_state();
	}

	return 0;
}


