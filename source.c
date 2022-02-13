#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// maybe move some of these functions to a header file later?

#define board_size 10

typedef struct {		// any given board, easier to pass into functions like this
	int b[board_size][board_size];
}board;

board dead_state();										// initialise a dead board state
board rand_state();										// randomise a starting board state
board tick(board current);								// moves the state forward one tick
board count(board curr);								// counts the things
void render(board printable);							// print to terminal, but make it pretty
void row();												// prints a row (in render())
int xadd(int i, int a);									// add to a width index, wrapping around like a cylinder
int yadd(int i, int a);									// add to a height index, wrapping around 
int adjacent_to(int board[][board_size], int i, int j);	// return the number of on cells adjacent to the i,j cell


void main() {
	board test_board = rand_state();
	render(test_board);
}

board dead_state() {
	// generate the matrix, set all values to 0, return
	board deadboard;

	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			deadboard.b[i][j] = 0;
		}
	}

	return deadboard;
}

board rand_state() {
	srand(time(NULL));

	board soup = dead_state();		// cause a soup is a random starting board, apparently

	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			int r = rand() % 10;
			if (r > 5) {			// just % 2 didn't work, so here we go
				soup.b[i][j] = 0;
			}
			else {
				soup.b[i][j] = 1;
			}
		}
	}

	return soup;
}

board tick(board current) {		
	board next_tick = dead_state();		// the next tick of the board
	board counting = count(current);

	
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; i < board_size; j++) {
			switch (counting.b[i][j]) {
				case 2, 3
			}
		}
	}
	
	// check against count_board and put into next_tick

}

board count (board curr) {
	board count = dead_state();

	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			count.b[i][j] = adjacent_to(curr.b, i, j);
		}
	}

	return count;
}

void render(board printable) {
	row();						// top row
	printf("\n");

	for (int i = 0; i < board_size; i++) {
		printf("| ");
		for (int j = 0; j < board_size; j++) {
			if (printable.b[i][j] == 1) {		// check if square is live or not
				printf(" # ");
			}
			else {
				printf("   ");
			}
		}
		printf(" |\n");
	}

	row();
}

void row() {
	for (int i = 0; i < board_size + 1; i++) {
		printf("---");
	}
	printf("-");
}

int xadd(int i, int a) {
	i += a;
	while (i < 0) {
		i += board_size;		// using the board_size as an offset
	}
	while (i >= board_size) {
		i -= board_size;		
	}
	return i;
}

int yadd(int i, int a) {
	i += a;
	while (i < 0) {
		i += board_size;
	}
	while (i >= board_size) {
		i -= board_size;
	}
	return i;
}

int adjacent_to(int board[][board_size], int i, int j) {
	int	k, l, no_live;
	no_live = 0;

	// go around the cell
	for (k = -1; k <= 1; k++) {
		for (l = -1; l <= 1; l++) {
			// only count if at least one of k, l isn't zero

		if (k || l) {
			if (board[xadd(i, k)][yadd(j, l)]) {
				no_live++;
			}
		}
		}
	}

	return no_live;
}
