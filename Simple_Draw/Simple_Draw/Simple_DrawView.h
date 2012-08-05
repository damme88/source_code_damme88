
// Simple_DrawView.h : interface of the CSimple_DrawView class
#pragma once


class CSimple_DrawView : public CView
{
protected: // create from serialization only
	CSimple_DrawView();
	DECLARE_DYNCREATE(CSimple_DrawView)

// Attributes
public:
	CSimple_DrawDoc* GetDocument() const;

// Operations
public:
HGLRC m_hRC; //Rendering Context
	CDC* m_pDC; //Device Context

private:
   BOOL m_bOXY;
   BOOL m_draw_grid;
   UINT count_oxy;
   UINT count_oxyz;
   UINT count_grid;
   BOOL m_bOXYZ;
   GLfloat m_xAngle;
	 GLfloat m_yAngle;
   GLfloat m_zoom;

   GLfloat m_texMode;
   GLfloat m_texWrap;
   GLfloat m_texFilter;
   //GLuint  m_Texture[10];
   CPoint m_MouseDownPoint;

   // variable for button checkbox of office toolbar
   short m_text_bold;
   short m_text_italic;
   short m_text_under_line;
   BOOL check_bold_;
   BOOL check_italic_;
   BOOL check_underline_;
   
   short m_align_left;
   short m_align_right;
   short m_align_center;
   short m_align_justify;

   short m_draw_line;
   short m_count_draw_line;

   CPoint m_first_point;
   CPoint m_end_point;
   int count_down;
   BOOL check_down;

public:
  BOOL status_text_editor_;

public:
   void OnEditUndo();
   void OnEditCut();
   void OnEditCopy();
   void OnEditPaste();
   void OnCoordinateOxyz();
   void OnCoordinateOxy();
   void OnDrawGrid();
   void OnDrawColor();

   void OnLButtonDown(UINT nFlags, CPoint point);
   void OnLButtonUp(UINT nFlags, CPoint point);
   void OnMouseMove(UINT nFlags, CPoint point);
   BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
   void OnViewFront();
   void OnViewBehind();
   void OnViewTop();
   void OnViewBottom();
   void OnViewRight();
   void OnViewLeft();
   void OnViewStandar();
   void OnZoomIn();
   void OnZoomOut();
   void OnZoomStandar();

   // function for office toolbar button 
   void OnTextBold();
   void OnTextItalic();
   void OnTextUnderLine();
   void OnUpdateBold(CCmdUI * pcmdui);
   void OnUpdateItalic(CCmdUI *pcmdui);
   void OnUpdateUnderLine(CCmdUI *pcmdui);

   void OnHandleAlign(UINT nID);
   void OnUpdateHandleAlign(CCmdUI *pcmdui);

   void OnSo1(); 
   void OnDrawline();
   void OnUpdateDrawLine(CCmdUI *pcmdui);
   
   void DrawLine();
   void DrawCurve();
   void DrawCircle();
   void DrawRectangle();
   void DrawRoundRectangle();
   void DrawPoint();
   void DrawColorPic();
   void DrawColorFill();
   void DrawEraser();
   void DrawPolygon();


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
	virtual ~CSimple_DrawView();
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
public:
  afx_msg void OnBnClickedSubmitBtn();
};

#ifndef _DEBUG  // debug version in Simple_DrawView.cpp
inline CSimple_DrawDoc* CSimple_DrawView::GetDocument() const
   { return reinterpret_cast<CSimple_DrawDoc*>(m_pDocument); }
#endif

