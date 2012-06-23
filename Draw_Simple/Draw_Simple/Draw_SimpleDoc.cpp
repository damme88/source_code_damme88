
// Draw_SimpleDoc.cpp : implementation of the CDraw_SimpleDoc class
//

#include "stdafx.h"
#include "Draw_Simple.h"

#include "Draw_SimpleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDraw_SimpleDoc

IMPLEMENT_DYNCREATE(CDraw_SimpleDoc, CDocument)

BEGIN_MESSAGE_MAP(CDraw_SimpleDoc, CDocument)
END_MESSAGE_MAP()


// CDraw_SimpleDoc construction/destruction

CDraw_SimpleDoc::CDraw_SimpleDoc()
{
	// TODO: add one-time construction code here

}

CDraw_SimpleDoc::~CDraw_SimpleDoc()
{
}

BOOL CDraw_SimpleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CDraw_SimpleDoc serialization

void CDraw_SimpleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CDraw_SimpleDoc diagnostics

#ifdef _DEBUG
void CDraw_SimpleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDraw_SimpleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDraw_SimpleDoc commands
