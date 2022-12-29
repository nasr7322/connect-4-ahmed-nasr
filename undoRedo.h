#pragma once
#include "actions.h"

int canUndo(int play_stack[], int cr_move);
int UndoMove(struct Board* B, struct Player* P1, struct Player* P2, int play_stack[], int* cr_move);


int canRedo(int play_stack[], int cr_move);


int RedoMove(struct Board* B, struct Player* P1, struct Player* P2, int play_stack[], int* cr_move);
/*
Example
for move

PlayerMove(&B,(crm&1)?(&P2):(&P1),col);
            play_stack[crm++]=col;
            play_stack[crm]=-1;
*/