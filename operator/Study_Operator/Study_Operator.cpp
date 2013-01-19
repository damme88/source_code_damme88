// Study_Operator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct  {
  int a;
  int b;
} PS;

ostream& operator<< (ostream &os, PS p);  // dinh nghia << cho doi tuong PS
istream& operator>> (istream & is, PS &p); // din nghia >> cho mot doi tuong PS

int uscln(int x, int y);  // Ham tin uoc chung lon nhat cua mot so

PS rutgon(PS p);          // ham rut gon phan so . ham nay se goi ham ucln
PS operator +(PS p1, PS p2);  // dinh nghia phep toan + cho 2 lop
PS operator -(PS p1, PS p2);  // dinh nghia phep toan - cho 2 lop
PS operator *(PS p1, PS p2);  // dinh nghia phep toan * cho 2 lop 
PS operator /(PS p1, PS p2);  // dinh nghia phep toan / cho 2 lop

ostream& operator << (ostream& os, PS p) {  // toan tu << ung voi doi tuong PS se thu hien 
  os << p.a << '/' << p.b;                  // viec in ra mot phan so co dang a/ b
  return os;                                // do do neu ta co command dang cout << p (p la mot PS)
}                                           // thi result = a/b

istream& operator >> (istream& is, PS &p) {  // nguoc lai toan tu >> voi doi tuong PS 
  cout << "\nNhap tu so =  ";                // se thuc hien viec nhap tu so va mau so cho PS
  is >> p.a;
  cout << "\nNhap mau so = ";
  is >> p.b;
  return is;
}

int uscln(int x, int y) {
  x = abs(x); // Lay gia tri tuyet doi 
  y = abs(y);
  if(x*y == 0) return 1;
  while ( x!= y) {
    if (x > y)
      x -= y;   // x = x -y;
    else
      y -= x;
  }
  return x;
}

PS rutgon(PS p) {
  PS q;
  int x;
  x= uscln(p.a, p.b);
  q.a = p.a/x;
  q.b = p.b/x;
  return q;
}

PS operator +(PS p1, PS p2) {  // dinh nghia phep cong cho 2 doi tuong PS
  PS q;
  q.a = p1.a*p2.b + p2.a*p1.b;
  q.b = p1.b*p2.b;
  return rutgon(q);
}

PS operator -(PS p1, PS p2) {
  PS q;
  q.a = p1.a*p2.b - p2.a*p1.b;
  q.b = p1.b*p2.b;
  return rutgon(q);
}

PS operator *(PS p1, PS p2) {
  PS q;
  q.a = p1.a*p2.a;
  q.b = p1.b*p2.b;
  return rutgon(q);
}

PS operator /(PS p1, PS p2) {
  PS q;
  q.a = p1.a*p2.b;
  q.b = p1.b*p2.a;
  return rutgon(q);
}

void main()
{
  PS p, q, z, u, v;
  PS s;
  cout << "Nhap cac phan so: " << endl;
  cout << "Nhap phan so p = "<< endl;
  cin >> p;  // Se goi den ham operator >>
  cout << "NHAP phan so q = " << endl;
  cin >> q;
  cout << "Nhap phan so z = " << endl;
  cin >> z;
  cout << "Nhap phan so u = " << endl;
  cin >> u;
  cout << "Nhap phan so v = " << endl;
  cin >> v;
  s = (p - q*z)/(u+v);
  cout << " phan so s = (p - q*z)/(u+v) co gia tri =  " << s;  // goi den ham operator <<
  _getch();
}



