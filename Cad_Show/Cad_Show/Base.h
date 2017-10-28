

#ifndef BASE_H_
#define BASE_H_
#define BASE_H_

#include "stdafx.h"
#include <io.h>

namespace Base {
  static CString GetPathModule() 
  {
    CString full_path = L"";
    ::GetModuleFileName(NULL, full_path.GetBufferSetLength(MAX_PATH+1), MAX_PATH);
    full_path = full_path.Left(full_path.ReverseFind('\\'));
    return full_path;
  }

	static char* CStringToChar(CString str) {
		char * chstr = new char [MAX_PATH];
		long nsize = str.GetLength();
		memset(chstr, 0, nsize);
		wcstombs(chstr, str, nsize+1);
		return chstr;
	}
}

#endif // BASE_H_