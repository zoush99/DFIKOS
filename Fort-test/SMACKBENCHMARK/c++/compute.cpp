// @expect verified

#include <smack.h>//<cassert>

int main(void) {
    int x = 10;
    int y = 20;
    int z = x + y;
    assert(z == 30);
}
