// FormView.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL_MFC.h"
#include "FormView.h"


// FormView

IMPLEMENT_DYNCREATE(FormView, CFormView)

FormView::FormView()
	: CFormView(FormView::IDD)
{

}

FormView::~FormView()
{
}

void FormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(FormView, CFormView)
END_MESSAGE_MAP()


// FormView diagnostics

#ifdef _DEBUG
void FormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void FormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// FormView message handlers
