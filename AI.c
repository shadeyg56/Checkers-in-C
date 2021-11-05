#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "AI.h"


size_t moves = 1;
Move *availableMoves = NULL;

int validMoves(char board[][8]){
    int i, j, k, l;
    Move *currentMove = NULL;
    int iter = 0;
    availableMoves = malloc(sizeof(Move));
    for (j = 0; j < 8; j++){
        currentMove = malloc(sizeof(Move));
        for (i = 0; i < 8; i++){
            iter++;
            //printf("iter %d\n", iter++);
            for (int x = 0; x < 2; x++){
                switch (x){
                    case 0:
                        k = i + 1;
                        break;
                    case 1:
                        k = i - 1;
                        break;
                }
                if (k == 8 || k == -1){
                    continue;
                }
                l = j + 1;
                if (tolower(board[j][i]) != 'o'){
                    continue;
                }
                if (board[l][k] != ' '){
                    continue;
                }
                printf("%d, %d to %d, %d is a valid move\n", i, j, k, l);
                currentMove->i = i;
                currentMove->j = j;
                currentMove->k = k;
                currentMove->l = l;
                currentMove->jump = 0;
                if (canJump(board, currentMove) == 1){
                    currentMove->jump = 1;
                }
                availableMoves = realloc(availableMoves, moves * sizeof(Move));
                availableMoves[moves-1] = *currentMove;
                moves++;
            }
        }
    }
    return 0;
}



int canJump(char board[][8], Move *move){
    int i = move->i;
    int j = move->j;
    int k = move->k;
    int l = move->l;
    char from = board[j][i];
    char to = board[l][k];
    int jumpX;
    int jumpY = j + 1;
    if (i < k){
        jumpX = i + 1;
    }
    else{
        jumpX = i - 1;
    }
    char jumpedPiece = board[jumpY][jumpX];
    if (jumpedPiece == 'x' || jumpedPiece == 'X'){
        return 1;
    }
    return 0;
}

Move *pickMove(){
    Move *currentMove = NULL;
    for (int i = 0; i < moves; i++){
        *currentMove = availableMoves[i];
        if (currentMove->jump == 1){
            return currentMove;
        }
    }
}