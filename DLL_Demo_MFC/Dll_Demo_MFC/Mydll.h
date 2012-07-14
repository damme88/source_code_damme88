
#pragma once

class MyDll  
{
public:
__declspec(dllexport) int AddNumbers(int a, int b);
 __declspec(dllexport) int MultiNumbers(int a, int b);
 __declspec(dllexport) MyDll();
 __declspec(dllexport) virtual ~MyDll();

};