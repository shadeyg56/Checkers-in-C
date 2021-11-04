#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "AI.h"

typedef struct{
    int i;
    int j;
    int k;
    int l;
} Move;

Move *availableMoves = NULL;

int validMoves(char board[][8]){
    int i, j, k, l;
    size_t moves = 1;
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
                availableMoves = realloc(availableMoves, moves * sizeof(Move));
                availableMoves[moves-1] = *currentMove;
                moves++;
            }
        }
    }
    return 0;
}