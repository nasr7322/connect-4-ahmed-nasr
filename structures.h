#pragma once
struct Board {
    int height, width;
    int board[100][100];
    int mode;
};

struct Player {
    int score;
    int id;
    int turns_played;

};

