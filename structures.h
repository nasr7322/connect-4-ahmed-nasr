#pragma once
struct Board {
    int height, width;
    int board[1000][1000];

};

struct Player {
    int score;
    int id;
    int turns_played;

};