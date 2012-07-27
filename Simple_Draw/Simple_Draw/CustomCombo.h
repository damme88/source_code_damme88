#pragma once


// CustomCombo

class CustomCombo : public CComboBox
{
	DECLARE_DYNAMIC(CustomCombo)

public:
	CustomCombo();
	virtual ~CustomCombo();

protected:
	DECLARE_MESSAGE_MAP()
public:
  INT_PTR AddItemCombo(LPCTSTR lpszItem, UINT iconID);
};


