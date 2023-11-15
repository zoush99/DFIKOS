//
// Created by zou on 11/15/23.
//
#include <iostream>
#include <ikos/core/number/bound.hpp>
#include <ikos/core/number/q_number.hpp>
#include <ikos/core/number/z_number.hpp>
#include <ikos/core/number/f_number.hpp> // By zoush99

using z_number=ikos::core::ZNumber;
using f_number=ikos::core::FNumber;
using Bound=ikos::core::Bound<f_number>;

/// \brief Bound b(a)
void testConstructor()
{
  float f;
  f=1.2;
  int a =0;
  f_number F(f);
  Bound b(F);
  Bound bb(f);
  f_number A(a);
  Bound AA(a);
//  f_number G;
//  G=f;
//  G.display();
//  b.displayF();
}

/// \brief
void testMemberFunc(){
  double d;
  d=3;
  f_number F(d);
  Bound B(F);
  B=4;
  B.display();
}

int main()
{
  testMemberFunc();
  return 0;
}