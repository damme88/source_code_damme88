// Khai bao cac ham xu ly voi mo hinh STACK

#include "Struct.h"
#include "stdafx.h"

DATA* PHead;	    // Con tro PHead se tro vao dau cua ngan xep
DATA* PEnd;		  // Con tro PEnd se tro vao cuoi cua ngan xep

/******************************************************************************
* Function Name			: Create
* Data Type				  : Kiểu dữ liệu cấu trúc DATA 
* Purpose				    : Nhận các thông tin nhập vào và tạo vùng nhớ chứa nó. 
* Input Parammeter  : Có 1 đối số đầu vào kieu int 
* Return Value			: Trả lại giá trị là 1 con trỏ kiểu DATA trỏ đến địa chỉ 
*                     của vùng nhớ lưu thông tin.
* Language				  : Visual C ++ 2008.
* Writer				    : Phạm Thanh Toàn Developer - Damme88.
* Time					    : 23h 45p 23s - Sunday 18/12/2011
******************************************************************************/

DATA *Create(int Val)
{
 DATA *Ptem;			// Con tro Ptem se nhan data dau vao
 Ptem= new DATA[1];    
 (Ptem->Value)=Val;
 return Ptem ;         // no se luu data vao 1 vung nho ma no dang tro den
}



/******************************************************************************
* Function Name			: Push 			 
* Purpose				    : Ham push thực hiện đẩy data vào một vùng nhớ STACK.
* Input Parammeter	: Có 1 đối số đầu vào kiểu int. 
* Return Value			: Không có giá trị trả lại.
* Language				  : Visual C ++ 2008.
* Writer				    : Phạm Thanh Toàn Developer - Damme88.
* Time					    : 23h 45p 23s - Sunday 18/12/2011.
******************************************************************************/

void Push(int Val) {
	DATA *Ptem2;
    Ptem2 = Create(Val);
	if (PHead == NULL) {
	  PHead = Ptem2;
	  PEnd=PHead;
	  PEnd->Next;
	} else {
	    Ptem2->Next = PHead;
	    PHead = Ptem2;
	}
}



/******************************************************************************
* Function Name			: Pop 			 
* Purpose				    : Ngược với Push- Get Data 
* Input Parammeter	: Nothing  
* Return Value			: Return value in Stack
* Language				  : Visual C ++ 2008.
* Writer				    : Phạm Thanh Toàn Developer - Damme88.
* Time					    : 23h 45p 23s - Sunday 18/12/2011
******************************************************************************/

int Pop() {
	int Value;
	DATA *Ptem4;
	Ptem4 = PHead;
	PHead = PHead->Next;
	Value = Ptem4->Value;
	delete Ptem4;
	return Value;
}


/******************************************************************************
* Function Name			: Convert_To_Binary			 
* Purpose				    : Apply cho mô hình Stack , convert decimal to binary.
                    : Show a binary string to screen
* Input Parammeter  : Nothing
* Return Value			: Nothing.
* Language				  : Visual C ++ 2008.
* Writer				    : Phạm Thanh Toàn Developer - Damme88.
* Time					    : 23h 45p 23s - Sunday 18/12/2011
******************************************************************************/

void Convert_To_Binary() {
  int Value ;
  int Value2;
  int result_du;
  int result_thuong;
  int icount= 0;
  int irun=0;
  int RTem;
  int Option;
Loop:
	cout << "\n\t Moi ban nhap so thap phan can doi sang so nhi phan ";
	cin >> Value;
	Value2 = Value ;
	icount = 0 ;
	do{
		result_du = Value%2;
		result_thuong = Value/2;
		Push(result_du);
		icount++;
		Value = result_thuong;
	}
	while(result_thuong != 0);
	cout << "\n\t So nhi phan cua " << Value2 << " la : " << " 0";
	for (irun = 1; irun<= icount; irun++) {
		RTem=Pop() ;
		cout << " "<<RTem;
	}
	cout << "\n\t Do you continue with other value ?";
  cout << "\n\t press 1 key to contiune and press other key to stop ";
	cin >> Option ;
	if (Option == 1) {
		goto Loop;
  } else {
		  cout << "\n\t Xin chao ";
		  return;
	}
}

