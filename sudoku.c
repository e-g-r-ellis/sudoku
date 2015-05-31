#include <stdlib.h>
#include <stdio.h>

const int N_DIGITS = 9;
const int LINE_SIZE = 20;

struct Sudoku {
	int *data;
	int size;
};

struct Sudoku *newSudoku(int size) {
	struct Sudoku *puzzle = (struct Sudoku *)calloc(1, sizeof(struct Sudoku));
	puzzle->data = calloc(size * size, sizeof(int));
	puzzle->size = size;
	return puzzle;
}

void printSudoku(struct Sudoku *puzzle) {
	printf("Sudoku:\n");
	int x,y;
	int *value;
	for (y = 0; y < puzzle->size; y++) {
		for (x = 0; x < puzzle->size; x++) {
			value = puzzle->data + (y * puzzle->size + x);
			if (*value != 0) {
				printf("%d", *value);
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
}

void readSudoku(struct Sudoku *puzzle) {
	char line[LINE_SIZE];
	int i, y, x;
	for (y = 0; y < puzzle->size; y++) {
		fgets(line, LINE_SIZE, stdin);
		for (x = 0; x < puzzle->size; x++) {
			int *value = puzzle->data + (puzzle->size * y) + x;
			switch (line[x]) {
			case '1':
				*value = 1;
				break;
			case '2':
				*value = 2;
				break;
			case '3':
				*value = 3;
				break;
			case '4':
				*value = 4;
				break;
			case '5':
				*value = 5;
				break;
			case '6':
				*value = 6;
				break;
			case '7':
				*value = 7;
				break;
			case '8':
				*value = 8;
				break;
			case '9':
				*value = 9;
				break;
			case '.':
				*value = 0;
				break;
			case '\n':
				break;
			default:
				fprintf(stderr, "Did not expect '%c'.\n", line[x]);
				fflush(stderr);
				return;
			}
		}
	}
}

int main(int argc, char **argv) {
	struct Sudoku *puzzle = newSudoku(9);
	printSudoku(puzzle);
	readSudoku(puzzle);
	printSudoku(puzzle);
	fflush(stderr);
	// Read sudoku
	// While not complete
		// Solve sudoku
		// Print sudoku
	return 0;
}
