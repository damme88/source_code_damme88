#ifndef FILE_WORK_H_
#define FILE_WORK_H_
#include <vector>
#include <string>
#include <Windows.h>
#include "StrWork.h"

namespace FileWrk {
  class FileWork {
  public:
    static std::vector <std::string>ListFileInFolder(std::string folder_path);
    static int DeleteFile(const char* file_path);
		static bool ChecIsExistFile(const char* path);
		static bool CopyFiles(const wchar_t * src_path, const wchar_t* dest_path);
		static bool CopyFileIntoFolder(const char* src_path, const char* des_path);
  };
}

#endif // FILE_WORK_H