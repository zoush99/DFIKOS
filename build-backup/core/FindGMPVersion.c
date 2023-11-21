
      #include <assert.h>
      #include <stdio.h>
      #include <gmp.h>

      int main() {
        mpz_t i, j, k;
        mpz_init_set_str(i, "1a", 16);
        mpz_init(j);
        mpz_init(k);
        mpz_sqrtrem(j, k, i);
        assert(mpz_get_si(j) == 5 && mpz_get_si(k) == 1);
        printf("%s", gmp_version);
        return 0;
      }
    