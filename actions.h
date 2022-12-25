#pragma once
#include "structures.h"
#include "NATools.h"
void UpdateScore(struct Board* B, struct Player* P);///Time Complexity O(N^2),Additional space O(1)



int Move(struct Board* B, struct Player* P, int col_number);