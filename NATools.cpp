#include "NATools.h"
#include <ctype.h>


int Min(int x, int y) {
    return (x < y) ? x : y;
}
int Max(int x, int y) {
    return (x > y) ? x : y;
}

char* lower(char* pres) {///Delete
    int cr = 0;
    char s[255];
    while (pres[cr] != '\0') {///Copy
        s[cr] = tolower(pres[cr++]);
    }
    s[cr] = '\0';
    return s;

}
