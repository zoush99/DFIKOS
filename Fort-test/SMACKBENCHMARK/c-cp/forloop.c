// @expect verified
// @flag --unroll=11

#include <stdio.h>

int main(void) {
    int x = 0;
    for (int i = 0; i < 10; i++) {
        x += 5;
    }
    if (x != 50)
    	return 1;
    else{
    	x = x + 1 / 3;
    	return x;
    }
}

