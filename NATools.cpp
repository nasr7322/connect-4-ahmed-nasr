#include "NATools.h"
#include <ctype.h>

int Min(int x, int y) {
    return (x < y) ? x : y;
}
int Max(int x, int y) {
    return (x > y) ? x : y;
}

char* lower(char* s) {
    int cr = 0;
    while (s[cr] != '\0') { s[cr] = tolower(s[cr++]); }
    return s;

}
