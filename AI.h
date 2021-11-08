#ifndef AI
#define AI

typedef struct{
    int i;
    int j;
    int k;
    int l;
    int jump;
    int score;
} Move;

int validMoves(char board[][8]);
int canJump(char board[][8], Move *move);
int hasNeighbors(char board[][8], int x, int y, char type);
Move pickMove();

#endif