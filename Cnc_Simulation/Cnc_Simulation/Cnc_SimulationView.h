
// Cnc_SimulationView.h : interface of the Cnc_SimulationView class
//

#pragma once


class Cnc_SimulationView : public CView
{
protected: // create from serialization only
	Cnc_SimulationView();
	DECLARE_DYNCREATE(Cnc_SimulationView)

// Attributes
public:
	Cnc_SimulationDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cnc_SimulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Cnc_SimulationView.cpp
inline Cnc_SimulationDoc* Cnc_SimulationView::GetDocument() const
   { return reinterpret_cast<Cnc_SimulationDoc*>(m_pDocument); }
#endif

