
#ifndef BASIC_CONVERT_H_
#define BASIC_CONVERT_H_
#include "stdafx.h"

namespace Converts {
  char* CStringToChar(CString strInput) 
  {
    long nSize = strInput.GetLength();
    char* ret_characs = new char[nSize];
    memset(ret_characs, 0, nSize);
    wcstombs(ret_characs, strInput, nSize + 1);
    return ret_characs;
  }
}


#endif // BASIC_CONVERT_H_