
// Simple_DrawView.cpp : implementation of the CSimple_DrawView class
//

#include "stdafx.h"
#include "Simple_Draw.h"

#include "Simple_DrawDoc.h"
#include "Simple_DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_ALIGN_START  ID_ALIGN_LEFT
#define ID_ALIGN_END    ID_ALIGN_JUSTIFY

IMPLEMENT_DYNCREATE(CSimple_DrawView, CView)

BEGIN_MESSAGE_MAP(CSimple_DrawView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT,         &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT,  &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSimple_DrawView::OnFilePrintPreview)
  ON_COMMAND(ID_EDIT_UNDO,          &CSimple_DrawView::OnEditUndo)
  ON_COMMAND(ID_EDIT_CUT,           &CSimple_DrawView::OnEditCut)
  ON_COMMAND(ID_EDIT_COPY,          &CSimple_DrawView::OnEditCopy)
  ON_COMMAND(ID_EDIT_PASTE,         &CSimple_DrawView::OnEditPaste)

  ON_COMMAND(ID_COORDINATE_OXYZ,    &CSimple_DrawView::OnCoordinateOxyz)
  ON_COMMAND(ID_COORDINATE_OXY,     &CSimple_DrawView::OnCoordinateOxy)
  ON_COMMAND(ID_DRAW_GRID,          &CSimple_DrawView::OnDrawGrid)
  ON_COMMAND(ID_DRAW_COLOR,         &CSimple_DrawView::OnDrawColor)
  ON_COMMAND(ID_FRONT,              &CSimple_DrawView::OnViewFront)
  ON_COMMAND(ID_BEHIND,             &CSimple_DrawView::OnViewBehind)
  ON_COMMAND(ID_TOP,                &CSimple_DrawView::OnViewTop)
  ON_COMMAND(ID_BOTTOM,             &CSimple_DrawView::OnViewBottom)
  ON_COMMAND(ID_RIGHT,              &CSimple_DrawView::OnViewRight)
  ON_COMMAND(ID_LEFT,               &CSimple_DrawView::OnViewLeft)
  ON_COMMAND(ID_PAN_STANDAR,        &CSimple_DrawView::OnViewStandar)
  ON_COMMAND(ID_ZOOM_IN,            &CSimple_DrawView::OnZoomIn)
  ON_COMMAND(ID_ZOOM_OUT,           &CSimple_DrawView::OnZoomOut)
  ON_COMMAND(ID_ZOOM_STANDAR,       &CSimple_DrawView::OnZoomStandar)

    ON_COMMAND(ID_BOLD, &CSimple_DrawView::OnTextBold)
    ON_UPDATE_COMMAND_UI(ID_BOLD, &CSimple_DrawView::OnUpdateBold)

    ON_COMMAND(ID_ITALIC, &CSimple_DrawView::OnTextItalic)
    ON_UPDATE_COMMAND_UI(ID_ITALIC, &CSimple_DrawView::OnUpdateItalic)

    ON_COMMAND(ID_UNDER_LINE, &CSimple_DrawView::OnTextUnderLine)
    ON_UPDATE_COMMAND_UI(ID_UNDER_LINE, &CSimple_DrawView::OnUpdateUnderLine)

    ON_COMMAND_RANGE(ID_ALIGN_START, ID_ALIGN_END, &CSimple_DrawView::OnHandleAlign)
    ON_UPDATE_COMMAND_UI_RANGE(ID_ALIGN_START, ID_ALIGN_END, &CSimple_DrawView::OnUpdateHandleAlign)

    // Enable buttons for toolbar Draw
    ON_COMMAND(ID_DRAW_CIRCLE, &CSimple_DrawView::DrawCircle)
    ON_COMMAND(ID_DRAW_COLOR_PICKER, &CSimple_DrawView::DrawColorPic)
    ON_COMMAND(ID_DRAW_ERASER, &CSimple_DrawView::DrawEraser)
    ON_COMMAND(ID_DRAW_FILL_COLOR, &CSimple_DrawView::DrawColorFill)
    ON_COMMAND(ID_DRAW_POINT, &CSimple_DrawView::DrawPoint)
    ON_COMMAND(ID_DRAW_LINE, &CSimple_DrawView::DrawLine)
    ON_COMMAND(ID_DRAW_RECTANGLE, &CSimple_DrawView::DrawRectangle)
    ON_COMMAND(ID_DRAW_POLYGON, &CSimple_DrawView::DrawPolygon)
    ON_COMMAND(ID_DRAW_ROUNDED_RECTANGLE, &CSimple_DrawView::DrawRoundRectangle)
    ON_COMMAND(ID_DRAW_CURVE, &CSimple_DrawView::DrawCurve)


	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
  ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
  ON_WM_MOUSEWHEEL()

