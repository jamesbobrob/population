// my first program in C++
#include <iostream>
#include <cmath>
#include <cfloat>

#define MONEY_ROUNDING    /* Force rounding of doubles */
#define MONEY_DECIMALS  2   /* 2 decimals for money data */
#include "money.h"


#include "pop.h"

using namespace std;

int main()
{
  long seed=-5123L;
  float x;
  Person p;
  
  ran3(&seed);
  x=ran3(&seed);
  p.salary=36000;
  cout << "Hello random World!"<<x;
  cout << "Salary = "<< p.salary;
  return 0;
}