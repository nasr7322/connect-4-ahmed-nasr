#include "storeRank.h"

#include <windows.h>

int createFile(char* filename) {

    FILE* fp;

    fp = fopen(filename, "w");

    if (fp == NULL) {
        return -1;
    }

    fclose(fp);
    return 0;
}

int parseScore(char* data) {
    int ret = 0;
    int cr = 0;
    while ('0'<=data[cr]&&data[cr] <= '9') {
        if (data[cr] == '\0')return -1;
        ret *= 10;
        ret += data[cr] - '0';
        cr++;

    }
    return ret;
}

char* parseName(char* data) {
    int ret = 0;
    int cr = 0;
    while (data[cr] != '=') {
        if (data[cr] == '\0')return "";
        cr++;

    }
    cr++;
    char newstring[255];
    int ncr = 0;
    while (data[cr] != '\0' && data[cr] != '\n') {
        newstring[ncr++] = data[cr++];
    }
    newstring[ncr] = '\0';

    char* tmpstring = newstring;
    return tmpstring;
}



int addScore(char* prename, int score, char* filename) {
    ///char* name = lower(prename);///To avoid case sensitive

    char* name = prename;
    FILE* newfp, * fp;
    fp = fopen(filename, "r");
    if (!fp ) {
        fp= fopen(filename, "w");
        fclose(fp);
        fp = fopen(filename, "r");
    }
    newfp = fopen("newscore.txt", "w");
    if (fp == NULL || newfp == NULL) {
        return -1;
    }
    int crscore = 1e9;
    char buffer[255];
    ///Copying before score
    int found = 0;
    while (!feof(fp) && crscore >= score) {
        fgets(buffer, 255, fp);
        if (feof(fp))break;
        crscore = parseScore(buffer);
        if (crscore < score)break;
        char* crname = parseName(buffer);
        if (strcmp(crname, name) == 0)found = 1;

        fprintf(newfp, "%s", buffer);

    }
    ///Adding score
    if (!found)
        fprintf(newfp, "%d=%s\n", score, name);
    found = 1;
    char* crname = parseName(buffer);
    if (!feof(fp) && strcmp(crname, name) != 0)
        fprintf(newfp, "%s", buffer);

    ///Copying after score
    while (!feof(fp)) {
        fgets(buffer, 255, fp);
        if (feof(fp))break;
        char* crname = parseName(buffer);
        printf("%s -> %s*\n", crname, name);
        if (strcmp(crname, name) == 0)continue;

        fprintf(newfp, "%s", buffer);
    }



    fclose(newfp);
    fclose(fp);
    remove(filename);
    rename("newscore.txt", filename);



    return 0;
}



int getScore(char* prename, char* filename) {
    char* name = lower(prename);///Avoid Case sensitive


    FILE* fp;
    fp = fopen(filename, "r");

    char buffer[255];
    int found = 0;
    int score = -1;
    while (!feof(fp)) {
        fgets(buffer, 255, fp);
        if (feof(fp))break;
        char* crname = parseName(buffer);
        if (strcmp(crname, name) == 0) {
            found = 1;
            score = parseScore(buffer);
            break;
        }
    }

    return score;
}

int getScoreByIndex(int idx, char* filename) {
    FILE* fp;
    fp = fopen(filename, "r");
    if (!fp)return -1;
    char buffer[255];
    int found = 0;
    int cr = 0;
    int score = -1;
    while (!feof(fp)) {
        fgets(buffer, 255, fp);
        if (feof(fp))break;
        if (cr == idx) {
            found = 1;
            score = parseScore(buffer);
            break;
        }
        cr++;
    }
    fclose(fp);

    return score;
}


char* getNameByIndex(int idx, char* filename) {

    FILE* fp;
    fp = fopen(filename, "r");
    char buffer[255];
    int found = 0;
    int cr = 0;
    char *name;
    while (!feof(fp)) {
        fgets(buffer, 255, fp);
        if (feof(fp))break;
        if (cr == idx) {
            found = 1;
            name = parseName(buffer);
            break;
        }
        cr++;
    }
    OutputDebugStringA(name);
    OutputDebugStringA("*\n");

    //fclose(fp);
    return name;
}
