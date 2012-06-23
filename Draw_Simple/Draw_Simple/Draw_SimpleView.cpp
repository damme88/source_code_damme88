
// Draw_SimpleView.cpp : implementation of the CDraw_SimpleView class
//

#include "stdafx.h"
#include "Draw_Simple.h"

#include "Draw_SimpleDoc.h"
#include "Draw_SimpleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDraw_SimpleView

IMPLEMENT_DYNCREATE(CDraw_SimpleView, CView)

BEGIN_MESSAGE_MAP(CDraw_SimpleView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDraw_SimpleView::OnFilePrintPreview)
  ON_COMMAND(ID_EDIT_UNDO, &CDraw_SimpleView::OnEditUndo)
  ON_COMMAND(ID_EDIT_CUT, &CDraw_SimpleView::OnEditCut)
  ON_COMMAND(ID_EDIT_COPY, &CDraw_SimpleView::OnEditCopy)
  ON_COMMAND(ID_EDIT_PASTE, &CDraw_SimpleView::OnEditPaste)
  ON_COMMAND(ID_VIEW_COLOR, &CDraw_SimpleView::OnViewColor)
  ON_COMMAND(ID_COORDINATE_OXYZ, &CDraw_SimpleView::OnCoordinateOxyz)
  ON_COMMAND(ID_COORDINATE_OXY, &CDraw_SimpleView::OnCoordinateOxy)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
  ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
  ON_WM_MOUSEWHEEL()

END_MESSAGE_MAP()

// CDraw_SimpleView construction/destruction
/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/
CDraw_SimpleView::CDraw_SimpleView()
{
	 // TODO: add construction code here
   m_bOXY   = FALSE ;
   m_bOXY   = FALSE ;
   count_oxy = 0;
   count_oxyz = 0;
   m_xAngle = 0;
   m_yAngle = 0;
   m_zoom   = 0;
}


/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/
CDraw_SimpleView::~CDraw_SimpleView()
{
}

/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/
BOOL CDraw_SimpleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
  cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}
/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/

int CDraw_SimpleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{	
	if (CView::OnCreate(lpCreateStruct) == -1){
        return -1;
	}
	// Goi ham khoi tao trang thai dau tien cua  ung dung 
    InitializeOpenGL();
    return 0;
}
// CDraw_SimpleView drawing

/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			: Damme88 - Developer phamtoanbonmat@gmail
* Time				:
*
******************************************************************************/

BOOL CDraw_SimpleView::InitializeOpenGL()
{
    //Get a DC for the Client Area
    m_pDC = new CClientDC(this);

    //Failure to Get DC
    if(m_pDC == NULL){
        MessageBox(_T("Error Obtaining DC"));
        return FALSE;
    }
	//Failure to set the pixel format
    if(!SetupPixelFormat()){
        return FALSE;
    }
	//Create Rendering Context
    m_hRC = ::wglCreateContext (m_pDC->GetSafeHdc ());

    //Failure to Create Rendering Context
    if(m_hRC == 0){
        MessageBox(_T("Error Creating RC"));
        return FALSE;
    }

	//Make the RC Current
    if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE){
        MessageBox(_T("Error making RC Current"));
        return FALSE;
    }
	//Specify Black as the clear color
    ::glClearColor(1.0f,1.0f,1.0f,1.0f);

    //Specify the back of the buffer as clear depth
    ::glClearDepth(1.0f);

    //Enable Depth Testing
    ::glEnable(GL_DEPTH_TEST);
}

/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/

BOOL CDraw_SimpleView::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd = 
    {
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd
		1,                                // version number
		PFD_DRAW_TO_WINDOW |              // support window
		PFD_SUPPORT_OPENGL |              // support OpenGL
		PFD_DOUBLEBUFFER,                 // double buffered
		PFD_TYPE_RGBA,                    // RGBA type
		24,                               // 24-bit color depth
		0, 0, 0, 0, 0, 0,                 // color bits ignored
		0,                                // no alpha buffer
		0,                                // shift bit ignored
		0,                                // no accumulation buffer
		0, 0, 0, 0,                       // accumulation bits ignored
		16,                               // 16-bit z-buffer
		0,                                // no stencil buffer
		0,                                // no auxiliary buffer
		PFD_MAIN_PLANE,                   // main layer
		0,                                // reserved
		0, 0, 0                           // layer masks ignored
    };
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
    if ( m_nPixelFormat == 0 ){
        return FALSE;
    }
	if ( ::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE){
        return FALSE;
    }
    return TRUE;
}

/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/

