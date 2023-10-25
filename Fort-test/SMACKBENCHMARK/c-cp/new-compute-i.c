// @expect verified

// #include "smack.h" //<assert.h>
#include <stdio.h>
int main() {
    int x = 10;
    int y = 1;
    int z;
    z  = x / (y - 1);
//    assert(z == 30);
    return z;
}
