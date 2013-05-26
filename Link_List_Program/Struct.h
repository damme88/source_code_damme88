
/*******************************************************************************
* Struct Name   : MEMBER
* Purpose       : Store data of pepole
* Writer        : Damme88_Phamtoanbonmat@gmail.com
* Role          : Electronic Communication and Graphics Developer
* Time          : 23h 23p 23s - Sunday 05/12/2011
* Language      : VC ++ Console 2010
* Run OS        : Windows 8 ultimate
*******************************************************************************/
#ifndef STRUCT_H_
#define STRUCT_H_
struct MEMBER {
  char name[20];
  int age;
  char sex[10];
  char company[20];
  char country[50];
  MEMBER*next;
} ;
MEMBER*phead ;
MEMBER*pend ;
#endif // STRUCT_H_

