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

        for (int k=0; k<TabSize; k++) {
            printw(" %i %15 |", count);
            count++;
        }

		printw("\n|");
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

int check_row(int i) {
    if (board[i][0]!='0' && board[i][0]==board[i][1] && board[i][1]==board[i][2]) {
        if (board[i][0]=='X') {
            return 1;
        }
        else {
            return 2;
        }
    }
    return 0;
}

int check_col(int j) {
    if (board[0][j]!='0' && board[0][j]==board[1][j] && board[1][j]==board[2][j]) {
        if (board[0][j]=='X') {
            return 1;
        }
        else {
            return 2;
        }
    }
    return 0;
}

int check_diagonal() {
    if (board[0][0]!='0' && board[0][0]==board[1][1] && board[1][1]==board[2][2]) {
        if (board[1][1]=='X') {
            return 1;
        }
        else {
            return 2;
        }
    }
    if (board[0][2]!='0' && board[0][2]==board[1][1] && board[1][1]==board[2][0]) {
        if (board[1][1]=='X') {
            return 1;
        }
        else {
            return 2;
        }
    }
    return 0;
}

int check_win() {
    for (int i=0; i < TabSize; i++) {
        if (check_row(i)==1 || check_col(i)==1) {
            return 1;
        }
        else if (check_row(i)==2 || check_col(i)==2) {
            return 2;
        }
    }
    if (check_diagonal()==1) {
        return 1;
    }
    else if (check_diagonal()==2) {
        return 2;
    }
    return 0;
}

void bot_play_random() {
    int n = rand() %  count_TabCase();
    for (unsigned int i=0; i<TabSize; i++) {
		for (int j=0; j<TabSize; j++) {
			if (board[i][j]=='0') {
				if (n) {
					n--;
				}
				else {
					board[i][j] = 'O';
					return;
				}
			}
		}
	}
}

void bot_play() {
    for (int i=0; i<TabSize; i++) {
        for (int j=0; j<TabSize; j++) {
            if (board[i][j]=='0') {
                board[i][j] = 'O';
                if (check_win()==2) {
                    return;
                }
                board[i][j]='0';
            }
        }
    }
    for (int i=0; i<TabSize; i++) {
        for (int j=0; j<TabSize; j++) {
            if (board[i][j]=='0') {
                board[i][j] = 'X';
                if (check_win()==1) {
                    board[i][j] = 'O';
                    return;
                }
                board[i][j]='0';
            }
        }
    }
    bot_play_random();
}

int play(int dir) {
    if (dir==127){
        printw("=============== FORFATE ===============\n");
	    printw("============ (press a key) ============");
        getch();
        DONE_GAME();
        return 0;
    }

    int case_played = (dir+1 - 49);
    for (int i=0; i<TabSize; i++) {
        for (int j=0; j<TabSize; j++) {
            case_played--;
            if (!case_played && board[i][j]=='0') {
                board[i][j] = 'X';
                return 1;
            }
        }
    }
    return 0;
}

int game() {
    if (!count_TabCase() && !check_win()) {
        printw("================== NULL ================\n");
		printw("============= (press a key) ============");
        display_board();
        getch();
        return 1;
    }
    else if (check_win()==1){
        printw("=============== Game WON =============\n");
		printw("============ (press a key) ===========");
        display_board();
        getch();
        return 1;
    }
    else if (check_win()==2) {
        printw("============= Game Over =============\n");
		printw("=========== (press a key) ===========");
        display_board();
        getch();
        return 1;
    }
    display_board();
    return 0;
}

int main() {
    INIT_GAME();
    init_board();
    display_board();
    int Play=1;
    int Game=0;
    while (!Game) {
        Play = play(getch());
        Game=game();
        if (Play && !Game) {
            bot_play();
            Game=game();
        }
        display_board();
    }
    DONE_GAME();
}