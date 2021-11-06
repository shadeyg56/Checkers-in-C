#ifndef AI
#define AI

typedef struct{
    int i;
    int j;
    int k;
    int l;
    int jump;
} Move;

int validMoves(char board[][8]);
int canJump(char board[][8], Move move);
Move pickMove();

#endif