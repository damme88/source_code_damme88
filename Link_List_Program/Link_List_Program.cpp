

// Link_List_Program.cpp : Defines the entry point for the console application.
/***************************************************************************************
* Name Program	: Mô hình Danh Sách Liên Kết -Link List Program LLP
* Purpose		: Quản lý thông tin nhiều phần tử theo kiểu một danh sách liên kết
* Detail		: Danh sách liên kết quản lý phần tử thông qua con trỏ đầu và cuối 
*				: Tiết kiệm việc việc sử dụng vùng nhớ và có sự quản lý chặt chẽ
* Writer		: Phạm Thanh Toàn Developer- Damme88
* Timer			: 23h 23p 23s - Sunday05/12/2011
* Language		: C kết hợp với C ++
* Environment	: Visual C 2008 - Windows XP - Window 7 - 32bit(X86)
*
***************************************************************************************/

#include "stdafx.h"
#include "Struct.h"
#include "Function.h"

void main ()
{
lap1:
	MEMBER member;
	int a,b,c,d ;
	cout <<"\n\n\t Moi ban nhap thong tin member: Please, write information for member ";
	cout <<"\n\n\t Name: ";
	cin.getline (member.name,18);
	cout <<"\n\n\t Age: ";
	cin>> member.age;
	cout <<"\n\n\t Sex: ";
	cin.ignore();
	cin.getline (member.sex,8);
	cout <<"\n\n\t Company: ";
	cin.getline (member.company,18);
	cout <<"\n\n\t Country: ";
	cin.getline (member.country,25);
	cout<<"\n\t An 1 neu muon chen vao dau list va an phim 2 neu muon cuoi list ";
	cin >> b ;
	if(b==1){
		InsertHead(member.name,member.age,member.sex,member.company,member.country) ;
		cout <<"\n\tDanh sach moi la : " <<endl;
		Print();
	}
	else{
		InsertEnd(member.name,member.age,member.sex,member.company,member.country);
		cout <<"\n\n\tDanh sach moi la "<<endl;
		Print();
	}
lap2:
		cout <<"\n\n\t An: 1	Neu muon tiep tuc them moi mot member \n\t An: 2 Neu muon xoa 1 phan tu nao do \n\t An: 3	Neu muon dung " ;
		cout <<"\n\n\t Key=" ;
		cin >> c ;
	if (c==1){
		cin.ignore();
		goto lap1;
	}
	if(c==2){
		cout <<"\n\t	Moi ban nhap vi tri phan tu can xoa : ";
		cin >> d;
		Clear(d);
		cout <<"\n\t	Danh sach moi la : " <<endl;
		Print();
		goto lap2 ;
	}
	if(c!=1&&c!=2)
		goto kt ;
kt:
	cout<<"\n\t		Toan bon mat xin chao cac ban - bye bye" ;
	getch();
return ;
}



