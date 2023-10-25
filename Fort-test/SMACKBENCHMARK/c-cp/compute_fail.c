// @expect error

// #include "smack.h" //<assert.h>
#include <stdio.h>

int main(void) {
    int x = 10;
    int y = 0;
    int z = x /  y;
//    assert(z != 30);
    return 0;
}
