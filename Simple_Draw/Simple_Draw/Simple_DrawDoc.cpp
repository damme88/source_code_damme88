
// Simple_DrawDoc.cpp : implementation of the CSimple_DrawDoc class
//

#include "stdafx.h"
#include "Simple_Draw.h"

#include "Simple_DrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimple_DrawDoc

IMPLEMENT_DYNCREATE(CSimple_DrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimple_DrawDoc, CDocument)
END_MESSAGE_MAP()


// CSimple_DrawDoc construction/destruction

CSimple_DrawDoc::CSimple_DrawDoc()
{
	// TODO: add one-time construction code here

}

CSimple_DrawDoc::~CSimple_DrawDoc()
{
}

BOOL CSimple_DrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSimple_DrawDoc serialization

void CSimple_DrawDoc::Serialize(CArchive& ar)
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


// CSimple_DrawDoc diagnostics

#ifdef _DEBUG
void CSimple_DrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimple_DrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSimple_DrawDoc commands
