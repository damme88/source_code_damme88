#pragma once


// TextEditor dialog

class TextEditor : public CDialog
{
	DECLARE_DYNAMIC(TextEditor)

public:
	TextEditor(CWnd* pParent = NULL);   // standard constructor
	virtual ~TextEditor();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
