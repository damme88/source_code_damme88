
#include "stdafx.h"


MEMBER *Makeone(char,int,char,char,char);   
void	InsertHead(char,int,char,char,char);
void	InsertEnd(char,int,char,char,char);
void	Print(void);
void	Clear(int);

/******************************************************************************
* Function Name			: Makeone.
* Data Type				  : Kiểu dữ liệu cấu trúc MEMBER. 
* Purpose				    : Nhận các thông tin nhập vào và tạo vùng nhớ chứa nó. 
* Input Parameter		: Có 5 đối số đầu vào.
* Output Parameter  : Tra ve con tro tro den vung nho luu thong tin. 
* Language				  : Visual C ++ 2008.
* Writer				    : Phạm Thanh Toàn Developer - Damme88.
* Time					    : 23h 23p 23s - Sunday05/12/2011
******************************************************************************/

MEMBER *Makeone(char name[20], int age,
                char sex[10], char company[20],
                char country[50]) {
	MEMBER*TempMemory ;
	TempMemory = NULL;
	TempMemory = (MEMBER*)malloc(sizeof(MEMBER));
	strcpy(TempMemory->name, name);
	TempMemory->age = age;
	strcpy(TempMemory->sex, sex);
	strcpy(TempMemory->company, company);
	strcpy(TempMemory->country, country);
	TempMemory->next = NULL ;
	return TempMemory ;
}


/******************************************************************************
* Function Name			: InsertHead
* Data Type				  : Kiểu Void 
* Purpose				    : Chèn 1 phần tử vào đầu của Danh Sách Liên Kết (LLP)
* Input Parammeter	: Có 5 đối số đầu vào.
* Return Value			: Không Có Giá Trị Trả Lại 
* Language				  : Visual c++ 2008 
* Writer				    : Phạm Thanh Toàn Developer - Damme88.
* Time					    : 23h 23p 23s - Sunday05/12/2011
******************************************************************************/
void InsertHead(char name[20], int age,char sex[10],
                char company[20], char country[50]) {
	MEMBER* temp1 ;
	temp1 = Makeone(name, age, sex, company, country) ;
	if (phead == NULL) {
	phead = temp1 ;
	phead->next = NULL ;
	pend = phead ;
	} else {
	temp1->next = phead ;
	phead = temp1 ;
	}
}


/***************************************************************************************
* Function Name			: InsertHead
* Data Type				: Kiểu Void 
* Purpose				: Chèn 1 phần tử vào cuối của Danh Sách Liên Kết (LLP)
* Input Parammeter		: Có 5 đối số đầu vào.
* Return Value			: Không Có Giá Trị Trả Lại                         
* Writer				: Phạm Thanh Toàn Developer - Damme88.
* Time					: 23h 23p 23s - Sunday05/12/2011
*
***************************************************************************************/
void InsertEnd(char name[20],int age,char sex[10],char company[20],char country[50])
{
	MEMBER*temp2 ;
	temp2=Makeone(name,age,sex,company,country) ;
	if(pend==NULL){
	pend=temp2 ;
	phead=pend ;
	}
	else{
	pend->next=temp2;
	temp2->next=NULL ;
	pend=temp2 ;
	}
}


/***************************************************************************************
* Function Name			: Print
* Data Type				: Kiểu Void 
* Purpose				: In ra màn hình các phần tử của Danh Sách Liên Kết (LLP)
* Input Parammeter		: Không có đối số đầu vào
* Return Value			: Không Có Giá Trị Trả Lại                         
* Writer				: Phạm Thanh Toàn Developer - Damme88.
* Time					: 23h 23p 23s - Sunday05/12/2011
*
***************************************************************************************/
void Print(void)
{
	MEMBER	*kq;
	MEMBER	*ks;
	ks=phead->next ;
	kq=phead ;
	while(kq!=NULL){
	cout << "\n\tName:  "<< kq->name <<endl ;
	cout << "\n\tAge:  "<< kq->age <<endl ;
	cout << "\n\tSex:  "<< kq->sex <<endl ;
	cout << "\n\tCompany:  "<< kq->company <<endl ;
	cout << "\n\tCountry:  "<< kq->country <<endl<<endl<<endl ;
	kq=kq->next ;
	}

return  ;
}


/***************************************************************************************
* Function Name			: Clear
* Data Type				: Kiểu Void 
* Purpose				: Xóa 1 phần tử theo yêu cầu của Danh Sách Liên Kết (LLP)
* Input Parammeter		: Có 1 đối số đầu vào là vị trí phần tử cần xóa
* Return Value			: Không Có Giá Trị Trả Lại                         
* Writer				: Phạm Thanh Toàn Developer - Damme88.
* Time					: 23h 23p 23s - Sunday05/12/2011
*
***************************************************************************************/
void Clear(int m)
{
	MEMBER	*temp3 ;
	MEMBER	*temp4 ;
	int		Num=0 ;
	temp3=phead ;
	while(temp3!=NULL){
	Num=Num+1;
	temp3=temp3->next ;
	}
	if(Num<m)
	cout <<"\n\t Xin loi ban , danh sach khong co den phan tu thu" << m << " Sorry! List dont have to"<< m <<"members"<<endl;
	if(m==1){
	temp3=phead->next ;
	delete phead ;
	phead=temp3 ;
	}
	if(Num==m){
	temp3=phead;
	temp4=phead->next ;
		for(int u=1;u<m-1;u++){
		temp3=temp4;
		temp4=temp4->next ;
		}

		temp3->next=NULL ;
		delete pend ;
		pend= temp3 ;
	}
	if(m!=1&&m<Num){
	MEMBER*temp7,*temp8  ;
	temp7=phead;
	temp8=phead->next ;
		for(int j=1;j<m-1;j++){
		temp7=temp8;
		temp8=temp8->next ;
		}
	MEMBER *temp5;
	temp5=temp8->next ;
	temp7->next= temp5;
	delete temp8 ;
	}
}

