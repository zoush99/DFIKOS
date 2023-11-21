
      #include <stdio.h>
      #include <ppl_c.h>

      int main() {
        const char* version;
        ppl_initialize();
        ppl_version(&version);
        printf("%s", version);
        return ppl_finalize();
      }
    