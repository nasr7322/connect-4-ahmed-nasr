#pragma once
#include "structures.h"
#include "NATools.h"

void UpdateScore(struct Board* B, struct Player* P);///Time Complexity O(N^2),Additional space O(1)

int PlayerMove(struct Board* B, struct Player* P, int col_number);

void Reset(struct Board* B, struct Player* P1, struct Player* P2);

int PopMove(struct Board* B, struct Player* P1, struct Player* P2, int col_number);