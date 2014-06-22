#ifndef STRWORK_H_
#define STRWORK_H_
#include <string>

namespace StrWrk {
  class StrWork {
  public:
    static std::string WcharToString(wchar_t* wsch);
    static wchar_t* StringToWchar(std::string str);
    static std::wstring WcharToWstring(wchar_t* wsch);
  };
}


#endif