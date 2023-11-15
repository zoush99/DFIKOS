
      #include <assert.h>
      #include <stdio.h>
      #include <string.h>
      #include <sqlite3.h>

      int main() {
        assert(strcmp(SQLITE_VERSION, sqlite3_libversion()) == 0);
        printf("%s", sqlite3_libversion());
        return 0;
      }
    