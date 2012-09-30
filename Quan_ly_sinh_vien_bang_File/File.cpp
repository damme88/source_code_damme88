/***************************************************************************************
* Name Program		: Chương trình xử lý file -File Process Programming
* Purpose			: Đọc dữ liệu đầu vào, tạo file 1 và ghi data vào file 1
*					: Thực hiện đọc data trong file 1 rồi đưa lên mảng xử lý 
*					: Sau đó tạo file 2 và ghi kết quả xử lý ra file 2
* Writer			: Phạm Thanh Toàn-Developer-Damme88
* Time Write		: Thứ 5 10h 10p 10s 08/12/2011
* Language			: Visual C ++ 2008
* Environment		: Window XP,Windows 7 -32bit 
***************************************************************************************/

#include "stdafx.h"
#include "Struct_Data.h"
    
STUDENT * sv ;
STUDENT * sv1 ;
STUDENT sv2[10];
 
/***************************************************************************************
* Name Function		: NhapThongTin
* Purpose			: Nhap thong tin tu ban phim 
* Prammeter         : Một đối số đầu vào int để xác định số phần tử
* Writer			: Phạm Thanh Toàn-Developer-Damme88
* Time Write		: 12/2011
*
***************************************************************************************/
void NhapThongTin(int n)
{
	int i= 1 ;	
	cout << "\n\t Nhap Thong Tin Sinh Vien "<<endl ;
	for(i=1; i<=n; i++){
		cout << "\n\t Thong Tin Sinh Vien Thu [" <<i<<"] "<<endl;
		cout << "\n\t	Ho ten : ";
		cin.ignore();
		cin.getline((sv+i)->Hoten,20);
		cout << "\n\t	Que Quan : ";
		cin.getline((sv+i)->Quequan,28);
		cout << "\n\t	Truong : ";
		cin.getline((sv+i)->Truong,28);
		cout << "\n\t	Nam Sinh : ";

		cin.getline((sv+i)->Namsinh,28);
		cout << "\n\t	Chuyen Nganh : ";
		cin.getline((sv+i)->Chuyennganh,28);
		cout << "\n\t	Tuoi : ";
		cin >> (sv+i)->Tuoi;
		cout << "\n\t	Diem : ";
		cin >> (sv+i)->Diem ;
		cout <<endl<<endl<<endl ;
	}
}


/***************************************************************************************
* Name Function		: GhiFile
* Purpose			: Ghi thông tin nhập vào từ bàn phím ra file 1  
* Prammeter         : Hai đối số đầu vào 1 là tên file sẽ được tạo ra để ghi,2 là số pt
* Writer			: Phạm Thanh Toàn-Developer-Damme88
* Time Write		: 12/2011
*
***************************************************************************************/
void GhiFile(char fname[50], int n)
 {
	 int i= 0;
	 ofstream file(fname);
     file << "\n\t  Thong Tin Sinh Vien " ;
	 for(i=1;i<=n;i++){
		file << "\n\t  Thong Tin Sinh Vien Thu [" <<i<<"] " <<endl <<endl;
		file << "\n\t Ho ten       : ";
		file << (sv+i)->Hoten ;
		file << "\n\t Que Quan     : ";
		file << (sv+i)->Quequan;
		file << "\n\t Truong       : ";
		file << (sv+i)->Truong;
		file << "\n\t Nam Sinh     : ";
		file << (sv+i)->Namsinh;
		file << "\n\t Chuyen Nganh : ";
		file << (sv+i)->Chuyennganh;
		file << "\n\t Tuoi         :  ";
		file << (sv+i)->Tuoi;
		file << "\n\t Diem         : ";
		file << (sv+i)->Diem ;
		file << endl << endl ;
	 }
	 file.close();
}



