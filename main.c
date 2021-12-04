#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "AI.h"

#define ISKING(p) (p == 'X' || p == 'O')

char board[8][8] = {
    {' ', 'o', ' ', 'o', ' ',  'o', ' ', 'o'},
    {'o', ' ', 'o', ' ', 'o', ' ', 'o', ' '},
    {' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'x', ' ', 'x', ' ', 'x', ' ', 'x', ' '},
    {' ', 'x', ' ', 'x', ' ',  'x', ' ', 'x'},
    {'x', ' ', 'x', ' ', 'x', ' ', 'x', ' '},
};

char turn = 'x';
int xPieces = 12;
int oPieces = 12;
int gameOver = 0;
int mode;

int mainMenu();
void printBoard();
int letterToCoord(char letter);
int move(int i, int j, int k, int l);
int checkForWin();

int main(void){
    char i, k;
    int j, l, x, x2;
    int inputs;
    Move AIMove;
    mode = mainMenu();
    printBoard();
    while (gameOver == 0){
        while (1){
            if (mode == 1){
                if (turn == 'o'){
                    validMoves(board);
                    AIMove = pickMove();
                    move(AIMove.i, AIMove.j, AIMove.k, AIMove.l);
                    if (l == 7){
                        board[AIMove.l][AIMove.k] = 'O';
                    }
                    turn = 'x';
                    break;
                }
            }
            printf("%c's turn: ", turn);
            fflush(stdin);
            inputs = scanf("%c%d", &i, &j);
            printf("To: ");
            fflush(stdin);
            inputs += scanf("%c%d", &k, &l);
            x = letterToCoord(i);
            x2 = letterToCoord(k);
            if (x == -1 || x2 == -1){
                continue;
            }
            if (inputs != 4){
                continue;
            }
            if (move(x, j, x2, l) == 0){
                if (turn == 'x'){
                    turn = 'o';
                }
                else if (turn == 'o'){
                    turn = 'x';
                }
                break;
            }
            else{
                printf("Invalid move\n");
            }
        }
        if (gameOver == 0){
            printBoard();
        }
    }
    return 0;
}

int mainMenu(){
    int mode;
    int selection;
    int cont = 1;
    while (cont){
        printf("Welcome to Checkers in C\n");
        printf("Select a mode:\n");
        printf("[1] Player vs Player\n");
        printf("[2] Player vs Computer\n");
        scanf(" %d", &selection);
        printf("%d", selection);
        switch (selection){
            case 1:
                mode = 2;
                cont = 0;
                break;
            case 2:
                mode = 1;
                cont = 0;
                break;
        }
    }
    return mode;
}

int move(int i, int j, int k, int l){
    
    // for(int iter = 0; board[j][i][iter]; iter++){
    //     board[j][i][iter] = tolower(board[j][i][iter]);
    // }
    int jump_x;
    int jump_y;
    int hasJump = 1;
    char jumped;
    char opponent;
    int won = 0;
    int dirY;
    int dirX = 1;
    char takeDouble;
    if (7 <= i < 0){
        printf("Out of bounds\n");
        return -1;
    }
    if (7 <= j < 0){
        printf("Out of bounds\n");
        return -1;
    }
    if (7 <= k < 0){
        printf("Out of bounds\n");
        return -1;
    }
    if (7 <= l < 0){
        printf("Out of bounds\n");
        return -1;
    }

     if (tolower(board[j][i]) != turn){
        printf("space is %d, %d\n", i, j);
        printf("Not your square\n");
        return -1;
    }
    if (board[l][k] != ' '){
        printf("Space is occupied\n");
        return -1;
    }
    if (turn == 'x'){
        opponent = 'o';
        if (!ISKING(board[j][i])){
            if (j <= l){
                printf("An piece that is not a king can only move forward\n");
                return -1;
            }
        }
    }
    if (turn == 'o'){
        opponent = 'x';
        if (!ISKING(board[j][i])){
            if (j >= l){
                printf("An piece that is not a king can only move forward\n");
                return -1;
            }
        }
    }
    if (i - k == 1 || i - k == -1){
        if (j - l == 1 || j - l == -1){
            board[l][k] = board[j][i];
            board[j][i] = ' ';
            return 0;
        }
    }
    if (i - k == 2 || i - k == -2){
        if (j - l == 2 || j - l == -2){
            if (i < k){
                jump_x = i + 1;
            }
            else{
                jump_x = i - 1;
            }
            if (j < l){
                jump_y = j + 1;
                dirY = 1;
            }
            else{
                jump_y = j - 1;
                dirY = -1;
            }
            jumped = tolower(board[jump_y][jump_x]);
            if (jumped != opponent){
                printf("You can only jump an enemy piece\n");
                return -1;
            }
            board[jump_y][jump_x] = ' ';
            board[l][k] = board[j][i];
            board[j][i] = ' ';
            switch (turn){
                case 'x':
                    oPieces--;
                    break;
                case 'o':
                    xPieces--;
                    break;
            }
            won = checkForWin();
            if (won == 1){
                printf("%c wins the game!", turn);
                gameOver = 1;
                hasJump = 0;
            }
            while (hasJump == 1){
                jump_y = l + dirY;
                for (int iter = 0; iter < 2; iter++){
                    jump_x = k + dirX;
                    hasJump = 0;
                    if (tolower(board[jump_y][jump_x]) == opponent){
                            if (jump_y+dirY >= 0 && jump_y+dirY < 8){
                                if (jump_x+dirX >= 0 && jump_x+dirX < 8){
                                    if (board[jump_y+dirY][jump_x+dirX] == ' '){
                                        if (mode == 1 && turn == 'o'){
                                            takeDouble = 'y';
                                        }
                                        else{
                                            printf("Another jump is available. Would you like to take it? (y/n)\n");
                                            scanf(" %c", &takeDouble);
                                        }
                                        if (takeDouble == 'y' || takeDouble == 'Y'){
                                            board[jump_y][jump_x] = ' ';
                                            board[jump_y+dirY][jump_x+dirX] = board[l][k];
                                            board[l][k] = ' ';
                                            l = jump_y+dirY;
                                            k = jump_x+dirX;
                                            hasJump = 1;
                                            break;
                                        }
                                    }
                                }
                            }
                    }
                    dirX = -1;
                }
            }
            if (turn == 'x'){
                if (l == 0){
                    board[l][k] = 'X';
                }
            }
            else if (turn == 'o'){
                if (l == 7){
                    board[l][k] = 'O';
                }
            }
            return 0;
        }
    }
    return -1;
}

void printBoard(){
    system("cls");
    int row;;
    int col;
    int side;
    printf("  +---+---+---+---+---+---+---+---+\n");
    for (row = 0; row < 8; row++){
        printf("%d |", row);
        for (col = 0; col < 8; col++){
            printf(" %c |", board[row][col]);
            
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    a   b   c   d   e   f   g   h\n");
    
}

int checkForWin(){
    if (oPieces == 0 || xPieces == 0){
        return 1;
    }
    return 0;
}

int letterToCoord(char letter){
    letter = tolower(letter);
    switch (letter){
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        default:
            return -1;
    }
}

