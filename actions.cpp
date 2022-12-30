#include "actions.h"


void UpdateScore(struct Board* B, struct Player* P) {///Time Complexity O(N^2),Additional space O(1)

    int new_score = 0;

    ///Check Horizional connect fours
    for (int i = 0;i < B->height;i++) {
        int lst = 0;
        ///printf("#row =%d\n",i);
        for (int j = 0;j < B->width;j++) {
            while (lst < j && ((j - lst + 1) > 4 || B->board[i][lst] != P->id))lst++;
            if (B->board[i][j] != P->id)lst = j;
            if ((j - lst + 1) == 4)new_score++;
        }
    }

    ///Check Vertical connect fours
    for (int j = 0;j < B->width;j++) {
        int lst = 0;
        ///printf("#col =%d\n",j);
        for (int i = 0;i < B->height;i++) {
            while (lst < i && ((i - lst + 1) > 4 || B->board[lst][j] != P->id))lst++;
            if (B->board[i][j] != P->id)lst = i;
            if ((i - lst + 1) == 4)new_score++;
            ///printf("from %d to %d\n",lst,i);
        }
    }

    ///Check 45degree connect fours
    for (int i = 0;i < B->height + B->width;i++) {///We start from all elements of most left column then of most bottom row so total height+width-1 beginning-cells
        int basex = Min(i, B->height - 1), basey = Max(0, i - (B->height - 1));///Decode position
        int lst = 0;
        ///printf("base cell =(%d,%d)\n",basex,basey);
        for (int j = 0;j < Min(basex + 1, B->width - basey);j++) {
            ///printf("#from %d to %d\n",lst,j);
            while (lst < j && ((j - lst + 1) > 4 || B->board[basex - lst][basey + lst] != P->id))lst++;
            if (B->board[basex - j][basey + j] != P->id)lst = j;
            if ((j - lst + 1) == 4)new_score++;
            ///printf("from %d to %d\n",lst,j);
        }
    }

    ///Check 135degree connect fours
    for (int i = 0;i < B->height + B->width;i++) {///We start from all elements of most right column then of most bottom row so total height+width-1 beginning-cells
        int basex = Min(i, B->height - 1), basey = Max(0, i - (B->height - 1));///Decode position
        basey = B->width - basey - 1;
        int lst = 0;
        ///printf("base cell =(%d,%d)\n",basex,basey);
        for (int j = 0;j < Min(basex + 1, basey + 1);j++) {
            ///printf("#from %d to %d\n",lst,j);
            while (lst < j && ((j - lst + 1) > 4 || B->board[basex - lst][basey - lst] != P->id))lst++;
            if (B->board[basex - j][basey - j] != P->id)lst = j;
            if ((j - lst + 1) == 4)new_score++;
            ///printf("from %d to %d\n",lst,j);
        }
    }
    P->score = new_score;
}

int PlayerMove(struct Board* B, struct Player* P, int col_number) {
    if (col_number >= B->width || col_number < 0 || B->board[0][col_number] != 0)return -1;
    int cr = 0;
    while (cr + 1 < B->height && B->board[cr + 1][col_number] == 0)cr++;
    B->board[cr][col_number] = P->id;
    UpdateScore(B, P);
    P->turns_played++;
    return 0;
}

void Reset(Board* B, Player* P1, Player* P2)
{
    for (int i = 0;i < B->height;i++) {
        for (int j = 0;j < B->width;j++) {
            B->board[i][j] = 0;
        }
    }
    P1->score = P1->turns_played = 0;
    P2->score = P2->turns_played = 0;
}

int PopMove(struct Board* B, struct Player* P1, struct Player* P2, int col_number) {
    if (col_number >= B->width || col_number < 0)return -1;
    int cr = 0;
    while (cr + 1 < B->height && B->board[cr + 1][col_number] == 0)cr++;
    cr++;
    if (cr == B->height)return -1;
    if (B->board[0][col_number])cr = 0;
    if (B->board[cr][col_number] == P1->id) {
        P1->turns_played--;
        B->board[cr][col_number] = 0;
        UpdateScore(B, P1);

    }
    else if (B->board[cr][col_number] == P2->id) {
        P2->turns_played--;
        B->board[cr][col_number] = 0;
        UpdateScore(B, P2);

    }
    return 0;
}

