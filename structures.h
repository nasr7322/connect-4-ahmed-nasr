#pragma once
struct Board {
    int height, width;
    int board[25][25];
    int mode;
    int Secounds;
    int Minutes;
};

struct Player {
    int score;
    int id;
    int turns_played;
};

