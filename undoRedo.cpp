#include "undoRedo.h"

int canUndo(int play_stack[], int cr_move) {
    return cr_move>0 && play_stack[cr_move-1]!=-1;
}

int UndoMove(struct Board* B, struct Player* P1, struct Player* P2, int play_stack[], int* cr_move) {
    if (!canUndo(play_stack, *cr_move))return -1;

    (*cr_move)--;
    PopMove(B, P1, P2, play_stack[*cr_move]);

    return 0;
}

int canRedo(int play_stack[], int cr_move) {
    return play_stack[cr_move] != -1;
}

int RedoMove(struct Board* B, struct Player* P1, struct Player* P2, int play_stack[], int* cr_move) {
    if (!canRedo(play_stack, *cr_move))return -1;
    PlayerMove(B, ((*cr_move) & 1) ? (P2) : (P1), play_stack[*cr_move]);
    (*cr_move)++;
    return 0;
}