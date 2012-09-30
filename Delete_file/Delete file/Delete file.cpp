// Delete file.cpp : Defines the entry point for the console application.

#include "stdafx.h"

/***************************************************************************************
* Function Name			: Delete_File
* Purpose				: Xoa mot file 
* Input Param			: const char * Path_File. Con tro luu duong dan den file 
* Output Param			: Ham ko co tham so dau ra hay return value 
* Writer				: Damme88- Deverloper - Phamtoanbonmat@gmail.com
* Time					: 13h35 phut Sunday 01/04/2012
***************************************************************************************/
void Delete_File(const char * Path_File)
{
	int check=0;
	check = remove(Path_File);
	if(check == 0){
		cout << "\n\t Ok File cua ban da duoc xoa ";
	}
}


/***************************************************************************************
* Function Name		: Ham main
* Purpose			: Ham chinh, goi cac ham con 
* Writer			: Damme88- Deverloper - Phamtoanbonmat@gmail.com
* Time				: 13h35 phut Sunday 01/04/2012
***************************************************************************************/
int main()
{
	const char * Path_File ;
	char Path[127];
	Path_File=Path ;
	int del=0;
	cout << "\n\t Moi ban nhap duong dan den file can xoa: Path = " ;
	cin.getline(Path,126);
	cout << "\n\t Ban hay an phim 1 neu thuc su muon xoa file " ;
	cin >> del ;
	if(del == 1){
		Delete_File(Path_File);
	}
	else{
		cout << "\n\t File cua ban chua duoc xoa " ;
	}
	getch ();
}
