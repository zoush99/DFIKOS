// @expect verified

// #include "smack.h" //<assert.h>
#include <stdio.h>
int main() {
    double x = 10;
    double y = 1;
    double z;
    z  = x / (y - 1);
//    assert(z == 30);
    return z;
}
