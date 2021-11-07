#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "AI.h"

#define ISKING(p) (p == 'O')

size_t moves = 1;
Move *availableMoves = NULL;

int validMoves(char board[][8]){
    int i, j, k, l;
    int iter = 0;
    availableMoves = (Move*) malloc(sizeof(Move));
    Move *currentMove = NULL;
    int checks = 2;
    for (j = 0; j < 8; j++){
        for (i = 0; i < 8; i++){;
            iter++;
            //printf("iter %d\n", iter++)
            if (ISKING(board[j][i])){
                checks = 4;
            }
            for (int x = 0; x < checks; x++){
                currentMove = &availableMoves[moves-1];
                currentMove->jump = 0;
                switch (x){
                    case 0:
                        k = i + 1;
                        l = j + 1;
                        break;
                    case 1:
                        k = i - 1;
                        l = j + 1;
                        break;
                    case 2:
                        k = i + 1;
                        l = j - 1;
                        break;
                    case 3:
                        k = i - 1;
                        l = j - 1;
                        break;
                }
                if (k == 8 || k == -1){
                    continue;
                }
                
                currentMove->i = i;
                currentMove->j = j;
                currentMove->k = k;
                currentMove->l = l;
                if (tolower(board[j][i]) != 'o'){
                    continue;
                }
                if (board[l][k] != ' '){
                    if (tolower(board[l][k]) == 'x'){
                        if (canJump(board, currentMove) == 1){
                            currentMove->jump = 1;
                        }
                        else{
                            continue;
                        }
                    }
                    else{
                        continue;
                    }
                }
                printf("%d, %d to %d, %d is a valid move\n", i, j, k, l);
                moves++;
                availableMoves = realloc(availableMoves, moves * sizeof(Move));
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
    int jumpY;
    if (l == 7 || k == 7 || k == 0){
        return 0;
    }
    if (i < k){
        jumpX = k + 1;
    }
    else{
        jumpX = k - 1;
    }
    if (j < l){
        jumpY = l + 1;
    }
    else{
        jumpY = l - 1;
    }
    char jumpedPiece = board[jumpY][jumpX];
    if (jumpedPiece == ' '){
        move->k = jumpX;
        move->l = jumpY;
        return 1;
    }
    return 0;
}

Move pickMove(){
    Move currentMove;
    for (int i = 0; i < moves - 1; i++){
        currentMove = availableMoves[i];
        if (currentMove.jump == 1){
            printf("jumping from ");
            return currentMove;
        }
    }
    return currentMove;
}