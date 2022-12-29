#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "NATools.h"
#include "structures.h"
#include "actions.h"


char* parseGameName(char* data);

int SaveBoard(struct Board* B, char* filename, char* gameprename);


int LoadBoard(struct Board* B, char* filename, char* gameprename);

int LoadGame(struct Board* B, struct Player* P1, struct Player* P2, int* turns, char* filename, char* gameprename);