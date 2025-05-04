#include <stdio.h>
#include <string.h>
// Console Colours
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
// PLayers
#define PLAYER1 1
#define PLAYER2 2
// MAIN BOARD
int BOARD[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
// Labels and coordinates on board
struct MAP {
    char *label;
    int row;
    int col;
} map[] = {
    {"UL", 0, 0}, {"UM", 0, 1}, {"UR", 0, 2},
    {"ML", 1, 0}, {"M",  1, 1}, {"MR", 1, 2},
    {"BL", 2, 0}, {"BM", 2, 1}, {"BR", 2, 2}
};

int checkWinner(int player) { 
    /* Checks for 3 in a row. 
    Returns player (1 or 2) if successful
    Returns 0 if no matches */
    if (BOARD[0][0] == player && BOARD[0][1] == player && BOARD[0][2] == player) return player; // TOP ROW
    if (BOARD[1][0] == player && BOARD[1][1] == player && BOARD[1][2] == player) return player; // MIDDLE ROW
    if (BOARD[2][0] == player && BOARD[2][1] == player && BOARD[2][2] == player) return player; // BOTTOM ROW
    if (BOARD[0][0] == player && BOARD[1][0] == player && BOARD[2][0] == player) return player; // LEFT COLUMN
    if (BOARD[0][1] == player && BOARD[1][1] == player && BOARD[2][1] == player) return player; // MIDDLE COLUMN
    if (BOARD[0][2] == player && BOARD[1][2] == player && BOARD[2][2] == player) return player; // RIGHT COLUMN
    if (BOARD[0][0] == player && BOARD[1][1] == player && BOARD[2][2] == player) return player; // MAIN DIAGONAL
    if (BOARD[0][2] == player && BOARD[1][1] == player && BOARD[2][0] == player) return player; // SECONDARY DIAGONAL
    return 0; // No winner
}

void displayBoard() {
    // Displays the board
    for (int i = 0;i<3;i++) {
        for (int j = 0;j<3;j++) {
            if (BOARD[i][j] == 1) printf(RED " X " RESET);          // Player 1's Red X
            else if (BOARD[i][j] == 2) printf(BLUE " O " RESET);    // Player 2's Blue O
            else printf("   ");                                     // Empty square
            if (j<2) printf("|");
        }
        printf("\n");
        if (i<2) printf("-----------\n");
    }
    printf("\n");
}

void displayOptions() {
    // Displays all remaining empty squares
    printf("Available options: ");
    if (BOARD[0][0] == 0) printf("UL "); // UP LEFT
    if (BOARD[0][1] == 0) printf("UM "); // UP MIDDLE
    if (BOARD[0][2] == 0) printf("UR "); // UP RIGHT
    if (BOARD[1][0] == 0) printf("ML "); // MIDDLE LEFT
    if (BOARD[1][1] == 0) printf("M ");  // MIDDLE (CENTRE)
    if (BOARD[1][2] == 0) printf("MR "); // MIDDLE RIGHT
    if (BOARD[2][0] == 0) printf("BL "); // BOTTOM LEFT
    if (BOARD[2][1] == 0) printf("BM "); // BOTTOM MIDDLE
    if (BOARD[2][2] == 0) printf("BR "); // BOTTOM RIGHT
    printf("\n");
}

int isSquareAvailable(const char *sq) {
    /* Checks if the square is available
    Returns 1: AVAILABLE
            0: UNAVAILABLE
            -1: INVALID INPUT */
    for (int i = 0;i<9;i++) {
        if (strcmp(sq,map[i].label) == 0) {
            if (BOARD[map[i].row][map[i].col] == 0) return 1;
            else return 0;
        } 
    }
    return -1;
}

void updateBoard(int player, const char *sq) {
    // Updates the board array. 0 -> 1 for Player 1, 0 -> 2 for Player 2
    for (int i = 0;i<9;i++) {
        if (strcmp(sq,map[i].label) == 0) {
            BOARD[map[i].row][map[i].col] = player;
            break;
        }
    }
}

void getSafeInput(char *input, int size) {
    // Validates input
    fgets(input, size, stdin);
    if (strchr(input, '\n') == NULL) { // If NULL, then input is too long
        int CH;
        while ((CH = getchar()) != '\n' && CH != EOF); // Remove excess characters
    }
    input[strcspn(input, "\n")] = 0;
}

int main() {
    printf("=  TIC TAC TOE  =\n");
    displayBoard();
    int player = PLAYER1; // Starting with player 1
    char square[10]; // To store user input
    int round = 0;   // To check for draw (if round==9)
    while (round != 9) {
        displayOptions();
        int availability = 2; // Not 0, 1, -1
        while (availability != 1) {
            if (player == PLAYER1) printf(RED "PLAYER 1, Choose a square: " RESET);
            else printf(BLUE "PLAYER 2, Choose a square: " RESET);
            getSafeInput(square, sizeof(square));
            availability = isSquareAvailable(square);
            if (availability == 0) {
                printf(MAGENTA "!! Square '%s' is unavailable. Try again !!\n",square); printf(RESET);
            }
            else if (availability == -1) printf(MAGENTA "!! Invalid Input. Try again !!\n" RESET);
        }
        updateBoard(player,square);
        displayBoard();
        int winner = checkWinner(player);
        if (winner != 0) {
            if (player == PLAYER1) printf(RED "PLAYER 1 WON!\n" RESET);
            else printf(BLUE "PLAYER 2 WON!\n" RESET);
            break;
        }
        if (player == PLAYER1) player = PLAYER2;    // Next player's turn
        else player = PLAYER1;
        round++;
    }
    if (round == 9) printf(MAGENTA "IT WAS A TIE!\n" RESET);    // Draw condition
    return 0;
}
