// Type_Casting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//
//class CBase {
//  virtual void dummy() {;}
//};
//
//class Derived : public CBase {
//private:
// int a;
//};
//
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//  try {
//    CBase *pba = new Derived;
//    CBase *pbb = new CBase;
//    Derived *pd;
//    pd = dynamic_cast <Derived*> (pba);
//    if (pd == 0) {
//      cout << "NULL pointer on first type_cast " << endl;
//    }
//    pd = dynamic_cast<Derived *> (pbb);
//    if (pd == 0) {
//      cout << "NULL pointer on second type_cast" << endl;     // this case will error
//    }
//  } catch (exception& e) {
//    cout << "Exception : " << e.what();
//  }
//  _getch();
//	return 0;
//}


// typeid
//#include <iostream>
#include <typeinfo>
using namespace std;

int main () {
  int * a,b;
  a=0; b=0;
  if (typeid(a) != typeid(b))
  {
    cout << "a and b are of different types:\n";
    cout << "a is: " << typeid(a).name() << '\n';
    cout << "b is: " << typeid(b).name() << '\n';
  }
  _getch();
  return 0;
}
