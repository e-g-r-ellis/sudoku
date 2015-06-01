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

void freeSudoku(struct Sudoku *puzzle) {
	if (puzzle) {
		free(puzzle->data);
		free(puzzle);
	}
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

struct Combinations {
	int *data;
	int size;
};

struct Combinations *newCombinations(int size) {
	struct Combinations *result;
	result = calloc(1, sizeof(struct Combinations));
	if (result != NULL) {
		result->data = calloc(size * size * N_DIGITS, sizeof(int));
		result->size = size;
	}
	return result;
}

void freeCombinations(struct Combinations *comb) {
	if (comb != NULL) {
		free(comb->data);
		free(comb);
	}
}

void populateAllCombinations(struct Combinations *comb, struct Sudoku *puzzle) {
	int y, x, i;
	int *value = comb->data;
	int *data = puzzle->data;
	for (y = 0; y < puzzle->size; y++) {
		for (x = 0; x < puzzle->size; x++) {
			if (*data == 0) {
				for (i = 0; i < N_DIGITS; i++) {
					*value = 1;
					value++;
				}
			} else {
				for (i = 0; i < N_DIGITS; i++) {
					if (*data == (i+1)) {
						*value = 1;
					} else {
						*value = 0;
					}
					value++;
				}
			}
			data++;
		}
	}
}

void printCombinations(struct Combinations *comb) {
	int y, x, i;
	int *value = comb->data;
	for (y = 0; y < comb->size; y++) {
		for (x = 0; x < comb->size; x++) {
			printf("[");
			for (i = 0; i < N_DIGITS; i++) {
				if (*value == 0) {
					printf(" ");
				} else {
					printf("%d", i+1);
				}
				value++;
			}
			printf("]");
		}
		printf("\n");
	}
}

int getUniqueValueAt(struct Combinations *comb, int y, int x) {
	int i, value;
	for (i = 0; i < N_DIGITS; i++) {
                if (*(comb->data + (y * comb->size * N_DIGITS) + (x * N_DIGITS) + i) != 0) {
                        value = i+1;
                }
        }
	return value;
}

void enforceUniqueRow(struct Combinations *comb, int y, int x) {
	int tx, i;
	int value = getUniqueValueAt(comb, y, x);
	printf("enforceRow(%d,%d):%d\n", y, x, value);
	int *data;
	for (tx = 0; tx < comb->size; tx++) {
		if (x != tx) {
			data = comb->data + (y * comb->size * N_DIGITS) + (tx * N_DIGITS) + value - 1;
			*data = 0;
		}
	}
}

void enforceUniqueColumn(struct Combinations *comb, int y, int x) {
	int ty, i;
	int value = getUniqueValueAt(comb, y, x);
	printf("enforceColumn(%d,%d)\n", y, x);
	int *data;
	for (ty = 0; ty < comb->size; ty++) {
		if (y != ty) {
			data = comb->data + (ty * comb->size * N_DIGITS) + (x * N_DIGITS) + value - 1;
			*data = 0;
		}
	}
}

int main(int argc, char **argv) {
	int size = 9;
	struct Sudoku *puzzle = newSudoku(size);
	printSudoku(puzzle);
	readSudoku(puzzle);
	printSudoku(puzzle);

	struct Combinations *comb = newCombinations(size);
	printCombinations(comb);
	populateAllCombinations(comb, puzzle);
	printCombinations(comb);
	enforceUniqueRow(comb, 0, 1);
	printCombinations(comb);
	enforceUniqueColumn(comb, 0, 1);
	printCombinations(comb);
	enforceUniqueRow(comb, 0, 5);
	printCombinations(comb);
	enforceUniqueColumn(comb, 0, 5);
	printCombinations(comb);
	enforceUniqueRow(comb, 1, 0);
	printCombinations(comb);
	enforceUniqueColumn(comb, 1, 0);
	printCombinations(comb);

	fflush(stderr);
	freeCombinations(comb);
	freeSudoku(puzzle);
	return 0;
}
