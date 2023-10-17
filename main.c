#include <stdio.h>
#include "C:/CUnit-2.1-2/CUnit/Headers/Basic.h"

void displayGrid(char grid[3][3]) {
    printf("       1  2  3\n");
    printf("1     %c | %c | %c \n", grid[0][0], grid[0][1], grid[0][2]);
    printf("     -----------\n");
    printf("2     %c | %c | %c \n", grid[1][0], grid[1][1], grid[1][2]);
    printf("     -----------\n");
    printf("3     %c | %c | %c \n", grid[2][0], grid[2][1], grid[2][2]);
};

int checkWin(char grid[3][3]) {
    // Loop through the rows & columns and see if there is a winner
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ' && grid[i][1] != ' ' && grid[i][2] != ' ' ||
            grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ' && grid[1][i] != ' ' && grid[2][i] != ' ') {
            return 1;
        }
    }
    // Diagonal
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != ' ' && grid[1][1] != ' ' && grid[2][2] != ' ' ||
        grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != ' ' && grid[1][1] != ' ' && grid[2][0] != ' ') {
        return 1;
    }
    return 0;
}

int isValidMove(char grid[3][3], const int* row, const int* col) {
    if (*row > 2 || *row < 0 || *col > 2 || *col < 0) {
        return 0;
    }
    if (grid[*row][*col] == ' ') {
        return 1;
    }
    return 0;
}

int isDraw(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int o = 0; o < 3; o++) {
            if (grid[i][o] == ' ') {
                return 0;
            }
        }
    }
    if (checkWin(grid) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void saveGame(char grid[3][3]) {
    // It has to have the full path, otherwise it won't work, due to CLions working directory
    const char* PATH_FILE = "C:\\Users\\lucac\\Documents\\Programming stuff\\C-C++\\C\\IE\\Assignment 1.2\\gameState.txt";
    FILE *fp;
    fp = fopen(PATH_FILE, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
    }
    for (int i = 0; i < 3; i++) {
        fprintf(fp, "%c %c %c\n", grid[i][0], grid[i][1], grid[i][2]);
    }
    fclose(fp);
}

char* importGame(char grid[3][3]) {
    const char* PATH_FILE = "C:\\Users\\lucac\\Documents\\Programming stuff\\C-C++\\C\\IE\\Assignment 1.2\\gameState.txt";
    FILE *fp;
    fp = fopen(PATH_FILE, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
    }
    unsigned short xCount = 0;
    unsigned short oCount = 0;

    for (int i = 0; i < 3; i++) {
        fscanf(fp, "%c %c %c\n", &grid[i][0], &grid[i][1], &grid[i][2]);
        if (grid[i][0] == 'X') {
            xCount++;
        } else if (grid[i][0] == 'O') {
            oCount++;
        }
    }
    fclose(fp);
    return (char *) grid;
}

// Initialize and clean up test suite
int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

// Test case functions
void test_wins(void) {
    char gridColumn[3][3] = {
            {'X', ' ', ' '},
            {'X', ' ', ' '},
            {'X', ' ', ' '}
    };
    CU_ASSERT_EQUAL(checkWin(gridColumn), 1);
    char gridRow[3][3] = {
            {'X', 'X', 'X'},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
    };
    CU_ASSERT_EQUAL(checkWin(gridRow), 1);
    char gridDiagonal[3][3] = {
            {'X', ' ', ' '},
            {' ', 'X', ' '},
            {' ', ' ', 'X'}
    };
    CU_ASSERT_EQUAL(checkWin(gridDiagonal), 1);
}

void test_draws(void) {
    char gridDraw[3][3] = {
            {'X', 'O', 'O'},
            {'O', 'X', 'X'},
            {'O', 'X', 'O'}
    };
    CU_ASSERT_EQUAL(isDraw(gridDraw), 1);
}

void test_move(void) {
    char gridInvalidMove [3][3] = {
            {'X', 'O', 'O'},
            {'O', 'X', 'X'},
            {'O', 'X', 'O'}
    };
    int invalidRow = 0;
    int invalidCol = 0;
    CU_ASSERT_EQUAL(isValidMove(gridInvalidMove, &invalidRow, &invalidCol), 0);

    char gridValidMove [3][3] = {
            {'X', 'O', 'O'},
            {'O', ' ', 'X'},
            {'O', ' ', 'O'}
    };
    int validRow = 1;
    int validCol = 1;
    CU_ASSERT_EQUAL(isValidMove(gridValidMove, &validRow, &validCol), 1);
}

void playGame(void) {

    /*
     * The function to save the game does exist, but it is not used in the game
     * Same as the function to import the game from a file
     */

    printf("Welcome to Tic Tac Toe!\n");
    printf("Player 1 is X and Player 2 is O\n");
    printf("Player 1 goes first\n");

    char grid[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
    };

    int row, column;
    int player = 1;

    while (checkWin(grid) == 0 && isDraw(grid) == 0) {
        displayGrid(grid);

        printf("Player %d, enter a row (1-3): ", player);
        scanf("%d", &row);
        row = row - 1;
        printf("Player %d, enter a column (1-3): ", player);
        scanf("%d", &column);
        column = column - 1;

        if (isValidMove(grid, &row, &column) == 1) {
            if (player == 1) {
                grid[row][column] = 'X';

                if (checkWin(grid) == 1) {
                    displayGrid(grid);
                    printf("Player %d wins!\n", player);
                    saveGame(grid);
                } else if (isDraw(grid) == 1) {
                    displayGrid(grid);
                    printf("It's a draw!\n");
                }

                player = 2;
            } else {
                grid[row][column] = 'O';

                if (checkWin(grid) == 1) {
                    displayGrid(grid);
                    printf("Player %d wins!\n", player);
                    saveGame(grid);
                } else if (isDraw(grid) == 1) {
                    displayGrid(grid);
                    printf("It's a draw!\n");
                }

                player = 1;
            }
        } else {
            row, column = 0;
            printf("Invalid move, try again\n");
        }
    }
}

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add a suite to the registry
    CU_pSuite suite = CU_add_suite("Suite_1", init_suite, clean_suite);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test case to the suite
    if ((NULL == CU_add_test(suite, "test_wins", test_wins))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(suite, "test_draws", test_draws))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(suite, "test_move", test_move))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run the tests
    CU_basic_run_tests();

    // Display test results
    CU_cleanup_registry();

    // If all tests passed, play the game
    playGame();
    return CU_get_error();
}
