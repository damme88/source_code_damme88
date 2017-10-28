
#include <io.h>
#include <fstream>
#include "FileWork.h"
namespace FileWrk {
  // List files in folder
  std::vector<std::string> FileWork::ListFileInFolder(std::string folder_path) {
    WIN32_FIND_DATA find_file_data;
    std::vector<std::string> list_file;

    wchar_t* path_folder_full = StrWrk::StrWork::StringToWchar(folder_path);

    HANDLE hFind = FindFirstFile(path_folder_full, &find_file_data);

    list_file.push_back(StrWrk::StrWork::WcharToString(find_file_data.cFileName));

    while(FindNextFile(hFind, &find_file_data)) {
      list_file.push_back(StrWrk::StrWork::WcharToString(find_file_data.cFileName));
    }
    return list_file;
  }

  // Delete File
  int FileWork::DeleteFile(const char* file_path) {
    // ret = 0 success else failed
    return remove(file_path);
  }

	bool FileWork::ChecIsExistFile(const char* path) {
		FILE*     file;
		file = fopen(path, "r");
		if (!file) {
			return false;
		} 
		fclose(file);
		return true;
	}

	bool FileWork::CopyFiles(const wchar_t * src_path, const wchar_t* dest_path) {  
		bool ret = CopyFile(src_path, dest_path, FALSE);
		return ret;
	}

	bool FileWork::CopyFileIntoFolder(const char* src_path, const char* des_path) 
  {

		std::ifstream::pos_type size;
		char * memblock;

		std::ifstream file_src (src_path, std::ios::in|
			std::ios::binary|
			std::ios::ate);
		if (file_src == NULL) {
			return false;
		}
		if (file_src.is_open()) {
			size = file_src.tellg();
			memblock = new char [size];
			file_src.seekg (0, std::ios::beg);
			file_src.read (memblock, size);
			file_src.close();
		}

		std::fstream file_des(des_path, std::ios::out | std::ios::binary);
		file_des.seekg(0, std::ios::beg);  
		file_des.write(memblock, size);

		file_des.close();
		return true;
	}
}