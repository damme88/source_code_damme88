
// Draw_SimpleView.h : interface of the CDraw_SimpleView class
//


#pragma once


class CDraw_SimpleView : public CView
{
protected: // create from serialization only
	CDraw_SimpleView();
	DECLARE_DYNCREATE(CDraw_SimpleView)

// Attributes
public:
	CDraw_SimpleDoc* GetDocument() const;

public:
  HGLRC m_hRC; //Rendering Context
	CDC* m_pDC; //Device Context

private:
   BOOL m_bOXY;
   UINT count_oxy;
   UINT count_oxyz;
   BOOL  m_bOXYZ;
   GLfloat m_xAngle ;
	 GLfloat m_yAngle ;
   GLfloat m_zoom;
   CPoint m_MouseDownPoint;
public:
   void OnEditUndo();
   void OnEditCut();
   void OnEditCopy();
   void OnEditPaste();
   void OnViewColor();
   void OnCoordinateOxyz();
   void OnCoordinateOxy();

   void OnLButtonDown(UINT nFlags, CPoint point);
   void OnLButtonUp(UINT nFlags, CPoint point);
   void OnMouseMove(UINT nFlags, CPoint point);
   BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  int OnCreate(LPCREATESTRUCT lpCreateStruct);
  BOOL InitializeOpenGL();
  BOOL SetupPixelFormat();
  void OnSize(UINT nType, int cx, int cy); 
  BOOL OnEraseBkgnd(CDC* pDC); 
  void OnDestroy();
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  void RenderScene ();


protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDraw_SimpleView();
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

#ifndef _DEBUG  // debug version in Draw_SimpleView.cpp
inline CDraw_SimpleDoc* CDraw_SimpleView::GetDocument() const
   { return reinterpret_cast<CDraw_SimpleDoc*>(m_pDocument); }
#endif

