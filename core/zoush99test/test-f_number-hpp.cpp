//
// Created by zou on 11/10/23.
//
#include <iostream>
#include <ikos/core/number/f_number.hpp>
#include <mpfr.h>

using F = ikos::core::FNumber;

void testConstruct(){
  float b=12.3;
  mpfr_t m;
  mpfr_init2(m,45);
  mpfr_set_d(m,12.4,MPFR_RNDA);
  F f(b);
  F g(m,MPFR_RNDA);
  F h(g);
  h=f;
  f.display();
  g.display();
  h.display();
}

void testOverwriteOperator(){
  float b=12.3;
  mpfr_t m;
  mpfr_init2(m,45);
  mpfr_set_d(m,12.4,MPFR_RNDA);
  F f(b);
  F g(m,MPFR_RNDA);
  F h(g);
  h=f;
  f.display();
  g.display();
  h+=f;
  h.display();
}

int main() {
  testOverwriteOperator();
  return 0;
}
