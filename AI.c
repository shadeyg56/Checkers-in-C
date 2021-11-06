#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "AI.h"


size_t moves = 1;
Move *availableMoves = NULL;

int validMoves(char board[][8]){
    int i, j, k, l;
    int iter = 0;
    availableMoves = (Move*) malloc(sizeof(Move));
    Move *varTest = availableMoves;
    for (j = 0; j < 8; j++){
        for (i = 0; i < 8; i++){;

            availableMoves[moves-1].jump = 0;
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
                availableMoves[moves-1].i = i;
                availableMoves[moves-1].j = j;
                availableMoves[moves-1].k = k;
                availableMoves[moves-1].l = l;
                if (tolower(board[j][i]) != 'o'){
                    if (tolower(board[j][i]) == 'x'){

                        // jumping currently broken
                        continue;
                        // if (canJump(board, availableMoves[moves-1]) == 1){
                        //     availableMoves[moves-1].jump = 1;
                        // }
                    }
                    else{
                        continue;
                    }
                }
                if (board[l][k] != ' '){
                    continue;
                }
                printf("%d, %d to %d, %d is a valid move\n", i, j, k, l);
                moves++;
                availableMoves = realloc(availableMoves, moves * sizeof(Move));
                //printf("move test %d, %d\n", availableMoves[moves-1].i, availableMoves[moves-1].j);
            }
        }
    }
    return 0;
}



int canJump(char board[][8], Move move){
    int i = move.i;
    int j = move.j;
    int k = move.k;
    int l = move.l;
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
        move.k = jumpX;
        move.l = jumpY;
        return 1;
    }
    return 0;
}

Move pickMove(){
    Move currentMove;
    for (int i = 0; i < moves - 1; i++){
        currentMove = availableMoves[i];

        if (currentMove.jump == 1){
            printf("move i %d\n", currentMove.i);
            return currentMove;
        }
    }
    return currentMove;
}