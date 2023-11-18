//
// Created by zou on 11/18/23.
//

#include <ikos/core/number/bound.hpp>
#include <ikos/core/number/f_number.hpp> // By zoush99
#include <ikos/core/number/q_number.hpp>
#include <ikos/core/number/z_number.hpp>
#include <ikos/core/domain/numeric/operator.hpp>
#include <ikos/core//domain/machine_int/operator.hpp>
#include <iostream>

using namespace ikos::core::numeric;

using ZNumber = ikos::core::ZNumber;
using FNumber = ikos::core::FNumber;
using QNumber=ikos::core::QNumber;
using BoundZ=ikos::core::Bound<ZNumber>;

using NumberT=FNumber;
void testFNumberOpeator(){
  FNumber E(1,3);
  FNumber F(2,3);
//  E.display();
//  F.display();
  F=apply_bin_operator(BinaryOperator::Add,E,F);

}

int main()
{
  testFNumberOpeator();
  return 0;
}