END_MESSAGE_MAP()

// CSimple_DrawView construction/destruction

CSimple_DrawView::CSimple_DrawView() :
   m_bOXY(FALSE),
   count_oxy(0),
   count_oxyz(0),
   count_grid(0),
   m_xAngle(0),
   m_yAngle(0),
   m_zoom(0),
   m_draw_grid(FALSE),
   m_texMode(0),
   m_texWrap(0),
   m_texFilter(0),
   m_text_bold(0),
   m_text_italic(0),
   m_text_under_line(0),
   check_bold_(false),
   check_italic_(false),
   check_underline_(false) {
  // m_Texture[0] = 0;
 //  m_Texture[1] = 0;
  // m_Texture[2] = 0;
 //  m_Texture[3] = 0;
 //  m_Texture[4] = 0;
   m_align_left = 1;
   m_align_right = 0;
   m_align_center = 0;
   m_align_justify = 0;
   m_draw_line = 0;
   m_count_draw_line = 0;

   // variable for draw
   check_down = FALSE;
   count_down = 0;
}


/******************************************************************************
* Function Name		: CSimple_DrawView
* Purpose			    : Ham huy cua Class CSimple_DrawView
* Input Param		  : Nothing
* Output Param		: Nothing
* Writer			    : Damme88_Developer_phamtoanbonmat@gmail.com
* Time				    : 08/2012
*
******************************************************************************/
CSimple_DrawView::~CSimple_DrawView() {
}


BOOL CSimple_DrawView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
  cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}


int CSimple_DrawView::OnCreate(LPCREATESTRUCT lpCreateStruct)  {	
	if (CView::OnCreate(lpCreateStruct) == -1){
        return -1;
	}
	// Goi ham khoi tao trang thai dau tien cua  ung dung 
    InitializeOpenGL();
    return 0;
}
// CSimple_DrawView drawing

