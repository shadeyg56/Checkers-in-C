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
int canJump(char board[][8], Move *move);
<<<<<<< HEAD
Move *pickMove();
=======
Move pickMove();
>>>>>>> a09e7512ab40daeb6b8ef6526091ba40400a5cf6

#endif