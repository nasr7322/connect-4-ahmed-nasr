#include "storeRank.h"



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
    while (data[cr] != '=') {
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
    printf("infunc=%s\n", "initial");
    int ncr = 0;
    while (data[cr] != '\0' && data[cr] != '\n') {
        newstring[ncr++] = data[cr++];
    }
    newstring[ncr] = '\0';
    printf("infunc=%s\n", newstring);
    char* tmpstring = newstring;
    return tmpstring;
}



int addScore(char* prename, int score, char* filename) {
    char* name = lower(prename);///To avoid case sensitive


    FILE* newfp, * fp;
    fp = fopen(filename, "r");
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