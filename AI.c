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
                currentMove->score = 0;
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
                            currentMove->score++;
                        }
                        else{
                            continue;
                        }
                    }
                    else{
                        continue;
                    }
                }
                if (hasNeighbors(board, currentMove, 'o') == 1){
                    currentMove->score++;
                }
                if (hasNeighbors(board, currentMove, 'x') == 1){
                    currentMove->score--;
                }
                printf("%d, %d to %d, %d is a valid move with a score of %d\n", i, j, k, l, currentMove->score);
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

int hasNeighbors(char board[][8], Move *move, char type){
    int x = move->k;
    int y = move->l;
    int jumpX = move->jumpX;
    int jumpY = move->jumpY;
    printf("%c %c\n", board[y+1][x-1], board[y+1][x+1]);
    switch (type){
        case 'x':
            if (board[y+1][x-1] == 'x' && (y+1 != jumpY && x-1 != jumpX)){
                return 1;
            }
            if (board[y+1][x+1] == 'x' && (y+1 != jumpY && x+1 != jumpX)){
                return 1;
            }
            break;
        case 'o':
            if (board[y-1][x-1] == 'o' || board[y-1][x+1] == 'o'){
                return 1;
            }
    }
    return 0;
    
}

Move pickMove(){
    Move currentMove;
    Move bestMove;
    bestMove.score = -2;

    for (int i = 0; i < moves - 1; i++){
        currentMove = availableMoves[i];
        if (currentMove.score > bestMove.score){
            bestMove = currentMove;
        }
    }
    if (bestMove.score == -2){
        bestMove = currentMove;
    }
    free(availableMoves);

    return bestMove;
}