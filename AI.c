#include <stdio.h>
#include "AI.h"

char turn = 'o';

typedef struct{
    int i;
    int j;
    int k;
    int l;
} Move;

Move *availableMoves;

int validMoves(char **board){
    int i, j, k, l;
    for (j = 0; j < 8; j++){
        for (i = 0; i < 8; i++){
            for (int x = 0; x < 2; x++){
                switch (x){
                    case 0:
                        k = i + 1;
                        l = j + 1;
                    case 1:
                        k = i - 1;
                        l = j - 1;
                }
                if (tolower(board[j][i]) != turn){
                    return -1;
                }
                if (board[l][k] != ' '){
                    printf("Space is occupied\n");
                    return -1;
                }
                // if (turn == 'o'){
                //     opponent = 'x';
                //     if (!ISKING(board[j][i])){
                //         if (j >= l){
                //             printf("An piece that is not a king can only move forward\n");
                //             return -1;
                //         }
                //     }
                // }
                return 0;
            }
        }
    }
}