BOOL CSimple_DrawView::InitializeOpenGL() {
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

BOOL CSimple_DrawView::SetupPixelFormat() {
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


void CSimple_DrawView::OnSize(UINT nType, int cx, int cy) {
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


BOOL CSimple_DrawView::OnEraseBkgnd(CDC* pDC) {
    // TODO: Add your message handler code here and/or call default
    //comment out the original call
    //return CView::OnEraseBkgnd(pDC);
    //Tell Windows not to erase the background
    return TRUE;
}


void CSimple_DrawView::OnDestroy() {
    status_text_editor_ = FALSE;
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


/******************************************************************************
* Function Name		: RenderScene
* Purpose			    : Ham nay thuc hien ve do hoa su dung OpenGL
* Input Param		  : Nothing
* Output Param		: Nothing
* Writer			    : Damme88_Developer_phamtoanbonmat@gmail.com
* Time				    : 08/2012
*
******************************************************************************/
void CSimple_DrawView::RenderScene () {
  glLoadIdentity();
	// Do xa gan 
  glTranslatef(0.0f, 0.0f, m_zoom - 20.0f);
	// Do nghieng
  glRotatef(m_xAngle + 45.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle - 45.0f, 0.0f, 1.0f, 0.0f);

  if (m_bOXYZ == TRUE) {	
	  // Truc OX co mau do 
		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(3.0f);

		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(3.0f, 0.0f, 0.0f);
		glEnd();
    //Arrow for OX
    glBegin(GL_LINES);
		glVertex3f(2.8f, 0.2f, 0.0f);
		glVertex3f(3.0f, 0.0f, 0.0f);
		glEnd();

    glBegin(GL_LINES);
		glVertex3f(2.8f, 0.0f, 0.2f);
	  glVertex3f(3.0f, 0.0f, 0.0f);
		glEnd();


	// Truc OY co mau xanh la cay
		glColor3f(0.0f, 1.0f, 0.0f);
		glLineWidth(3.0f);  
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
	  glVertex3f(0.0f, 3.0f, 0.0f);
		glEnd();
    // Arrow for Oy
    glBegin(GL_LINES);
		glVertex3f(0.2f, 2.8f, 0.0f);
	  glVertex3f(0.0f, 3.0f, 0.0f);
		glEnd();
    glBegin(GL_LINES);
		glVertex3f(0.0f, 2.8f, 0.2f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		glEnd();

	// Truc OZ co mau xanh nuoc bien 
		glColor3f(0.0f, 0.0f, 1.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 3.0f);
		glEnd();
    // Arrow for OZ
    glBegin(GL_LINES);
		glVertex3f(0.2f, 0.0f, 2.8f);
		glVertex3f(0.0f, 0.0f, 3.0f);
		glEnd();
    glBegin(GL_LINES);
		glVertex3f(0.0f, 0.2f, 2.8f);
		glVertex3f(0.0f, 0.0f, 3.0f);
		glEnd();
	 }

	 if(m_bOXY == TRUE) {
	 // Truc OX co mau do 
		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(3.0f, 0.0f);
		glEnd();
    // Arrow for OX
    glBegin(GL_LINES);
		glVertex3f(2.8f, 0.2f, 0.0f);
		glVertex3f(3.0f, 0.0f, 0.0f);
		glEnd();
    glBegin(GL_LINES);
		glVertex3f(2.8f, 0.0f, 0.2f);
		glVertex3f(3.0f, 0.0f, 0.0f);
		glEnd();
	// Truc OY co mau xanh la cay
		glColor3f(0.0f, 1.0f, 0.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 3.0f);
		glEnd();	 
    // Arrow for Oy
    glBegin(GL_LINES);
		glVertex3f(0.2f, 2.8f, 0.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		glEnd();
    glBegin(GL_LINES);
	  glVertex3f(0.0f, 2.8f, 0.2f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		glEnd();
	 }
   if (m_draw_grid == TRUE) {
     //Draw a Plane
     glColor3f(1.0f, 1.0f, 1.0f);
     glBegin(GL_POLYGON);
		 glVertex3f(10.0f, -4.5f, 10.0f);
		 glVertex3f(10.0f, -4.5f, -10.0f);
     glVertex3f(-10.0f, -4.5f, -10.0f);
		 glVertex3f(-10.0f, -4.5f, 10.0f);
		 glEnd();
     // Draw Grid
		 glColor3f(1.0f, 1.0f, 0.0f);
		 glLineWidth(4.0f);
     // OX +
     for (float i = 10.0; i >= 0; i = i-0.5) {
       glBegin(GL_LINES);
			 glVertex3f(i, -2.0f, 10.0f);
			 glVertex3f(i, -2.0f, -10.0f);
		   glEnd();
     }
      
     // OX -
     for (float i = - 10.0 ;i <=0;i=i+0.5) {
       glBegin(GL_LINES);
		   glVertex3f(i, -2.0f, 10.0f);
		   glVertex3f(i, -2.0f, -10.0f);
	     glEnd();
     }

     for (float i = 10.0f; i>=0; i = i-0.5) {
       glBegin(GL_LINES);
		   glVertex3f(10, -2.0f, i);
		   glVertex3f(-10, -2.0f, i);
	     glEnd();
     }

     for (float i = -10.0f; i <=0; i = i+0.5) {
       glBegin(GL_LINES);
		   glVertex3f(10, -2.0f, i);
		   glVertex3f(-10, -2.0f, i);
	     glEnd();
     }
   }
}




void CSimple_DrawView::OnCoordinateOxy()
{
  count_oxy ++;
  count_oxyz = 0;
  if (count_oxy %2 != 0) {
  m_bOXY = TRUE ;
	m_bOXYZ = FALSE ;
	InvalidateRect(NULL,FALSE);
  }
  else {
   m_bOXY = FALSE ;
	 m_bOXYZ = FALSE ;
	 InvalidateRect(NULL, FALSE);
  }
}

void CSimple_DrawView::OnCoordinateOxyz()
{ 
   count_oxy = 0;
  count_oxyz ++;
  if (count_oxyz%2 != 0) {
    m_bOXYZ = TRUE ;
	  m_bOXY = FALSE ;
	  InvalidateRect(NULL, FALSE);
  }
  else {
    m_bOXYZ = FALSE ;
	  m_bOXY = FALSE ;
	  InvalidateRect(NULL, FALSE);
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
     if(count_grid%2 != 0 ) {
         m_draw_grid = TRUE;
         InvalidateRect(NULL, FALSE);
     } else {
        m_draw_grid = FALSE;
        InvalidateRect(NULL, FALSE);
     }
}

void CSimple_DrawView::OnDrawColor() {
  CColorDialog dlg ;
  dlg.DoModal();
}

void CSimple_DrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  m_MouseDownPoint = point;
  SetCapture();
  CView::OnLButtonDown(nFlags, point);
  if (m_draw_line == 1) {
    m_first_point = point;
    check_down = TRUE;
  }
}


void CSimple_DrawView::OnLButtonUp(UINT nFlags, CPoint point)  {
        // TODO: Add your message handler code here and/or call default
        m_MouseDownPoint = CPoint(0, 0);
        ReleaseCapture();
        CView::OnLButtonUp(nFlags, point);
  if (m_draw_line == 1) {
    check_down = FALSE;
    m_end_point = point;
  }
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
        if (GetCapture() == this){
          //Increment the object rotation angles
          m_xAngle += (point.y - m_MouseDownPoint.y)/3.6;
          m_yAngle += (point.x - m_MouseDownPoint.x)/3.6;
            //Redraw the view
          InvalidateRect(NULL, FALSE);
            //Set the mouse point
          m_MouseDownPoint = point;
        }
        CView::OnMouseMove(nFlags, point);

        // handle draw 
        if ( m_draw_line == 1) {
          CDC* pdc = GetDC();
          if( check_down == FALSE){
             pdc->MoveTo(point.x, point.y);
             pdc->LineTo(m_first_point.x, m_first_point.y);
          } else {
              pdc->LineTo(m_end_point.x, m_first_point.y);
              pdc->MoveTo(m_first_point.x, m_first_point.y);
          }
        }
}


BOOL CSimple_DrawView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
  BOOL ret = FALSE ;
  if (zDelta >=0) {
    m_zoom = m_zoom + 0.4f;
    ret = TRUE ;
  }
  else {
    m_zoom = m_zoom - 0.4f;
    ret = TRUE ;
  }
  InvalidateRect(NULL,FALSE);
  //Set the mouse point
  m_MouseDownPoint = point;
  CWnd::OnMouseMove(nFlags, point);
  return ret;
}

void CSimple_DrawView::OnViewFront() {
}
void CSimple_DrawView::OnViewBehind() {
}
void CSimple_DrawView::OnViewTop() {
}
void CSimple_DrawView::OnViewBottom() {
}
void CSimple_DrawView::OnViewRight() {
}
void CSimple_DrawView::OnViewLeft() {
}
void CSimple_DrawView::OnViewStandar() {
}
void CSimple_DrawView::OnZoomIn() {
}
void CSimple_DrawView::OnZoomOut() {
}
void CSimple_DrawView::OnZoomStandar() {
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

void CSimple_DrawView::OnTextBold() {
  if (check_bold_ == true) {
    m_text_bold = 0;
    check_bold_ = false;
  } else {
    m_text_bold = 1;
    check_bold_ = true;
  }
}

void CSimple_DrawView::OnTextItalic() {

  if (check_italic_ == true) {
    m_text_italic = 0;
    check_italic_ = false;
  } else {
    m_text_italic = 1;
    check_italic_ = true;
  }
}

void CSimple_DrawView::OnTextUnderLine() {
  if (check_underline_ == true) {
    m_text_under_line = 0;
    check_underline_ = false;
  } else {
    m_text_under_line = 1;
    check_underline_ = true;
  }
}

void CSimple_DrawView::OnUpdateBold(CCmdUI * pcmdui) {
  if (m_text_bold ==1) {
    pcmdui->SetCheck(1);
  } else {
    pcmdui->SetCheck(0);
  }
}

void CSimple_DrawView::OnUpdateItalic(CCmdUI * pcmdui) {
  if (m_text_italic ==1) {
    pcmdui->SetCheck(1);
  } else {
    pcmdui->SetCheck(0);
  }
}


void CSimple_DrawView::OnUpdateUnderLine(CCmdUI *pcmdui) {
  if (m_text_under_line ==1) {
    pcmdui->SetCheck(1);
  } else {
    pcmdui->SetCheck(0);
  }
}


void CSimple_DrawView::OnHandleAlign(UINT nID) {
  if (nID == ID_ALIGN_LEFT) {
    m_align_left = 1;
    m_align_center = 0;
    m_align_right = 0;
    m_align_justify = 0;
  }
  if (nID == ID_ALIGN_RIGHT) {
    m_align_left = 0;
    m_align_center = 0;
    m_align_right = 1;
    m_align_justify = 0;
  }
  if (nID == ID_ALIGN_CENTER) {
    m_align_left = 0;
    m_align_center = 1;
    m_align_right = 0;
    m_align_justify = 0;
  }
  if (nID == ID_ALIGN_JUSTIFY) {
    m_align_left = 0;
    m_align_center = 0;
    m_align_right = 0;
    m_align_justify = 1;
  }
}

void CSimple_DrawView::OnUpdateHandleAlign(CCmdUI *pcmdui) {
  if (pcmdui->m_nID == ID_ALIGN_LEFT) {
    if (m_align_left) 
      pcmdui->SetCheck(1);
    else
    pcmdui->SetCheck(0);
  } else if (pcmdui->m_nID == ID_ALIGN_RIGHT) {
    if (m_align_right) 
      pcmdui->SetCheck(1);
    else
    pcmdui->SetCheck(0);
  } else if (pcmdui->m_nID == ID_ALIGN_CENTER) {
    if (m_align_center) 
      pcmdui->SetCheck(1);
    else
    pcmdui->SetCheck(0);
  } else if (pcmdui->m_nID == ID_ALIGN_JUSTIFY) {
    if (m_align_justify) 
      pcmdui->SetCheck(1);
    else
    pcmdui->SetCheck(0);
  }
}


void CSimple_DrawView::OnSo1() {
  AfxMessageBox(L" XIN CHAO CAC BAN");
}


void CSimple_DrawView::DrawLine() {
}
void CSimple_DrawView::DrawCurve() {
}
void CSimple_DrawView::DrawCircle() {
}
void CSimple_DrawView::DrawRectangle() {
}
void CSimple_DrawView::DrawRoundRectangle() {
}
void CSimple_DrawView::DrawPoint() {
}
void CSimple_DrawView::DrawColorPic() {
}
void CSimple_DrawView::DrawColorFill() {
}
void CSimple_DrawView::DrawEraser() {
}
void CSimple_DrawView::DrawPolygon() {
}






    
void CSimple_DrawView::OnDrawline() {
  m_count_draw_line ++;
  if (m_count_draw_line %2 != 0)
    m_draw_line = 1;
  else m_draw_line = 0;
  if(m_count_draw_line == 0)
    m_count_draw_line = 0 ;
}
void CSimple_DrawView::OnUpdateDrawLine(CCmdUI *pcmdui) {
  if (m_draw_line ==1 )
    pcmdui->SetCheck(1);
  else
    pcmdui->SetCheck(0);
}
