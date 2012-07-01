
#ifndef _STACK_DATA_STRUCT_H_
#define _STACK_DATA_STRUCT_H_


/******************************************************************************
* Struct Name			: DATA
* Purpose				  : Cau truc data gom 1 truong kieu int dung cho mo hinh Stack.
*						      : La mo hinh luu data vao ngan xep mot cach hieu qua
* Component				: 1 truong int.
* Language				: Visual C++2008.
* Writer				  : Phạm Thanh Toàn Developer - Damme88.
* Time					  : 23h 45p 23s - Sunday 18/12/2011
*******************************************************************************/
struct DATA {
  int Value;        // gia tri kieu nguyen can luu
  DATA *Next;       // 1 con tro next de chay theo mo hinh danh sach lien ket
};
#endif