/***************************************************************************************
* Name Function		: Đọc File
* Purpose			: Đọc data từ file ra và ghi nó vào mảng
* Prammeter         : Hai đối số đầu vào 1 là tên file sẽ được đọc ,2 là số pt
* Writer			: Phạm Thanh Toàn-Developer-Damme88
* Time Write		: 12/2011
*
***************************************************************************************/
void DocFile(char qname[50], int n)
{
	int i= 0 ;
	ifstream file(qname);
	for(i=1;i<=n;i++){
		strcpy (sv2[i].Hoten,(sv+i)->Hoten);
		strcpy (sv2[i].Quequan,(sv+i)->Quequan);
		strcpy (sv2[i].Truong,(sv+i)->Truong);
		strcpy (sv2[i].Namsinh,(sv+i)->Namsinh);
		strcpy (sv2[i].Chuyennganh,(sv+i)->Chuyennganh);
		sv2[i].Tuoi=(sv+i)->Tuoi;
		sv2[i].Diem=(sv+i)->Diem;
	}
	file.close();
}


/***************************************************************************************
* Name Function		: XulyFile
* Purpose			: Xử lý data trong file theo mục đích người sử dụng 
* Prammeter         : 1 đối số đầu vào là số pt
* Writer			: Phạm Thanh Toàn-Developer-Damme88
* Time Write		: 12/2011
*
***************************************************************************************/
void XulyFile(int n)
{
	int		i= 0 ;
	int		j= 0 ;
	STUDENT svp ;
	for (i=1; i<=n; i++){
		for (j=i+1 ;j<=n; j++){
			if (sv2[i].Diem < sv2[j].Diem){
				svp.Diem= sv2[i].Diem;
				sv2[i].Diem= sv[j].Diem;
				sv2[j].Diem= svp.Diem;

				strcpy (svp.Hoten,sv2[i].Hoten);
				strcpy (sv2[i].Hoten,sv2[j].Hoten);
				strcpy (sv2[j].Hoten,svp.Hoten);

				strcpy (svp.Quequan,sv2[i].Quequan);
				strcpy (sv2[i].Quequan,sv2[j].Quequan);
				strcpy (sv2[j].Quequan,svp.Quequan);


				strcpy (svp.Truong,sv2[i].Truong);
				strcpy (sv2[i].Truong,sv2[j].Truong);
				strcpy (sv2[j].Truong,svp.Truong);


				strcpy (svp.Chuyennganh,sv[i].Chuyennganh);
				strcpy (sv2[i].Chuyennganh,sv2[j].Chuyennganh);
				strcpy (sv2[j].Chuyennganh,svp.Chuyennganh);

				strcpy (svp.Namsinh,sv[i].Namsinh);
				strcpy (sv2[i].Namsinh,sv2[j].Namsinh);
				strcpy (sv2[j].Namsinh,svp.Namsinh);

				svp.Tuoi=sv[i].Tuoi;
				sv2[i].Tuoi=sv[j].Tuoi;
				sv2[j].Tuoi=svp.Tuoi;
			}
		}
		strcpy ((sv+i)->Hoten,sv2[i].Hoten);
		strcpy ((sv+i)->Quequan,sv2[i].Quequan);
		strcpy ((sv+i)->Truong,sv2[i].Truong);
		strcpy ((sv+i)->Namsinh,sv2[i].Namsinh);
		strcpy ((sv+i)->Chuyennganh,sv2[i].Chuyennganh);
		(sv+i)->Tuoi=sv2[i].Tuoi;
		(sv+i)->Diem=sv2[i].Diem;
	}
}


/***************************************************************************************
* Function Name		: Ham main
* Purpose			: Ham chinh, goi cac ham con 
* Writer			: Damme88- Deverloper - Phamtoanbonmat@gmail.com
* Time				: 13h35 phut Sunday 01/04/2012
***************************************************************************************/
 void main()
 {
	int n= 0 ;
	cout << "\n\t Moi ban nhap so sinh vien \n\t n = " ;
	cin >> n ;
	sv= new STUDENT[n+1];
	NhapThongTin(n);
	GhiFile("DanhSach1.txt",n);
	DocFile("DanhSach1.txt",n);
	XulyFile(n );
	GhiFile("Danh Sach2.txt",n);
	delete sv ;
	getch ();
}

