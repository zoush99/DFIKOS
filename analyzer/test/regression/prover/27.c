extern void __ikos_assert(int);
extern int __ikos_nondet_int(void);

/*
 * "nested2.c" from InvGen benchmark suite
 */

int main() {
  int i, k, n, l;
  // assume(l>0);
  l = __ikos_nondet_int();
  n = __ikos_nondet_int();
  if (l > 0) {
    for (k = 1; k < n; k++) {
      for (i = l; i < n; i++) {
      }
      for (i = l; i < n; i++) {
        __ikos_assert(1 <= k);
      }
    }
  }
}
