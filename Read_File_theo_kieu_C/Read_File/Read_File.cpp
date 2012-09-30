// Read_File.cpp : Defines the entry point for the console application.
// Ham doc file theo ngon ngu C (dan xen mot vai cau lenh cua C++)
// Doc lan luot tung ky tu va hien thi ra man hinh ke ca ky tu space
// Su dung mot mang ky tu de luu cac ky tu lai 
// han che do la mang ky tu chi luu duoc 127 ky tu 


#include "stdafx.h"


/***************************************************************************************
* Function Name			: Read_File
* Purpose				: Doc mot file 
* Input Param			: const char * Path_File. Con tro luu duong dan den file 
* Output Param			: Ham ko co tham so dau ra hay return value 
* Writer				: Damme88- Deverloper - Phamtoanbonmat@gmail.com
* Time					: 13h35 phut Sunday 01/04/2012
***************************************************************************************/
void Read_File(const char * Path_File, const char * mode)
{
    
	char save[150] ;
	int i =0 ;
	// ta khai bon 1 con tro co ten la File Process de xu ly file viet tat la fp
	FILE *fp   ;
	int check ;
	// khai bao 1 bien kieu char de lay cac ky tu tu file 
	char ch ;
	// thuc hien mo file bang ham fopen va file duoc mo se duoc tro boi fp 
	fp = fopen (Path_File,mode); 
	if(fp==NULL){
		cout << "\n\t File ban tro den khong ton tai hoac duong dan bi sai." ;
	}
	else {
		// thuc hien lay lan luot cac ky tu trong file thong qua con tro fp
		// va gui ky tu do vao bien ky tu char 
		ch=getc(fp);

		// thuc hien dieu nay lien tuc cho den khi gap ket thuc file hoac bi loi
		// EOF la define de bao hieu ky tu ket thuc file hoac ky tu bat thuoc 
		while(ch!=EOF){
			// khi ky tu nhan duoc con khac EOF thi thuc hien goi ham putchar
			// gui ky tu do ra man hinh		
			putchar(ch);
			// dong thoi luu ky tu lay duoc tu file vao mang ke ca ky tu space
			save[i]=ch ;
			i=i+1 ;
			// thuc hien lay ky tu tiep theo 
			ch =getc(fp) ;
		}
		// ham print nay thuc hien xuong dong 2 lan 
		printf ("\n\n") ;
	}
}


/***************************************************************************************
* Function Name		: Ham main
* Purpose			: Ham chinh, goi cac ham con 
* Writer			: Damme88- Deverloper - Phamtoanbonmat@gmail.com
* Time				: 13h35 phut Sunday 01/04/2012
***************************************************************************************/
void main(void)
{
	const char * Path_File ;
	char Path [127] ;
	Path_File=Path ;
	const char * mode=("r");
	int option=0;
	cout << "\n\t Moi ban nhap duong dan cho file : Path = " ;
	cin.getline(Path,126);
	cout << "\n\t Ban hay thuc hien an phim 1 de doc file\n\t Opntion = " ;
	cin >> option ;
	if(option ==1){
		Read_File(Path_File,mode);
	}
	getch () ;
}
