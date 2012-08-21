#pragma once


// CustomCombo
struct ITEMDATA
{
	BOOL bold;
	HICON icon;
};


class CustomCombo : public CComboBox
{
	DECLARE_DYNAMIC(CustomCombo)

public:
	CustomCombo();
	virtual ~CustomCombo();

public:
  CString str;

protected:
	DECLARE_MESSAGE_MAP()
  CMap<int,int,ITEMDATA,ITEMDATA> myMap;
public:
  INT_PTR AddItemCombo(LPCTSTR lpszItem);
  void MeasureItem(LPMEASUREITEMSTRUCT);

  void DrawItem(LPDRAWITEMSTRUCT);
  int CompareItem(LPCOMPAREITEMSTRUCT);

};


