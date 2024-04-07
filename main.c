#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#define TabSize 3
char board[TabSize][TabSize];

// ONE = 49

void INIT_GAME() {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	srand(time(NULL));
}

void DONE_GAME() {
	endwin();
	exit(0);
}

void init_board() {
    char count='1';
	for (unsigned int i=0; i<TabSize; i++) {
		for (unsigned int j=0; j<TabSize; j++) {
			board[i][j] = count;
            count++;
		}
	}
}

void display_board() {
	move(0, 0);
	printw("============= TIC TAC TOE =============\n");
	printw("=======================================\n");
	for (unsigned int i=0; i<TabSize; i++) {
		printw("+ - - - - - - - - + - - - - - - - - + - - - - - - - - +\n");
		printw("| %17 | %17 | %17 |\n");
		printw("|");
		for (unsigned int j=0; j<TabSize; j++) {
            printw("%9c", board[i][j]);
            printw("%9|");
		}
		printw("\n| %17 | %17 | %17 |\n");
	}
	printw("+ - - - - - - - - + - - - - - - - - + - - - - - - - - +\n");
	refresh();
}

int play(int dir) {
    if (dir==127){
        DONE_GAME();
        return 0;
    }

    int count = (dir+1 - 49);
    for (int i=0; i<TabSize; i++) {
        for (int j=0; j<TabSize; j++) {
            count--;
            if (!count && (board[i][j]!='X' || board[i][j]!='O')) {
                board[i][j] = 'X';
                display_board();
                return 1;
            }
        }
    }
    return 0;
}

int victory() {
    return 0;
}

int main() {
    INIT_GAME();
    init_board();
    display_board();
    int key = getch();
    int playing=1;
    while (!victory()) {
        playing = play(key);
        key=getch();
    }
    DONE_GAME();
}