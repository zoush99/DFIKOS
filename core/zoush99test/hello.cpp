//
// Created by zou on 11/10/23.
//
#include <iostream>
#include <ikos/core/number/f_number.hpp>
#include <mpfr.h>

int main() {
  int a;
  double b=12.3;
  mpfr_t c;
  mpfr_init(c);
  mpfr_set_d(c,b,MPFR_RNDN);
  using F=ikos::core::FNumber;
  F f(c);
  //F e(b);
  mpfr_printf("fvalue: ",f.mpfvalue());
  //mpfr_printf("evalue: ",e.mpfvalue());
  std::cout << "hello" << std::endl;
  return 0;
}