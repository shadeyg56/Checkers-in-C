#ifndef AI
#define AI

typedef struct{
    int i;
    int j;
    int k;
    int l;
    int jump;
    int jumpX;
    int jumpY;
    int score;
} Move;

int validMoves(char board[][8]);
int canJump(char board[][8], Move *move);
int hasNeighbors(char board[][8], Move *move, char type);
Move pickMove();

#endif