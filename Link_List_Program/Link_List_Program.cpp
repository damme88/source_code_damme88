
#include "stdafx.h"
#include "Struct.h"
#include "Function.h"

void main () {
lap1:
	MEMBER member;
	int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;
	cout <<"\n\n\t Please, enter information for member ";
	cout <<"\n\n\t Name: ";
	cin.getline (member.name, 18);
	cout <<"\n\n\t Age: ";
	cin>> member.age;
	cout <<"\n\n\t Sex: ";
	cin.ignore();
	cin.getline (member.sex, 8);
	cout <<"\n\n\t Company: ";
	cin.getline (member.company, 18);
	cout <<"\n\n\t Country: ";
	cin.getline (member.country, 25);
	cout<<"\n\t press 1 key to insert head ";
	cin >> b ;
	if(b == 1) {
		InsertHead(member.name, member.age, member.sex,
               member.company, member.country) ;
		cout <<"\n\t New List : " <<endl;
		Print();
	} else {
		InsertEnd(member.name, member.age, member.sex,
              member.company, member.country);
		cout <<"\n\n\t New List "<<endl;
		Print();
	}
lap2:
		cout <<"\n\n\t Press 1 key to continue add new"<< endl;
    cout << "Press 2 to clear any element"<< endl;
    cout << "Press 3 key to stop"<<endl;
		cout <<"\n\n\t Key = " ;
		cin >> c ;
	if (c == 1){
		cin.ignore();
		goto lap1;
	}
	if(c == 2){
		cout <<"\n\t Please, enter index of clear element";
		cin >> d;
		Clear(d);
		cout <<"\n\t	New List" <<endl;
		Print();
		goto lap2 ;
	}
	if(c !=1 && c != 2)
		goto kt ;
kt:
	cout<<"\n\t		Damme88- bye bye" ;
	getch();
  return ;
}



