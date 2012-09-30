// xu ly doc file bang C++

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std; 

void main()
{	    
	// khai bao mot doi tuong thuoc lop ifstream
	// phuong thuc nay mo file theo duong dan tuong doi
	// file Text phai co san va nam trong folder ReadFile Cua project
	ifstream stream1("Text.txt"); 
	// Kha bao mot mang ky tu de luu cac ky tu se doc duoc 	                              
    char save[150]; 
	// Thuc hien kiem tra ket qua cua stream 
    if(!stream1){
		cout << "Khong the mo file" << endl; 
	}
    else{
		// kiem tra ky tuc do duoc voi ky tu ket thuc file
		while(!stream1.eof())  
		{   
			// neu khac nhau thi gui ky tu nhan duoc duoc den mang save
			stream1 >> save;  
			// in ky tu do ra man hinh
			cout << save <<" ";  
		}
	}       
    getch();
}