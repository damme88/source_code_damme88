

/***********************************Prorgram Creat File ***********************
* Program Name    : Program Create File
* Purpose		      : Create a file Text with capacity 
*				          : unit for file capacity : B,KB,MB
* OS			        : Windows XP, Windows 7, Windows 2K
* Language		    : Visual C++ 2008. Windows Console
* Writer		      : Damme88-deve-Phamtoanbonmat@gmail.com
******************************************************************************/

#include "stdafx.h"



/******************************************************************************
* Function Name		  : CreateFile()
* Purpose			      : Create a file with capacity is desired
* Input Param		    : Nothing
* Output Param		  : Nothing
* Language			    : Visual C++ 2008 
* Coding Convention : Google Coding Style.
* Writer			      : Damme88-Phamtoanbonmat@gmail.com
* Time				      : 18/04/2012.
******************************************************************************/

void CreateFile() {
	char file_name [101]={""};
	char level ;
	char path[127]={""};
	unsigned long capacity = 0 ;
	unsigned long i = 0;
	int end = 0;
	int length = 0;
	int key = 0 ;
	cout << "\n\t Moi ban nhap ten File Text kem theo dinh dang .txt \n\t NameFile = " ;
	cin.getline(file_name,100);
	// lay leng cua chuoi de biet so ky tu cua NameFile
	length = strlen(file_name);
	// kiem tra xem 4 ky tu cuoi cung da duoc nhap theo format txt chua 
		if (file_name[length-4]!='.'||
			file_name[length-3]!='t'||
			file_name[length-2]!='x'||
			file_name[length-1]!='t') {
			// neu chua thi se noi them dinh dang .txt vao cuoi
			strcat(file_name,".txt");
		}
again:
	cout << "\n\t Moi ban nhap don vi cho File. B,KB,MB";
	cout << "\n\t Tuong voi cac ky tu viet hoa B,K,M : DV = " ;
	cin.get(level) ;
	cout << "\n\t Moi ban nhap dung luong file can tao.  Capacity =   " ;
	cin >> capacity ;
	cout << "\n\t Moi ban nhap duong dan de tao File.";
	cout << "\n\t Path = " ;
	cin.ignore();
	cin.getline(path,126);
    // thuc hien kiem tra xem ky tu cuoi cua cua Path co ky tu \ hay chua
	end = strlen(path);
	if(path[end-1] != '\\') {
		// neu chua thi se them vao 
		strcat(path,"\\");
	}
	strcat(path, file_name) ;
	// Khai bao doi tuong fp thuoc lop stream cho phep create 1 file
	ofstream fp(path) ;
	// kiem tra xem don vi dung luong nhap vao la gi
	if(level =='B'){
		for(i = 0 ;i <capacity; i++){
			fp << "a" ;
			if((i>0) && (i%500 == 0)) { // chieu dai cua line da = 500 thi xuong dong
				fp << "\n" ;
			}
		}
	} else if (level =='K'){
		for (i = 0;i <(capacity*8);i++) {
			fp << "128character128character128character128character128character128character128character128character128character128character128chara";
			if((i > 0) &&( i%512 == 0)) {
				fp << "\n";
			}
		}
	} else if (level == 'M') {
		for (i = 0; i<(capacity*1024*8); i++) {
			fp << "128character128character128character128character128character128character128character128character128character128character128chara";
			if ((i>0) && (i%512 == 0)) {
				fp <<"\n";
			}
		}
	} else {
		cout << "\n\t  Ban da nhap sai ky don vi. Chu y nhap dung va nhap chu hoa " ;
		cout << "\n\t Ban hay an phim 1 de thuc hien lai. An phim khac neu muon dung ";
		cout << "\n\t Key = " ;
		cin >> key ;
		if (key == 1) {
			goto again ; 
		} else {
		return ;
		}
	}
	cout << "\n\t Ok Creat File Successful" ;
}

void main() {
	CreateFile() ;
	getch();
}

