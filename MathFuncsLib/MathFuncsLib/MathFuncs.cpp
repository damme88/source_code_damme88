
#include "MathFuncsLib.h"
#include <stdexcept>
#include <Windows.h>

using namespace std;

namespace MathFuncs {
  
  double MyMathFuncs::Add(double a, double b) {
    return a+b;
  }

  double MyMathFuncs::Subtract(double a, double b) {
    return a-b;
  }
  double MyMathFuncs::Multiply(double a, double b) {
    return a*b;
  }

  double MyMathFuncs::Divide(double a, double b) {
    if (b == 0) {
      return 0.0;
    } else {
      return a/b;
    }
  }
  double CheckMax(double a, double b) {
   return a >b ? a : b; 
  }

  double CheckMin(double a, double b) {
    return a < b ? a : b;
  }
}