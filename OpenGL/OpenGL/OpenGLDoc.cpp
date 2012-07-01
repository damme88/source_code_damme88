// OpenGLDoc.cpp : implementation of the COpenGLDoc class
//

#include "stdafx.h"
#include "OpenGL.h"

#include "OpenGLDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLDoc

IMPLEMENT_DYNCREATE(COpenGLDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenGLDoc, CDocument)
END_MESSAGE_MAP()


// COpenGLDoc construction/destruction

COpenGLDoc::COpenGLDoc()
{
	// TODO: add one-time construction code here

}

COpenGLDoc::~COpenGLDoc()
{
}

BOOL COpenGLDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
  return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}




// COpenGLDoc serialization

void COpenGLDoc::Serialize(CArchive& ar)
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


// COpenGLDoc diagnostics

#ifdef _DEBUG
void COpenGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COpenGLDoc commands
