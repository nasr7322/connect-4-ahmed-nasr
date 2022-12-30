#include "actions.h"
#include<Windows.h>

int evaluatePlayer(struct Board* B, struct Player* P) {
    int new_score = 0;

    ///Check Horizional connect fours
    for (int i = 0;i < B->height;i++) {
        int lst = 0;
        for (int j = 0;j < B->width;j++) {
            while (lst < j && ((j - lst + 1) > 4 || B->board[i][lst] != P->id))lst++;
            if (B->board[i][j] != P->id)lst = j;
            ///Add score iff     connected 4                        There is room to connect 4
            if ((j - lst + 1) && ((j - lst + 1) == 4 || (j + 1 < B->width && (B->board[i][j + 1] == 0 || B->board[i][j + 1] == P->id))))new_score += (1 << (2 * (j - lst)));
        }
    }

    ///Check Vertical connect fours
    for (int j = 0;j < B->width;j++) {
        int lst = 0;
        for (int i = 0;i < B->height;i++) {
            while (lst < i && ((i - lst + 1) > 4 || B->board[lst][j] != P->id))lst++;
            if (B->board[i][j] != P->id)lst = i;
            ///Add score iff     connected 4                        There is room to connect 4
            if ((i - lst + 1) && ((i - lst + 1) == 4 || (i + 1 < B->height && (B->board[i + 1][j] == 0 || B->board[i + 1][j] == P->id))))
                new_score += (1 << (2 * (i - lst)));
        }
    }

    ///Check 45degree connect fours
    for (int i = 0;i < B->height + B->width;i++) {///We start from all elements of most left column then of most bottom row so total height+width-1 beginning-cells
        int basex = Min(i, B->height - 1), basey = Max(0, i - (B->height - 1));///Decode position
        int lst = 0;
        for (int j = 0;j < Min(basex + 1, B->width - basey);j++) {
            while (lst < j && ((j - lst + 1) > 4 || B->board[basex - lst][basey + lst] != P->id))lst++;
            if (B->board[basex - j][basey + j] != P->id)lst = j;
            ///Add score iff     connected 4                        There is room to connect 4
            if ((j - lst + 1) && ((j - lst + 1) == 4 || (j + 1 < Min(basex + 1, B->width - basey) && (B->board[basex - (j + 1)][basey + (j + 1)] == 0 || B->board[basex - (j + 1)][basey + (j + 1)] == P->id))))
                new_score += (1 << (2 * (j - lst)));
        }
    }

    ///Check 135degree connect fours
    for (int i = 0;i < B->height + B->width;i++) {///We start from all elements of most right column then of most bottom row so total height+width-1 beginning-cells
        int basex = Min(i, B->height - 1), basey = Max(0, i - (B->height - 1));///Decode position
        basey = B->width - basey - 1;
        int lst = 0;
        for (int j = 0;j < Min(basex + 1, basey + 1);j++) {
            while (lst < j && ((j - lst + 1) > 4 || B->board[basex - lst][basey - lst] != P->id))lst++;
            if (B->board[basex - j][basey - j] != P->id)lst = j;
            if ((j - lst + 1) && ((j - lst + 1) == 4 || (j + 1 < Min(basex + 1, basey + 1) && (B->board[basex - (j + 1)][basey - (j + 1)] == 0 || B->board[basex - (j + 1)][basey - (j + 1)] == P->id))))
                new_score += (1 << (2 * (j - lst)));
        }
    }

    return new_score;
}

int evaluation(struct Board* B, struct Player* Ptowin, struct Player* Ptolose) {
    return evaluatePlayer(B, Ptowin) - evaluatePlayer(B, Ptolose);
}

int f = 0;

int best_score(struct Board* B, struct Player* Ptowin, struct Player* Ptolose, int maxmize, int dpth) {
    if (dpth == 0) {
        return evaluation(B, Ptowin, Ptolose);
    }
    if (maxmize) {
        int mx = -1e9;
        for (int i = 0;i < B->width;i++) {
            int state = PlayerMove(B, Ptowin, i);
            if (state == -1)continue;
            int ret = best_score(B, Ptowin, Ptolose, 0, dpth - 1);
            mx = Max(ret, mx);
            PopMove(B, Ptowin, Ptolose, i);
        }
        return mx;
    }
    else {
        int mn = 1e9;
        for (int i = 0;i < B->width;i++) {
            int state = PlayerMove(B, Ptolose, i);
            if (state == -1)continue;
            int ret = best_score(B, Ptowin, Ptolose, 1, dpth - 1);
            mn = Min(mn, ret);
            PopMove(B, Ptowin, Ptolose, i);
        }
        return mn;
    }
}


int best_move(struct Board* B, struct Player* Ptowin, struct Player* Ptolose) {
    int mx = -1e9;
    int bst = -1;
    for (int i = 0;i < B->width;i++) {
        int state = PlayerMove(B, Ptowin, i);
        if (state == -1)continue;
        OutputDebugStringA("Room to move");
        int ret = best_score(B, Ptowin, Ptolose, 0, 4);
        if (ret >= mx) {
            mx = ret;
            bst = i;
        }
        PopMove(B, Ptowin, Ptolose, i);
    }

    return bst;
}
