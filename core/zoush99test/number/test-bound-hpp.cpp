//
// Created by zou on 11/15/23.
//
#include <ikos/core/number/bound.hpp>
#include <ikos/core/number/f_number.hpp> // By zoush99
#include <ikos/core/number/q_number.hpp>
#include <ikos/core/number/z_number.hpp>
#include <iostream>

using ZNumber = ikos::core::ZNumber;
using FNumber = ikos::core::FNumber;
using Bound = ikos::core::Bound< FNumber >;

/// \brief Bound b(a)
void testConstructor() {
  float f;
  f = 1.2;
  int a = 5;
  FNumber F(f);
  Bound b(F);
  Bound bb(f);
  FNumber A(a);
  Bound AA(a);
  AA.display();
}

/// \brief +=,
void testMemberFunc() {
  long double d;
  d = 3;
  FNumber F(d);
  Bound B(F);
//  B.display();  // 3
  Bound A(4);
//  B +=A;
//  B.display();  // 7 53'
//  B=4;
//  B.display();  // 4
//  B+=B;
//  B.display();  // 8
//  B=A.plus_infinity();
//  B.display();  // +oo
//  std::cout<<B.is_finite()<<std::endl;  // 0
//  B=A.minus_infinity();
//  B.display();  // -oo
//  std::cout<<B.is_finite()<<std::endl;  // 0
  B=A+B;
  B.display();
  std::cout<<(A<=B)<<std::endl;
}

int main() {
  testMemberFunc();
  return 0;
}