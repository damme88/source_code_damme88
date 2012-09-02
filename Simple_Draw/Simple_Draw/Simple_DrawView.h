
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
   BOOL m_bOXYZ;
   BOOL check_oxy;
   BOOL check_oxyz;
   BOOL m_draw_grid;
   BOOL check_grid;
   GLfloat m_xAngle;
	 GLfloat m_yAngle;
   GLfloat m_zoom;

   GLfloat m_texMode;
   GLfloat m_texWrap;
   GLfloat m_texFilter;
   CPoint m_MouseDownPoint;
   
   // Variable for move object
   GLfloat m_xPos ;
	 GLfloat m_yPos ;

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

  BOOL status_text_editor_;

  GLuint m_3DTextList;
  GLuint m_2DTextList;
  GLuint m_b3DText;
  GLuint m_b2DText;
  // variable for getting color from color dialog 
  // variable for MFC color
  unsigned int red_color_;
  unsigned int green_color_;
  unsigned int blue_color_;
  // variable for Opengl color
  GLfloat gl_red_color_;
  GLfloat gl_green_color_;
  GLfloat gl_blue_color_;

// variable for draw 2d and 3d Object
  BOOL enalbe_point_ ;
  BOOL enable_line_ ;
  BOOL enable_polygon_ ;
  BOOL enable_triangle_ ;
  BOOL enable_rectang_;
  BOOL enable_square_;
  BOOL enable_circle_;

	BOOL enable_cube_ ;
	BOOL enable_torus_ ;
	BOOL enable_teaport_;
	BOOL enable_lsahedron_ ;
  BOOL enable_sphere_;

public:
   void OnHandleMoveObject(UINT nID);
   void OnHandleZoom(UINT nID);
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

   // Draw a text with OPenGL
   void Create3DTextList();
   void Create2DTextLists();

   // Function for draw 2d 3d Opengl Object
   void Draw2DObject(UINT nID);
   void Draw3DObject(UINT nID);

   void DrawQuadric();
   void DrawCylinder();
   void DrawCubeFull();
   // functions for drawing 2d and 3d object 
   void OnDraw2DObject();
   void OnDraw3DObject();
   void SetupLighting();

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
  afx_msg void OnKeyDown(UINT nchar , UINT nRepCnt, UINT nFlas);
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedSubmitBtn();
};

#ifndef _DEBUG  // debug version in Simple_DrawView.cpp
inline CSimple_DrawDoc* CSimple_DrawView::GetDocument() const
   { return reinterpret_cast<CSimple_DrawDoc*>(m_pDocument); }
#endif

