
#include "stdafx.h"

/******************************************************************************
* Function name		: CreateFolder
* Purpose			    : Create a folder when you have a path
* Input Param		  : Path La mot bien kieu char de luu duong dan noi tao folder
* Output Param		: return = 1 is success
*                 : return = 0 is fail
* Language			  : Visual C++ 2008 - Windows console
* OS				      : Windows 7-Windows Server-Windows XP...
* Writer			    : Damme88 - Developer - Phamtoanbonmat@gmail.com
* Time				    : 22h14p Wednesday 11/04/2012
******************************************************************************/

BOOL CreateFolder(char Path[MAX_PATH]) {
	int   i = 0;
	BOOL  ret = 0;
	// Khai bao mot mang kieu TCHAR de lay cac ky tu Path
	_TCHAR PATH[MAX_PATH];
	for(i = 0;  i<= strlen((const char *)Path); i++) {
		// Phai thuc hien ep kieu tu char sang _TCHAR
		PATH[i] = (_TCHAR)Path[i] ;
	}
    // mang TCHAR phu hop voi kieu du kieu con tro LPCWSTR
	ret = CreateDirectory(PATH, NULL) ;
	return ret ;
}


/******************************************************************************
* Function Name		  : Ham main
* Purpose			      : Ham chinh, goi cac ham con 
* Language			    : Visual C++ 2008 - Windows console.
* OS				        : Windows 7-Windows Server-Windows XP...
* Writer			      : Damme88- Deverloper - Phamtoanbonmat@gmail.com
* Time				      : 22h14p Wednesday 11/04/2012
******************************************************************************/
void main() {
	BOOL check = 0;
	char FolderPath[MAX_PATH];
	char FolderName[MAX_PATH];
	int i = 0 ;
Lap:
	cout << " \n\t Enter Path to Create folder " ;
	cout << " \n\t add  character '\\'  on string end \n\t FolderPath = " ;
	cin.getline((char*)FolderPath,MAX_PATH-1);
	// Ham access thuc hien kiem tra xem duong dan co ton tai hay khong 
	// Ham nay duoc dinh nghia trong thu vien <io.h>
	check = access(FolderPath,0) ;
	if (check == -1) {
		cout << "\n\t This Path is not exist \n\t Please Enter again " ;
		goto Lap ;
	}
	cout << "\n\t Input Ten folder can tao. \n\t Folder Name = " ;
	cin.getline(FolderName,MAX_PATH-1);

	// thuc hien noi ten folder vao chuoi chua duong dan can tao folder 
	strcat((char*)FolderPath,(const char*)FolderName);

    // Goi ham thuc hien viec tao folder 
	check = CreateFolder(FolderPath) ;
	if (check == 1) {
		cout << "\n\t Create new folder successful " ;
	} else {
		  cout << "\n\t Create new folder is fail" ; 
	    cout << "\n\t 1.The cause can be this folder do da ton tai" ;
		  cout << "\n\t 2.This Path is not correct " ;
	}
	getch();
}

