#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#define TabSize 3
char board[TabSize][TabSize];

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
	for (unsigned int i=0; i<TabSize; i++) {
		for (unsigned int j=0; j<TabSize; j++) {
			board[i][j] = '0';
		}
	}
}

void display(char* val) {
    for (int i=0; i<TabSize; i++) {
        printw(val);
    }
}

void display_board() {
    int count=1;
	move(0, 0);
	printw("============= TIC TAC TOE =============\n");
	printw("=======================================\n");
	for (int i=0; i<TabSize; i++) {
		display("+ - - - - - - - - ");
        printw("+\n|");

        for (int i=0; i<TabSize; i++) {
            printw(" %i %15 |", count);
            count++;
        }

        printw("\n");
		printw("|");
		for (int j=0; j<TabSize; j++) {
            if (board[i][j] != '0'){
                printw("%9c", board[i][j]);
                printw("%9|");
            }
            else {
                printw("%18|");
            }
		}
        printw("\n|");
		display(" %17 |");
        printw("\n");
        
	}
    display("+ - - - - - - - - ");
    printw("+\n");
	refresh();
}

int count_TabCase() {
    int count=TabSize*TabSize;
    for (int i=0; i<TabSize; i++) {
        for (int j=0; j<TabSize; j++) {
            if (board[i][j]=='X' || board[i][j]=='O') {
                count--;
            }
        }
    }
    return count;
}

int play(int dir) {
    if (dir==127){
        printw("=========== (press a key) ===========");
        getch();
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

int game() {
    if (!count_TabCase()) {
        printw("============= Game Over =============\n");
		printw("=========== (press a key) ===========");
        getch();
        return 1;
    }

    return 0;
}

int main() {
    INIT_GAME();
    init_board();
    display_board();
    int key = getch();
    int playing=1;
    while (!game()) {
        playing = play(key);
        key=getch();
    }
    DONE_GAME();
}