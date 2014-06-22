
#include "StrWork.h"

namespace StrWrk {
  std::string StrWork::WcharToString(wchar_t* wsch) {
    std::string str("");
    int index = 0;
    while (wsch[index] != 0) {
      str += (char)wsch[index];
      ++index;
    }
    return str;
  }

   wchar_t* StrWork::StringToWchar(std::string str) {
     int index = 0;
     int count = str.length();
     wchar_t* wsch = new wchar_t[count+1];
     while (index < count) {
       wsch[index] = (wchar_t)str[index];
       ++index;
     }
     wsch[index] = 0;
     return wsch;
   }

   std::wstring StrWork::WcharToWstring(wchar_t* wsch) {
     return (std::wstring)(wsch);	
   }
}