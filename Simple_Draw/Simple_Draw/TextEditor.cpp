// TextEditor.cpp : implementation file
//

#include "stdafx.h"
#include "Simple_Draw.h"
#include "TextEditor.h"


// TextEditor dialog

IMPLEMENT_DYNAMIC(TextEditor, CDialog)

TextEditor::TextEditor(CWnd* pParent /*=NULL*/)
	: CDialog(TextEditor::IDD, pParent)
{

}

TextEditor::~TextEditor()
{
}

void TextEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TextEditor, CDialog)
END_MESSAGE_MAP()


// TextEditor message handlers
