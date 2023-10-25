// @expect verified

// #include "smack.h" //<assert.h>
#include <stdio.h>
int main() {
    int x = 10;
    int y = 0;
    int z;
    z  = x / y;
//    assert(z == 30);
    return 0;
}
