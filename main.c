#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *board[8][8] = {
    {" ", "o", " ", "o", " ",  "o", " ", "o"},
    {"o", " ", "o", " ", "o", " ", "o", " "},
    {" ", "o", " ", "o", " ", "o", " ", "o"},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {" ", " ", " ", " ", " ", " ", " ", " "},
    {"x", " ", "x", " ", "x", " ", "x", " "},
    {" ", "x", " ", "x", " ",  "x", " ", "x"},
    {"x", " ", "x", " ", "x", " ", "x", " "},
};

char turn = 'x';

void printBoard();
int letterToCoord(char letter);
int move(int i, int j, int k, int l);

int main(void){
    printBoard();
    return 0;
}

int move(int i, int j, int k, int l){
    if (tolower(board[i][j]) != turn){
        return -1;
    }
    if (board[i][j] != " "){
        return -1;
    }
    if (turn == "x"){
        if (j >= k){
            return -1;
        }
    }
    if (turn == "o"){
        if (j <= k){
            return -1;
        }
    }
    if (7 <= i < 0){
        return -1;
    }
    if (7 <= j < 0){
        return -1;
    }
    if (7 <= k < 0){
        return -1;
    }
    if (7 <= l < 0){
        return -1;
    }
    if (i - k == 1 || i - k == -1){

    }
}

void printBoard(){
    system("cls");
    printf("Printing board...\n");
    int row;;
    int col;
    int side;
    printf("  +---+---+---+---+---+---+---+---+\n");
    for (row = 0; row < 8; row++){
        printf("%d |", row+1);
        for (col = 0; col < 8; col++){
            printf(" %s |", board[row][col]);
            
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    a   b   c   d   e   f   g   h\n");
    
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
    }
}

