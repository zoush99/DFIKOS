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

void testConstructor()
{
  float f;
  f=1.2;
  f_number F(f);
  Bound b(F);
//  b.displayF();
}

int main()
{
  testConstructor();
  return 0;
}