//
// Created by zou on 11/10/23.
//
#include <iostream>
#include <ikos/core/number/f_number.hpp>
#include <mpfr.h>

using F = ikos::core::FNumber;

/// \brief Constructor
void testConstruct(){
  float b=12.3;
  mpfr_t m;
  mpfr_init2(m,24);
  mpfr_set_flt(m,12.4,MPFR_RNDA);
  // From float
  F f(b);
  // From mpfr_t
  F g(m,MPFR_RNDA);
  // From FNumber
  F h(g);
  // FNumber=FNumber
  h=f;
  f.display();
  g.display();
  h.display();
}

/// \brief +=, -+, +, -, *, / and so on
void testOverwriteOperator(){
  float f=1;
  mpfr_t m;
  mpfr_init2(m,24);
  mpfr_set_flt(m,0.5,MPFR_RNDN);

  mpfr_t n;
  mpfr_init2(n,53);
  mpfr_set_d(n,0.5,MPFR_RNDN);

  mpfr_t o;
  mpfr_init2(o,113);
  mpfr_set_d(o,0.5,MPFR_RNDN);

  // From mpfr_t
  F M(m,MPFR_RNDN); // 24
  F N(n,MPFR_RNDN); // 53
  F O(o,MPFR_RNDN); // 113
//  M+=N;
//  M.display();
//  N+=M;
//  N.display();
  N+=f;
  N.display();
  N-=f;
  N.display();
  N*=f;
  N.display();
  N/=f;
  N.display();

  float b=0;
  N/=b;
  N.display();
  //N++;
  //N.display();
}

void testTwoFNoperator(){
  float b=3.6;
  mpfr_t m;
  mpfr_init2(m,53);
  mpfr_set_flt(m,1.5,MPFR_RNDN);

  mpfr_t n;
  mpfr_init2(n,24);
  mpfr_set_d(n,2,MPFR_RNDN);

  F M(m,MPFR_RNDN);
  F N(n,MPFR_RNDN);
//  f.display();
//  f.setFN(n,24,MPFR_RNDA);
//  f.display();
  F temp;
  temp=M+N;
  temp.display();
  temp=N+M;
  temp.display();
  temp=b+M;
  temp.display();
  temp=M+b;
  temp.display();

}

int main() {
  testTwoFNoperator();
  return 0;
}
