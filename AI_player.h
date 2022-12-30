#pragma once
#include "actions.h"

int evaluatePlayer(struct Board* B, struct Player* P);

int evaluation(struct Board* B, struct Player* Ptowin, struct Player* Ptolose);

int best_score(struct Board* B, struct Player* Ptowin, struct Player* Ptolose, int maxmize, int dpth);

int best_move(struct Board* B, struct Player* Ptowin, struct Player* Ptolose);
