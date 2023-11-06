// @expect verified

// #include "smack.h" //<assert.h>
#include <stdio.h>
int main() {
    float x = 10;
    float y = 1;
    float z;
    z = x + (x + 1);
    z = z / x;
    z  = x / (y - 1);
//    assert(z == 30);
    return z;
}
