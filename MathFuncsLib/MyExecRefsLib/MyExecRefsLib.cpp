// MyExecRefsLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MathFuncsLib.h"

void main()
{
   double a = 0.0;
   double b = 0.0;
   unsigned int operation = 0;
   cout << " Enter value for a = ";
   cin >> a;
   cout << "\n Enter value for b = ";
   cin >> b;
   cout << "\n option operation for a, b";
   cout << "\n enter 1 to add \n enter 2 to subtract \n enter 3 to multiply \n enter 4 to divide";
   cout << "\n operation = ";
   cin >> operation;
   if (operation == 1) {
     cout << " a + b = " << MathFuncs::MyMathFuncs::Add(a, b);
   }
   if (operation == 2) {
     cout << " a -b = " << MathFuncs::MyMathFuncs::Subtract(a, b);
   }
   if (operation == 3) {
     cout << " a * b = " << MathFuncs::MyMathFuncs::Multiply(a, b);
   }
   if (operation == 4) {
     if (b == 0) {
       cout << "\n value b is 0: Invalidate";
       return;
     } else {
       cout << " a /b  = " << MathFuncs::MyMathFuncs::Divide(a, b);
     }
   }
  _getch();
}

