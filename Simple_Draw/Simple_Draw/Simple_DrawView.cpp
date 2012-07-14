
// Simple_DrawView.cpp : implementation of the CSimple_DrawView class
//

#include "stdafx.h"
#include "Simple_Draw.h"

#include "Simple_DrawDoc.h"
#include "Simple_DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimple_DrawView

IMPLEMENT_DYNCREATE(CSimple_DrawView, CView)

BEGIN_MESSAGE_MAP(CSimple_DrawView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSimple_DrawView::OnFilePrintPreview)
  ON_COMMAND(ID_EDIT_UNDO, &CSimple_DrawView::OnEditUndo)
  ON_COMMAND(ID_EDIT_CUT, &CSimple_DrawView::OnEditCut)
  ON_COMMAND(ID_EDIT_COPY, &CSimple_DrawView::OnEditCopy)
  ON_COMMAND(ID_EDIT_PASTE, &CSimple_DrawView::OnEditPaste)

  ON_COMMAND(ID_COORDINATE_OXYZ, &CSimple_DrawView::OnCoordinateOxyz)
  ON_COMMAND(ID_COORDINATE_OXY, &CSimple_DrawView::OnCoordinateOxy)
  ON_COMMAND(ID_DRAW_GRID, &CSimple_DrawView::OnDrawGrid)
  ON_COMMAND(ID_DRAW_COLOR, &CSimple_DrawView::OnDrawColor)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
  ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
  ON_WM_MOUSEWHEEL()
  ON_BN_CLICKED(IDC_SUBMIT_BTN, &CSimple_DrawView::OnBnClickedSubmitBtn)
END_MESSAGE_MAP()

// CSimple_DrawView construction/destruction

CSimple_DrawView::CSimple_DrawView()
{
	// TODO: add construction code here	
   m_bOXY   = FALSE ;
   m_bOXY   = FALSE ;
   count_oxy = 0;
   count_oxyz = 0;
   count_grid = 0;
   m_xAngle = 0;
   m_yAngle = 0;
   m_zoom   = 0;
   m_draw_grid = FALSE;
   m_texMode = 0;
   m_texWrap = 0;
   m_texFilter = 0;
   m_Texture[0]=0;
   m_Texture[1]=0;
   m_Texture[2]=0;
   m_Texture[3]=0;
   m_Texture[4]=0;
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
CSimple_DrawView::~CSimple_DrawView()
{
}


BOOL CSimple_DrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}


int CSimple_DrawView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{	
	if (CView::OnCreate(lpCreateStruct) == -1){
        return -1;
	}
	// Goi ham khoi tao trang thai dau tien cua  ung dung 
    InitializeOpenGL();
    return 0;
}
// CSimple_DrawView drawing

BOOL CSimple_DrawView::InitializeOpenGL()
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
    ::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //Specify the back of the buffer as clear depth
    ::glClearDepth(1.0f);

    //Enable Depth Testing
    ::glEnable(GL_DEPTH_TEST);
}

BOOL CSimple_DrawView::SetupPixelFormat()
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


void CSimple_DrawView::OnSize(UINT nType, int cx, int cy) 
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


BOOL CSimple_DrawView::OnEraseBkgnd(CDC* pDC) 
{
    // TODO: Add your message handler code here and/or call default
    //comment out the original call
    //return CView::OnEraseBkgnd(pDC);
    //Tell Windows not to erase the background
    return TRUE;
}


void CSimple_DrawView::OnDestroy() 
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

void CSimple_DrawView::OnDraw(CDC* /*pDC*/)
{
	CSimple_DrawDoc* pDoc = GetDocument();
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


void CSimple_DrawView::RenderScene ()
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
   if (m_draw_grid == TRUE) {
     // Draw a Plane
     glColor3f(1.0f,1.0f,1.0f);
      glBegin(GL_POLYGON);
			   glVertex3f(10.0f,-4.5f,10.0f);
			   glVertex3f(10.0f,-4.5f,-10.0f);
         glVertex3f(-10.0f,-4.5f,-10.0f);
			   glVertex3f(-10.0f,-4.5f,10.0f);
		  glEnd();
     // Draw Grid
		  glColor3f(1.0f,1.0f,0.0f);
		  glLineWidth(4.0f);
      // OX +
     for (float i = 10.0 ;i >=0;i=i-0.5) {
         glBegin(GL_LINES);
			   glVertex3f(i,-2.0f,10.0f);
			   glVertex3f(i,-2.0f,-10.0f);
		  glEnd();
     }
      
     // OX -
     for (float i = - 10.0 ;i <=0;i=i+0.5) {
       glBegin(GL_LINES);
		   glVertex3f(i,-2.0f,10.0f);
		   glVertex3f(i,-2.0f,-10.0f);
	     glEnd();
     }

     for (float i = 10.0f; i>=0;i=i-0.5) {
       glBegin(GL_LINES);
		   glVertex3f(10,-2.0f,i);
		   glVertex3f(-10,-2.0f,i);
	     glEnd();
     }

     for (float i = -10.0f; i<=0;i=i+0.5) {
       glBegin(GL_LINES);
		   glVertex3f(10,-2.0f,i);
		   glVertex3f(-10,-2.0f,i);
	     glEnd();
     }
   }

}




void CSimple_DrawView::OnCoordinateOxy()
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

void CSimple_DrawView::OnCoordinateOxyz()
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
void CSimple_DrawView::OnEditUndo() {
}
void CSimple_DrawView::OnEditCopy() {
}
void CSimple_DrawView::OnEditCut() {
}
void CSimple_DrawView::OnEditPaste() {
}


void CSimple_DrawView::OnDrawGrid() {
     count_grid ++ ;
     if(count_grid%2 !=0 ) {
         m_draw_grid = TRUE;
         InvalidateRect(NULL,FALSE);
     } else {
        m_draw_grid = FALSE;
        InvalidateRect(NULL,FALSE);
     }
}

void CSimple_DrawView::OnDrawColor() {
  CColorDialog dlg ;
  dlg.DoModal();
}

void CSimple_DrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  m_MouseDownPoint=point;
  SetCapture();
  CView::OnLButtonDown(nFlags, point);
}


void CSimple_DrawView::OnLButtonUp(UINT nFlags, CPoint point) 
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

void CSimple_DrawView::OnMouseMove(UINT nFlags, CPoint point) 
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

BOOL CSimple_DrawView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
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


// CSimple_DrawView printing
void CSimple_DrawView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSimple_DrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSimple_DrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSimple_DrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSimple_DrawView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSimple_DrawView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CSimple_DrawView diagnostics

#ifdef _DEBUG
void CSimple_DrawView::AssertValid() const
{
	CView::AssertValid();
}

void CSimple_DrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimple_DrawDoc* CSimple_DrawView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimple_DrawDoc)));
	return (CSimple_DrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimple_DrawView message handlers

void CSimple_DrawView::OnBnClickedSubmitBtn()
{
  // TODO: Add your control notification handler code here
  MessageBox(_T("Thank you for your consideration\n"));
}