void CDraw_SimpleView::OnSize(UINT nType, int cx, int cy) 
{
    CView::OnSize(nType, cx, cy);
	GLdouble aspect_ratio; 
	if ( 0 >= cx || 0 >= cy ){
        return;
    }
	::gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f); 
	// select the full client area
    ::glViewport(0, 0, cx, cy);
    // compute the aspect ratio
    // this will keep all dimension scales equal
    aspect_ratio = (GLdouble)cx/(GLdouble)cy;
    // select the projection matrix and clear it
    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();
    // select the viewing volume
    ::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);
   // switch back to the modelview matrix and clear it
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
	// Lenh nay thuc hien viec lua chon goc nhin nhu mot cameral
	gluLookAt (0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/

BOOL CDraw_SimpleView::OnEraseBkgnd(CDC* pDC) 
{
    // TODO: Add your message handler code here and/or call default
    //comment out the original call
    //return CView::OnEraseBkgnd(pDC);
    //Tell Windows not to erase the background
    return TRUE;
}


/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/

void CDraw_SimpleView::OnDestroy() 
{
    CView::OnDestroy();
    // TODO: Add your message handler code here
	   //Make the RC non-current
    if(::wglMakeCurrent (0,0) == FALSE){
        MessageBox(_T("Could not make RC non-current"));
    }
	 //Delete the rendering context
    if(::wglDeleteContext (m_hRC)==FALSE){
        MessageBox(_T("Could not delete RC"));
    }
	//Delete the DC
    if(m_pDC){
        delete m_pDC;
    }
    //Set it to NULL
    m_pDC = NULL;
}

void CDraw_SimpleView::OnDraw(CDC* /*pDC*/)
{
	CDraw_SimpleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
  // Clear out the color & depth buffers
    ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	RenderScene();
	 // Tell OpenGL to flush its pipeline
    ::glFinish();
	 // Now Swap the buffers
    ::SwapBuffers( m_pDC->GetSafeHdc() );
	// TODO: add draw code for native data here
	// TODO: add draw code for native data here
}

/******************************************************************************
* Function Name		: RenderSecene 
* Purpose			: Ham quan trong la noi xay dung cac xu ly ve cua OpenGL
* Input Param		: ko co 
* Output Param		: ko co
* Writer			: Damme88 Developer Phamtoanbonmat@gmail.com
* Time				: Sunday 27/05/2010
*
******************************************************************************/

void CDraw_SimpleView::RenderScene ()
{
	 glLoadIdentity();
	 // Do xa gan 
     glTranslatef(0.0f, 0.0f, m_zoom - 20.0f);
	 // Do nghieng
     glRotatef(m_xAngle + 45.0f, 1.0f, 0.0f, 0.0f);
	   glRotatef(m_yAngle - 45.0f, 0.0f, 1.0f, 0.0f);

     if(m_bOXYZ == TRUE)
	 {	
	 // Truc OX co mau do 
		glColor3f(1.0f,0.0f,0.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
			 glVertex3f(0.0f,0.0f,0.0f);
			 glVertex3f(3.0f,0.0f,0.0f);
		glEnd();
    //Arrow for OX
    glBegin(GL_LINES);
			 glVertex3f(2.8f,0.2f,0.0f);
			 glVertex3f(3.0f,0.0f,0.0f);
		glEnd();
    glBegin(GL_LINES);
			 glVertex3f(2.8f,0.0f,0.2f);
			 glVertex3f(3.0f,0.0f,0.0f);
		glEnd();


	// Truc OY co mau xanh la cay
		glColor3f(0.0f,1.0f,0.0f);
		glLineWidth(3.0f);  
		glBegin(GL_LINES);
			 glVertex3f(0.0f,0.0f,0.0f);
			 glVertex3f(0.0f,3.0f,0.0f);
		glEnd();
    // Arrow for Oy
    glBegin(GL_LINES);
			 glVertex3f(0.2f,2.8f,0.0f);
			 glVertex3f(0.0f,3.0f,0.0f);
		glEnd();
    glBegin(GL_LINES);
			 glVertex3f(0.0f,2.8f,0.2f);
			 glVertex3f(0.0f,3.0f,0.0f);
		glEnd();

	// Truc OZ co mau xanh nuoc bien 
		glColor3f(0.0f,0.0f,1.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,3.0f);
		glEnd();
    // Arrow for OZ
    glBegin(GL_LINES);
		glVertex3f(0.2f,0.0f,2.8f);
		glVertex3f(0.0f,0.0f,3.0f);
		glEnd();
    glBegin(GL_LINES);
		glVertex3f(0.0f,0.2f,2.8f);
		glVertex3f(0.0f,0.0f,3.0f);
		glEnd();
	 }

	 if(m_bOXY == TRUE)
	 {
	 // Truc OX co mau do 
		glColor3f(1.0f,0.0f,0.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
			 glVertex2f(0.0f,0.0f);
			 glVertex2f(3.0f,0.0f);
		glEnd();
    // Arrow for OX
    glBegin(GL_LINES);
			 glVertex3f(2.8f,0.2f,0.0f);
			 glVertex3f(3.0f,0.0f,0.0f);
		glEnd();
    glBegin(GL_LINES);
			 glVertex3f(2.8f,0.0f,0.2f);
			 glVertex3f(3.0f,0.0f,0.0f);
		glEnd();
	// Truc OY co mau xanh la cay
		glColor3f(0.0f,1.0f,0.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
			 glVertex2f(0.0f,0.0f);
			 glVertex2f(0.0f,3.0f);
		glEnd();	 
    // Arrow for Oy
      glBegin(GL_LINES);
			 glVertex3f(0.2f,2.8f,0.0f);
			 glVertex3f(0.0f,3.0f,0.0f);
		glEnd();
    glBegin(GL_LINES);
			 glVertex3f(0.0f,2.8f,0.2f);
			 glVertex3f(0.0f,3.0f,0.0f);
		glEnd();
	 }
}

void CDraw_SimpleView::OnCoordinateOxy()
{
  count_oxy ++;
  count_oxyz =0;
  if (count_oxy%2!=0){
  m_bOXY = TRUE ;
	m_bOXYZ=FALSE ;
	InvalidateRect(NULL,FALSE);
  }
  else {
   m_bOXY = FALSE ;
	 m_bOXYZ=FALSE ;
	 InvalidateRect(NULL,FALSE);
  }
}

void CDraw_SimpleView::OnCoordinateOxyz()
{ 
   count_oxy = 0;
  count_oxyz ++;
  if (count_oxyz%2 != 0) {
    m_bOXYZ = TRUE ;
	  m_bOXY=FALSE ;
	  InvalidateRect(NULL,FALSE);
  }
  else {
    m_bOXYZ = FALSE ;
	  m_bOXY=FALSE ;
	  InvalidateRect(NULL,FALSE);
  }
}
void CDraw_SimpleView::OnEditUndo() {
}
void CDraw_SimpleView::OnEditCopy() {
}
void CDraw_SimpleView::OnEditCut() {
}
void CDraw_SimpleView::OnEditPaste() {
}

void CDraw_SimpleView::OnViewColor() {
  CColorDialog dlg ;
  dlg.DoModal();
}

void CDraw_SimpleView::OnLButtonDown(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  m_MouseDownPoint=point;
  SetCapture();
  CView::OnLButtonDown(nFlags, point);
}


void CDraw_SimpleView::OnLButtonUp(UINT nFlags, CPoint point) 
{
        // TODO: Add your message handler code here and/or call default
        m_MouseDownPoint=CPoint(0,0);
        ReleaseCapture();
        CView::OnLButtonUp(nFlags, point);
}

/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/

void CDraw_SimpleView::OnMouseMove(UINT nFlags, CPoint point) 
{
        // TODO: Add your message handler code here and/or call default
        // Check if we have captured the mouse
        if (GetCapture()==this)
        {
            //Increment the object rotation angles
            m_xAngle+=(point.y-m_MouseDownPoint.y)/3.6;
            m_yAngle+=(point.x-m_MouseDownPoint.x)/3.6;
            //Redraw the view
            InvalidateRect(NULL,FALSE);
            //Set the mouse point
            m_MouseDownPoint=point;
        }
        CView::OnMouseMove(nFlags, point);
}

BOOL CDraw_SimpleView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
  BOOL ret = FALSE ;
  if(zDelta >=0) {
    m_zoom = m_zoom + 0.4f;
    ret = TRUE ;
  }
  else {
    m_zoom = m_zoom - 0.4f;
    ret = TRUE ;
  }
  InvalidateRect(NULL,FALSE);
  //Set the mouse point
  m_MouseDownPoint=point;
  CWnd::OnMouseMove(nFlags, point);
  return ret;
}



void CDraw_SimpleView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CDraw_SimpleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDraw_SimpleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDraw_SimpleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDraw_SimpleView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDraw_SimpleView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CDraw_SimpleView diagnostics

#ifdef _DEBUG
void CDraw_SimpleView::AssertValid() const
{
	CView::AssertValid();
}

void CDraw_SimpleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDraw_SimpleDoc* CDraw_SimpleView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDraw_SimpleDoc)));
	return (CDraw_SimpleDoc*)m_pDocument;
}
#endif //_DEBUG


// CDraw_SimpleView message handlers
