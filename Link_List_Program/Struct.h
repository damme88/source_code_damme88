// Khai báo các struct sử dụng cho chương trình

/***************************************************************************************
* Struct Name			: MEMBER 
* Purpose				: Xây dựng một kiểu dữ liệu mới,dữ liệu nhân viên 1 công ty
* Component				: Gồm có 5 trường thông tin và 1 con trỏ
* Writer				: Phạm Thanh Toàn Developer - Damme88.
* Time					: 23h 23p 23s - Sunday05/12/2011
*
*
*
***************************************************************************************/

		struct MEMBER   
		{
		char name[20];			// Ho ten
		int age ;				// Tuoi
		char sex[10] ;			// Gioi tinh
		char company[20];		// Cong ty
		char country[50];		// Que quan
		MEMBER*next ;           // Mot con tro trung gian de chay 
		} ;
		MEMBER*phead ;          // Hai con tro tro den dau va cuoi danh sach
		MEMBER*pend ;

/**************************************************************************************/

