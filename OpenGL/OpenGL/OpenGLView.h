// OpenGLView.h : interface of the COpenGLView class
//


#pragma once


class COpenGLView : public CView
{
protected: // create from serialization only
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:
	COpenGLDoc* GetDocument() const;

// Operations
public:
	HGLRC m_hRC; //Rendering Context
	CDC* m_pDC; //Device Context
	
	BOOL m_bPoint ;
    BOOL m_bLine ;
    BOOL m_bPolygon ;
    BOOL m_bTriangle ;

	BOOL m_bCube ;
	BOOL m_bTorus ;
	BOOL m_bTeaport;
	BOOL m_blsahedron ;

	GLfloat m_xAngle ;
	GLfloat m_yAngle ;
	GLfloat m_xPos ;
	GLfloat m_yPos ;
	GLfloat  m_zoom ;
	CPoint m_MouseDownPoint ;

	BOOL m_bOXY ;
	BOOL m_bOXYZ ;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnSize(UINT nType, int cx, int cy);
	int OnCreate(LPCREATESTRUCT lpCreateStruct) ;
	void RenderScene ();
	BOOL OnEraseBkgnd(CDC* pDC) ;
	void OnShapesPoint();
	BOOL InitializeOpenGL();
	BOOL SetupPixelFormat();
	void OnLButtonDown(UINT nFlags, CPoint point) ;
	void OnLButtonUp(UINT nFlags, CPoint point); 
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags); 
	void OnMouseMove(UINT nFlags, CPoint point);

	// Toa do de cac
	void OnOXYZ();
	void OnOXY();
	
	// Function for draw 3D
	void WriteCube();
	void WriteTeaport();
	void WritelCosahedron();
	void WriteTorus();

	void OnPoint();
	void OnLines();
	void OnPolygon();
	void OnTriangle();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void OnDestroy() ;
	
// Implementation
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OpenGLView.cpp
inline COpenGLDoc* COpenGLView::GetDocument() const
   { return reinterpret_cast<COpenGLDoc*>(m_pDocument); }
#endif

