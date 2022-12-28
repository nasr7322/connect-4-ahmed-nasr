#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "NATools.h"

int createFile(char* filename);

int parseScore(char* data);

char* parseName(char* data);


int addScore(char* prename, int score, char* filename);



int getScore(char* prename, char* filename);

int getScoreByIndex(int idx, char* filename);