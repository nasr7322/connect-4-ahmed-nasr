#include "saveGame.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parseGameName(char* data) {
    int ret = 0;
    int cr = 0;

    char newstring[255];
    int ncr = 0;
    while (data[cr] != '\0' && data[cr] != '\n') {
        newstring[ncr++] = data[cr++];
    }
    newstring[ncr] = '\0';
    char* tmpstring = newstring;
    return tmpstring;
}

int SaveBoard(struct Board* B, char* filename, char* gameprename) {
    FILE* fgames, * newfgames;///Files pointers of games names
    if (!(fgames = fopen("games.txt", "r"))) {
        fgames = fopen("games.txt", "w");
        fclose(fgames);
        fgames = fopen("games.txt", "r");
    }
    char* gamename = gameprename;
    
    
    
    newfgames = fopen("newgames.txt", "w");
    if (fgames == NULL || newfgames == NULL) {
        return -1;
    }


    FILE* fsgames, * newfsgames;///Files pointers of games structures
    if (!(fsgames = fopen(filename, "rb"))) {
        fsgames = fopen(filename, "wb");
        fclose(fsgames);
        fsgames = fopen(filename, "rb");
    }


    newfsgames = fopen("newgames_structures.txt", "wb");
    if (fsgames == NULL || newfsgames == NULL) {
        return -1;
    }




    char buffer[255];
    ///Copying before score
    struct Board temp_board;
    int found = 0;

    while (!feof(fgames)) {
        fgets(buffer, 255, fgames);///name of game
        fread(&temp_board, sizeof(struct Board), 1, fsgames);///struct of a game


        if (feof(fgames))break;
        if (strcmp(parseGameName(buffer), gamename) == 0) {///No duplicate struct
            found = 1;


            fprintf(newfgames, "%s\n", gamename);
            fwrite(B, sizeof(struct Board), 1, newfsgames);
            continue;
        }

        fprintf(newfgames, "%s", buffer);
        fwrite(&temp_board, sizeof(struct Board), 1, newfsgames);
    }

    if (!found) {
        fprintf(newfgames, "%s\n", gamename);
        fwrite(B, sizeof(struct Board), 1, newfsgames);
    }


    ///Replace names files
    fclose(newfgames);
    fclose(fgames);
    remove("games.txt");
    rename("newgames.txt", "games.txt");

    ///Replace structs files
    fclose(newfsgames);
    fclose(fsgames);
    remove(filename);
    rename("newgames_structures.txt", filename);
    
}

int comp(char* s1,char*s2) {
    int cr = 0;
    char debg[255];
    debg[0] = s1[0];
    debg[1] = '\0';
    OutputDebugStringA("s1\n");
    while (s1[cr] != '\0' && s2[cr] != '\0') {
        OutputDebugStringA(s1);
        if (s1[cr] != s2[cr])return -1;
        cr++;
    }
    return s1[cr]==s2[cr];
}

int isBoardExist( char* filename, char* gameprename) {

    char* gamename = (gameprename);///Avoid Case sensitive


    FILE* fgames;///names file
    fgames = fopen("games.txt", "r");



    char buffer[255];
    int found = 0;
    int cnt = 0;
    while (!feof(fgames)) {
        fgets(buffer, 255, fgames);
        if (feof(fgames))break;
        if (strcmp(buffer, gamename) == 0) {
            found = 1;
            break;
        }
        cnt++;
    }
    fclose(fgames);

    return found;
}
int LoadBoard(struct Board* B, char* filename, char* gameprename) {

    char* gamename = (gameprename);///Avoid Case sensitive


    FILE* fgames;///names file
    fgames = fopen("games.txt", "r");


    OutputDebugStringA("prename\n");
    OutputDebugStringA(gameprename);
    FILE* fsgames;///structs file
    fsgames = fopen(filename, "rb");

    char buffer[255];
    int found = 0;
    int cnt = 0;
    while (!feof(fgames)) {
        fgets(buffer, 255, fgames);
        if (feof(fgames))break;
        OutputDebugStringA("*");
        OutputDebugStringA(gamename);
        OutputDebugStringA("*");
        OutputDebugStringA(buffer);
        OutputDebugStringA("*");
        if (strcmp(buffer, gamename) == 0) {
            found = 1;
            fseek(fsgames, sizeof(struct Board) * cnt, SEEK_SET);
            int ret = fread(B, sizeof(struct Board), 1, fsgames);

            fclose(fsgames);
            fclose(fgames);
            return ret;
        }
        cnt++;
    }
    fclose(fsgames);
    fclose(fgames);

    return 0;
}

int LoadGame(struct Board* B, struct Player* P1, struct Player* P2, int* turns, char* filename, char* gameprename) {
    
    int state = LoadBoard(B, filename, gameprename);
    if (state <= 0)return -1;
    for (int i = 0;i < B->height;i++) {
        for (int j = 0;j < B->width;j++) {

            if (B->board[i][j] == P1->id)P1->turns_played++;
            if (B->board[i][j] == P2->id)P2->turns_played++;
        }
    }
    *turns = (P1->turns_played) + (P2->turns_played);
    UpdateScore(B, P1);
    UpdateScore(B, P2);

    return 0;
}

int GetNoSaved() {
    FILE* fgames;///names file
    fgames = fopen("games.txt", "r");

    if (!fgames)return -1;

    char buffer[255];
    int cnt = 0;
    while (!feof(fgames)) {
        fgets(buffer, 255, fgames);
        if (feof(fgames))break;
        cnt++;
    }
    fclose(fgames);

    return cnt;
}

int DeleteBoard(char* filename, char* gameprename){
    FILE* fgames, * newfgames;///Files pointers of games names
    if (!(fgames = fopen("games.txt", "r"))) {
        return -1;
    }
    char* gamename = gameprename;



    newfgames = fopen("newgames.txt", "w");
    if (fgames == NULL || newfgames == NULL) {
        return -1;
    }


    FILE* fsgames, * newfsgames;///Files pointers of games structures
    if (!(fsgames = fopen(filename, "rb"))) {
        fsgames = fopen(filename, "wb");
        fclose(fsgames);
        fsgames = fopen(filename, "rb");
    }


    newfsgames = fopen("newgames_structures.txt", "wb");
    if (fsgames == NULL || newfsgames == NULL) {
        return -1;
    }




    OutputDebugStringA("Delete");
    OutputDebugStringA(gamename);
    OutputDebugStringA("*\n");
    char buffer[255];
    ///Copying before score
    struct Board temp_board;
    int found = 0;

    while (!feof(fgames)) {
        fgets(buffer, 255, fgames);///name of game
        fread(&temp_board, sizeof(struct Board), 1, fsgames);///struct of a game


        if (feof(fgames))break;
        if (strcmp(buffer, gamename) == 0) {///No duplicate struct
            OutputDebugStringA(buffer);
            OutputDebugStringA("*");
            found = 1;


            continue;
        }

        fprintf(newfgames, "%s", buffer);
        fwrite(&temp_board, sizeof(struct Board), 1, newfsgames);
    }



    ///Replace names files
    fclose(newfgames);
    fclose(fgames);
    remove("games.txt");
    rename("newgames.txt", "games.txt");

    ///Replace structs files
    fclose(newfsgames);
    fclose(fsgames);
    remove(filename);
    rename("newgames_structures.txt", filename);

}