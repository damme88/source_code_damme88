#pragma once
#include "resource.h"


// FormView form view

class FormView : public CFormView
{
	DECLARE_DYNCREATE(FormView)

protected:
	FormView();           // protected constructor used by dynamic creation
	virtual ~FormView();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};


