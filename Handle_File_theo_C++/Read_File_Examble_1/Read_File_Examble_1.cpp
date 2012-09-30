// Read_File_Examble_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// function nay se thuc hien nhiem vu khi data vao 1 file
// neu file chua co thi no se tao ra va ghi file vao
void WriteFileModeOne() {
  fstream dataFile ;  // fstream can read , create, write file
  cout << "Opening file \n";
  dataFile.open("write_file.txt", ios::out); // opening file exist 
                                       // or create file dont exist
  cout << "now writting data to file \n";
  dataFile << "ToanPT \n"; // write line 1 in File
  dataFile << "Damme88 \n"; // write line 1 in File
  dataFile << "Dream88 \n"; // write line 1 in File
  dataFile.close();  // phai co lenh nay khi ket thuc
}


// function nay se thuc hien chuc nang ghi data vao 1 file
// sau do dong file lai
// roi lai open file va ghi tiep data vao
// Neu su dung them mode ios::app thi noi dung truoc do da ghi ko bi xoa
void WriteFileModeTwo() {
  fstream dataFile; cout << "Opening file...\n";  // ofstream cho phep create file va write file
  dataFile.open("write_file_2.txt", ios::out);
  cout << "Now writing data to the file.\n";
  dataFile << "Jones\n"; // Ghi dòng thứ 1
  dataFile << "Smith\n"; // Ghi dòng thứ 2
  cout << "Now closing the file.\n";
  dataFile.close(); // Đóng file

  cout << "Opening the file again...\n";
  // Mở file ở chế độ gắn vào.
  dataFile.open("write_file_2", ios::out | ios::app);  // neu chi su dung iso::out thi noi dung truoc do se bi clear
  cout << "Writing more data to the file.\n";
  dataFile << "Willis\n"; // Ghi dòng thứ 3
  dataFile << "Davis\n"; //Ghi dòng thứ 4
  cout << "Now closing the file.\n";
  dataFile.close(); // Đóng file
  
  cout << "Done.\n";
}

void WriteFileModeThree() {
  fstream data_file;
  data_file.open("file_put.txt", ios::out); // neu file ko ton tai thi se create new file
  char ch;
  cout << "Moi ban nhap data de ghi vao file. Ket thuc chuoi = ky tu '.'";
  cout << "\n data = ";
  cin.get(ch);
  while (ch !='.') {// chi khi nao ky tu nhap vao = ky tu '.' thi ket thuc chuoi
  cin.get(ch);  // nhap 1 ky tu tu ban phim
  data_file.put(ch);
} 
  cout << "ok ban da ghi file thanh cong";
  data_file.close();
  return;
}



// thuc hien chuc nang kiem tra xem 1 file co ton tai hay ko
// neu de duong dan tuong doi thi no chi kiem tra trong muc chua file source
// Co the kiem tra file voi duong dan tuyet doi
// Khong co su phan biet chu hoa voi chu thuong

void CheckFileExisting() {
  fstream data_file;
  data_file.open("check_file.txt", ios::in);
  //data_file.open("G:\\STUDING\\Read File Full\\Read_File_Examble_1\\value.txt", ios::in);
  bool ret = data_file.fail();
  if (ret == true) {
    cout << " File don't exist";
    data_file.open("value.txt", ios::out); // tao file moi
  } else {
    // neu file co ton tai thi thuc hien lam gi do trong day
    cout << "File exist";
  }
  data_file.close();
}

// ReaFile theo kieu 1. su dung toan tu >>
// chi su dung khi doc du lieu khong co ky tu space
// vi cach nay no se coi ky tu space la 1 ky tu ket thuc
void ReadFileModeOne() {
  char input[100];
  fstream name_file;
  name_file.open("read_file.txt", ios::in);
  // neu file ko ton tai thi name_file se ko co value
  if (name_file == 0) {
    cout << "read file fail, file don't exist";
    return;
  } else {
    while (name_file >> input) {
      cout << input;
    }
  }
  name_file.close();
}

// doc data tu file su dung ham getline
void ReadFileModeTwo() {
  char input[100];
  fstream file_data;
  file_data.open("read_file.txt", ios::in);
  if(file_data == 0) {
    cout << "file don't exit ";
    return;
  } else {
    while(!file_data.eof()) {  // chay theo tung dong den khi ket thuc xau
      file_data.getline(input, 100); // lay ra tung line. hay la tung chuoi cach nhau boi ky tu \n
      file_data.getline(input, 100);
      cout << input;
    }
  }
  file_data.close();
}

// doc data tu file su dung ham get
void ReadFileModeThree() {
  char ch;
  char *input = new char [100];
  int i=0;
  fstream file_data;
  file_data.open("read_file_3.txt", ios::in);
  if (file_data == 0) {
    cout << "File don't exist";
    return;
  } else {
    while (!file_data.eof()) {
      file_data.get(ch);
      input[i] = ch;
      i++;
    }
    for (int j =0; j<i;j++) {
      cout << input[j];
    }
  }
  file_data.close();
}

// Doc file nhi phan theo kieu ngon ngu C
void HanldeFileBinary() {
FILE *f;
f=fopen("E:\\CacSo.txt","wb");
if (f!=NULL) {
double d=3.14;
int i=100;
long l=54321;
fwrite(&d,sizeof(double),1,f);
fwrite(&i,sizeof(int),1,f);
fwrite(&l,sizeof(long),1,f);

/* Doc tu tap tin*/
rewind(f);
fread(&i,sizeof(int),1,f);
fread(&l,sizeof(long),1,f);
printf("Cac ket qua la: %f %d %ld",d,i,l);
fclose(f);
}
return;

}

int _tmain(int argc, _TCHAR* argv[])
{
  //WriteFileModeOne();
  //WriteFileModeTwo();
  //CheckFileExisting();
  //ReadFileModeOne() ;
  //ReadFileModeTwo();
  //ReadFileModeThree();
  //WriteFileModeThree() ;
  //HanldeFileBinary();
  getch();
	return 0;
}

