
#include "stdafx.h"
#include "MyDll.h"

MyDll::MyDll()
{

}

MyDll::~MyDll()
{

}


__declspec(dllexport) int MyDll::AddNumbers(int a, int b) {
   AFX_MANAGE_STATE(AfxGetModuleState());
	 return a+b;
}

extern "C" __declspec(dllexport) int MultiNumbers(int a, int b) {
	  return a+b;
}
