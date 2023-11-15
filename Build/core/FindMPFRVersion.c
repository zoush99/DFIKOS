
      #include <stdio.h>
      #include <mpfr.h>

      int main() {
        mpfr_t x;
        mpfr_init_set_ui(x, 2, MPFR_RNDN);
        printf("%s", mpfr_get_version());
        return 0;
      }
    