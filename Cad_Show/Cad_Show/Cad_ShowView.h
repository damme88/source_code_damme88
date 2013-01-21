
// Cad_ShowView.h : interface of the CCad_ShowView class
//

#pragma once

class CCad_ShowView : public CView
{
protected: // create from serialization only
	CCad_ShowView();
	DECLARE_DYNCREATE(CCad_ShowView)

// Attributes
public:
	CCad_ShowDoc* GetDocument() const;

// Operations
private:
  HGLRC m_hRC; //Rendering Context
  CDC* m_pDC; //Device Context
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
  int OnCreate(LPCREATESTRUCT lpCreateStruct);
  BOOL InitializeOpenGL();
  BOOL SetupPixelFormat();
  void OnSize(UINT nType, int cx, int cy);
  void RenderScene();
  BOOL OnEraseBkgnd(CDC* pDC);
  void OnDestroy();

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCad_ShowView();
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
  afx_msg void OnKeyDown(UINT nchar , UINT nRepCnt, UINT nFlas);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

private:
  //variable for rotatef and zoom for cad object
  GLfloat angle_x_;
	GLfloat angle_y_;
  GLfloat value_zoom_;
  CPoint mouse_down_point_;

  GLfloat x_position_ ;
	GLfloat y_position_ ;
  int     m_nFontOffset;
  GLuint  m_nAxisesList;

  //Variable for MButtonDown
  BOOL middle_down_;
  CPoint middle_down_pos_;
  HCURSOR cursor_;
  HCURSOR middle_down_cursor_;

  // Variable for rotate button
  BOOL rotate_left_;
  BOOL rotate_righit_;
public: 
  void OnMouseMove(UINT nFlags, CPoint point);
  BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  void OnRButtonDown(UINT nFlags, CPoint point);
  void BuildAxisesList();
  void PrintAxisLabel(const char* str);
  void SetUpLight();
  void DisableSetupLigting();
  // functions for drawing
  void DrawCad();
  void PrepareAxisLabel();
  void OnMButtonDown(UINT nFlags, CPoint point);
  void OnMButtonUp(UINT nFlags, CPoint point);
public:
  void OnHandleViewButton(UINT nID); 
};

#ifndef _DEBUG  // debug version in Cad_ShowView.cpp
inline CCad_ShowDoc* CCad_ShowView::GetDocument() const
   { return reinterpret_cast<CCad_ShowDoc*>(m_pDocument); }
#endif

