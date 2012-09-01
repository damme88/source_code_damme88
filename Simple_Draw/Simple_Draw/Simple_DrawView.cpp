
// Simple_DrawView.cpp : implementation of the CSimple_DrawView class

#include "stdafx.h"
#include "Simple_Draw.h"

#include "Simple_DrawDoc.h"
#include "Simple_DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_ALIGN_START  ID_ALIGN_LEFT
#define ID_ALIGN_END    ID_ALIGN_JUSTIFY

#define ID_MOVE_START    ID_MOVE_UP
#define ID_MOVE_END      ID_MOVE_RIGHT

#define ID_ZOOM_START    ID_ZOOM_IN
#define ID_ZOOM_END      ID_ZOOM_STANDAR

#define ID_2D_START      ID_2DOBJECT_POINTS
#define ID_2D_END        ID_2DOBJECT_POLYGON

#define ID_3D_START      ID_3DOBJECT_WRITECUBE
#define ID_3D_END        ID_3DOBJECT_WRITELCOSAHEDRON


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

  ON_COMMAND_RANGE(ID_ZOOM_START,ID_ZOOM_END,  &CSimple_DrawView::OnHandleZoom)

  ON_COMMAND(ID_DRAW_3DTEXT,         &CSimple_DrawView::Create3DTextList)
  ON_COMMAND(ID_DRAW_TEXT2D,         &CSimple_DrawView::Create2DTextLists)

  ON_COMMAND_RANGE(ID_MOVE_START, ID_MOVE_END, &CSimple_DrawView::OnHandleMoveObject)

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

  ON_COMMAND_RANGE(ID_2D_START, ID_2D_END, &CSimple_DrawView::Draw2DObject)
  ON_COMMAND_RANGE(ID_3D_START, ID_3D_END, &CSimple_DrawView::Draw3DObject)



	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
  ON_WM_KEYDOWN()
  ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
  ON_WM_MOUSEWHEEL()

END_MESSAGE_MAP()

// CSimple_DrawView construction/destruction

CSimple_DrawView::CSimple_DrawView() :
   m_bOXY(FALSE),
   check_oxy(false),
   check_oxyz(false),
   check_grid(false),
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
   check_underline_(false),
   m_align_left(1),
   m_align_right(0),
   m_align_center(0),
   m_align_justify(0),
   m_draw_line(0),
   m_count_draw_line(0),
   count_down(0),
   // variable for draw
   check_down(FALSE),
   // Variable for move Object 
   m_xPos(0.0f),
	 m_yPos(0.0f),
   m_b2DText(0),
   m_b3DText(0),
   enalbe_point_(false),
   enable_line_(false),
   enable_polygon_(false),
   enable_triangle_(false),
   enable_circle_(false),
   enable_square_(false),
   enable_rectang_(false),
	 enable_cube_(false),
	 enable_torus_(false),
	 enable_teaport_(false),
	 enable_lsahedron_(false),
   enable_sphere_(false)
{
  red_color_ = 255;
  green_color_ = 0;
  blue_color_ = 0;
  gl_red_color_ = 1.0f;
  gl_green_color_ = 1.0f;
  gl_blue_color_ = 0.0f;
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
  glTranslatef(m_xPos, m_yPos, m_zoom - 20.0f);
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

    if(m_b2DText) {
    // Position The Text On The Screen
    glColor3f(1.0f, 0.25f, 0.25f);
    glDisable(GL_LIGHTING);
    glRasterPos2f(0,0);
    glListBase(m_2DTextList);
    glCallLists(6, GL_UNSIGNED_BYTE , __T("Damme88"));
    glEnable(GL_LIGHTING);
  }
  if(m_b3DText) {
    glColor3f(1.0f, 0.25f, 1.0f);
    glDisable(GL_LIGHTING);
    glListBase(m_3DTextList);
    glCallLists(6, GL_UNSIGNED_BYTE , __T("Damme88"));
  }

   if (m_draw_grid == TRUE) {
     //Draw a Plane
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     glColor3f(gl_red_color_, gl_green_color_, gl_blue_color_);
     glBegin(GL_POLYGON);
		 glVertex3f(10.0f, -4.5f, 10.0f);
		 glVertex3f(10.0f, -4.5f, -10.0f);
     glVertex3f(-10.0f, -4.5f, -10.0f);
		 glVertex3f(-10.0f, -4.5f, 10.0f);
		 glEnd();

     // Draw Grid
		 //glColor3f(1.0f, 1.0f, 0.0f);
     glColor3f(theApp.glred_color_, theApp.glgreen_color_, theApp.glblue_color_);
     glLineWidth(theApp.glline_grid_size_);
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

   OnDraw2DObject();
   OnDraw3DObject();
   DrawCubeFull();
}


void CSimple_DrawView::OnCoordinateOxy()
{
  check_oxyz = false;
  if (check_oxy == false) {
  m_bOXY = TRUE ;
	m_bOXYZ = FALSE ;
  check_oxy = true;
  InvalidateRect(NULL,FALSE);
  } else {
   m_bOXY = FALSE ;
	 m_bOXYZ = FALSE ;
   check_oxy = false;
	 InvalidateRect(NULL, FALSE);
  }
}

void CSimple_DrawView::OnCoordinateOxyz()
{ 
  check_oxy = false;
  if (check_oxyz == false) {
    m_bOXYZ = TRUE ;
	  m_bOXY = FALSE ;
    check_oxyz = true;
	  InvalidateRect(NULL, FALSE);
  }
  else {
    m_bOXYZ = FALSE ;
	  m_bOXY = FALSE ;
    check_oxyz = false;
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
  if(check_grid == false ) {
         m_draw_grid = TRUE;
         InvalidateRect(NULL, FALSE);
         check_grid = true;
     } else {
        m_draw_grid = FALSE;
        InvalidateRect(NULL, FALSE);
        check_grid = false;
     }
}

void CSimple_DrawView::OnDrawColor() {
  CColorDialog dlg ;
  dlg.DoModal();
  COLORREF color;
  if (IDOK == TRUE) {
    color = dlg.GetColor();
    red_color_ = GetRValue(color);
    green_color_ = GetGValue(color);
    blue_color_ = GetBValue(color);
    gl_red_color_ = (GLfloat)red_color_/255.0f;
    gl_green_color_ = (GLfloat)green_color_/255.0f;
    gl_blue_color_ = (GLfloat)blue_color_/255.0f;
    InvalidateRect(NULL, TRUE);
  }
}

void CSimple_DrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  m_MouseDownPoint = point;
  SetCapture();
  CView::OnLButtonDown(nFlags, point);
 
}


void CSimple_DrawView::OnLButtonUp(UINT nFlags, CPoint point)  {
        // TODO: Add your message handler code here and/or call default
        m_MouseDownPoint = CPoint(0, 0);
        ReleaseCapture();
        CView::OnLButtonUp(nFlags, point);
}

void CSimple_DrawView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
        // TODO: Add your message handler code here and/or call default
        switch (nChar)
        {
            case VK_UP:        m_yPos = m_yPos + 0.5f;
                                          break;
            case VK_DOWN:      m_yPos = m_yPos - 0.5f;
                                          break;
            case VK_LEFT:      m_xPos = m_xPos - 0.5f;
                                          break;
            case VK_RIGHT:     m_xPos = m_xPos + 0.5f;
                                          break;
        } 
        InvalidateRect(NULL,FALSE);
        CView::OnKeyDown(nChar, nRepCnt, nFlags);
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
    m_zoom = m_zoom + 0.5f;
    ret = TRUE ;
  }
  else {
    m_zoom = m_zoom - 0.5f;
    ret = TRUE ;
  }
  InvalidateRect(NULL,FALSE);
  //Set the mouse point
  m_MouseDownPoint = point;
  CWnd::OnMouseMove(nFlags, point);
  return ret;
}

void CSimple_DrawView::OnViewFront() {
  m_xAngle = -45;
  m_yAngle = 45;
  InvalidateRect(NULL, FALSE);
}
void CSimple_DrawView::OnViewBehind() {
  m_xAngle = -45;
  m_yAngle = 45;
  InvalidateRect(NULL, FALSE);
}
void CSimple_DrawView::OnViewTop() {
  m_xAngle = 45;
  m_yAngle = -45;
  InvalidateRect(NULL, FALSE);
}
void CSimple_DrawView::OnViewBottom() {
  m_xAngle = 0;
  m_yAngle = -45;
  InvalidateRect(NULL, FALSE);
}
void CSimple_DrawView::OnViewRight() {
  m_xAngle = 45;
  m_yAngle = 0;
  InvalidateRect(NULL, FALSE);
}
void CSimple_DrawView::OnViewLeft() {
  m_xAngle = 45;
  m_yAngle = 45;
  InvalidateRect(NULL, FALSE);
}
void CSimple_DrawView::OnViewStandar() {
  m_xAngle = 0;
  m_yAngle = 0;
  InvalidateRect(NULL, FALSE);
}
void CSimple_DrawView::OnHandleZoom(UINT nID) {
  if (nID == ID_ZOOM_IN)
    m_zoom = m_zoom + 0.5;
  if (nID == ID_ZOOM_OUT)
    m_zoom = m_zoom - 0.5;
  if (nID == ID_ZOOM_STANDAR)
    m_zoom = -15;
  InvalidateRect(NULL, FALSE);
}


// Handling Move for Object
void CSimple_DrawView::OnHandleMoveObject(UINT nID) {
  if (nID == ID_MOVE_UP)
    m_yPos = m_yPos + 0.5f;
  else if (nID == ID_MOVE_DOWN) 
    m_yPos = m_yPos - 0.5f;
  else if (nID == ID_MOVE_LEFT)
    m_xPos = m_xPos - 0.5f;
  else
    m_xPos = m_xPos + 0.5f;
  InvalidateRect(NULL,FALSE);
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

// Draw a text in OPenGL and MFC
void CSimple_DrawView::Create3DTextList() {
  CFont m_font;
  GLYPHMETRICSFLOAT agmf[256];
  // Create a true Type font 
  m_font.CreateFont(-12,                 // Heigh of Font
                   0,                  // Width of Font
                   0,                  // Angle of EsCapement
                   0,                  // Orientation Angle
                   FW_BOLD,            // Font Weight
                   FALSE,              // Italic = false
                   FALSE,              // Under = false
                   FALSE,              // Strikeout
                   ANSI_CHARSET,       // Character Set indentifier
                   OUT_TT_PRECIS,                 // Output Precision
                   CLIP_DEFAULT_PRECIS,           // Clipping Precision
                   ANTIALIASED_QUALITY,           // Output Quality
                   FF_DONTCARE | DEFAULT_PITCH,  // Family and Pitch
                   L"Algerin" ); 

  CFont* m_pOldFont = m_pDC->SelectObject(&m_font);
  // create display lists for glyphs 0 through 255 with 0.1 extrusion 
  // and default deviation. The display list numbering starts at 1000 
  // (it could be any number) 
  m_3DTextList = glGenLists(256);
  wglUseFontOutlines(m_pDC->GetSafeHdc(), 0, 255, m_3DTextList, 0.0f,

                                0.5f,WGL_FONT_POLYGONS, agmf); 

   m_pDC->SelectObject(m_pOldFont);
   m_b3DText = 1;
   InvalidateRect(NULL, FALSE);
}


void CSimple_DrawView::Create2DTextLists() {
  m_2DTextList = glGenLists(256);
  // Create a set of bitmap display lists 
  // based on the glyphs in the currently selected font 
   // in the current DC for use in the current OpenGL RC using wglUseFontBitmaps

  wglUseFontBitmaps(m_pDC->GetSafeHdc(), 0, 255, m_2DTextList); 
  m_b2DText = 1;
  InvalidateRect(NULL, FALSE);
}


void CSimple_DrawView::Draw2DObject(UINT nID) {
  if (nID == ID_2DOBJECT_LINES) {
    enable_line_ = true;
    enalbe_point_ = false;
    enable_circle_ = false;
    enable_rectang_ = false;
    enable_triangle_ = false;
    enable_polygon_ = false;
    enable_square_ = false;
  }
  if (nID == ID_2DOBJECT_POINTS) {
      enable_line_ = false;
    enalbe_point_ = true;
    enable_circle_ = false;
    enable_rectang_ = false;
    enable_triangle_ = false;
    enable_polygon_ = false;
    enable_square_ = false;
  }
  if (nID == ID_2DOBJECT_CRICLE) {
      enable_line_ = false;
    enalbe_point_ = false;
    enable_circle_ = true;
    enable_rectang_ = false;
    enable_triangle_ = false;
    enable_polygon_ = false;
    enable_square_ = false;
  }
  if (nID == ID_2DOBJECT_RECTANG) {
    enable_line_ = false;
    enalbe_point_ = false;
    enable_circle_ = false;
    enable_rectang_ = true;
    enable_triangle_ = false;
    enable_polygon_ = false;
    enable_square_ = false;
  }
  if (nID == ID_2DOBJECT_SQUARE) {
    enable_line_ = false;
    enalbe_point_ = false;
    enable_circle_ = false;
    enable_rectang_ = false;
    enable_triangle_ = false;
    enable_polygon_ = false;
    enable_square_ = true;
  }
  if (nID == ID_2DOBJECT_TRIANGLE) {
    enable_line_ = false;
    enalbe_point_ = false;
    enable_circle_ = false;
    enable_rectang_ = false;
    enable_triangle_ = true;
    enable_polygon_ = false;
    enable_square_ = false;
  }
  if (nID == ID_2DOBJECT_POLYGON) {
    enable_line_ = false;
    enalbe_point_ = false;
    enable_circle_ = false;
    enable_rectang_ = false;
    enable_triangle_ = false;
    enable_polygon_ = true;
    enable_square_ = false;
  }
  InvalidateRect(NULL);
}

void CSimple_DrawView::Draw3DObject(UINT nID) {
  if (nID == ID_3DOBJECT_WRITECUBE) {
    enable_cube_ = true;
    enable_teaport_ = false;
    enable_torus_ = false;
    enable_lsahedron_ = false;
    enable_sphere_ = false;
  }
  if (nID == ID_3DOBJECT_WRITETEAPORT) {
    enable_cube_ = false;
    enable_teaport_ = true;
    enable_torus_ = false;
    enable_lsahedron_ = false;
    enable_sphere_ = false;
  }
  if (nID == ID_3DOBJECT_WRITETOURUS) {
    enable_cube_ = false;
    enable_teaport_ = false;
    enable_torus_ = true;
    enable_lsahedron_ = false;
    enable_sphere_ = false;
  }
  if (nID == ID_3DOBJECT_WRITELCOSAHEDRON) {
    enable_cube_ = false;
    enable_teaport_ = false;
    enable_torus_ = false;
    enable_lsahedron_ = true;
    enable_sphere_ = false;
  }
  if (nID == ID_3DOBJECT_SPHERE) {
    enable_cube_ = false;
    enable_teaport_ = false;
    enable_torus_ = false;
    enable_lsahedron_ = false;
    enable_sphere_ = true;
  }
  InvalidateRect(NULL);
}

void CSimple_DrawView::OnDraw2DObject() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  if (enalbe_point_ == true) {
    glColor3f(1.0f, 0.0f, 0.0f);
		glPointSize(3.0f);
		glBegin(GL_POINTS);
	  glVertex2f(0.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glEnd();
  }

  if (enable_line_ == true) {
 		glColor3f(0.0f, 1.0f, 0.0f);
		glPointSize(3.0f);
		glBegin(GL_LINES);
	  glVertex2f(0.0f, 0.0f);
		glVertex2f(10.0f, 0.0f);
		glEnd(); 
  }

  if (enable_circle_ == true) {
   const float PI = 3.14;
   glBegin(GL_LINE_STRIP);
   glLineWidth(3.0f);
   glColor3f(0.5f, 0.5f, 1.0f);
   for(int i=0; i <= 360; i++)
   glVertex3f(sin(i*PI/180)*5, cos(i*PI/180)*5, 1);
   glEnd();
  }

  if (enable_rectang_ == true) {
  }

  if (enable_triangle_ == true) {
    glColor3f(1.0f,0.0f,1.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(1.0f,0.0f);
		glVertex2f(1.0f,0.5f);
		glVertex2f(0.5f,0.5f);
		glEnd();
  }

  if (enable_polygon_ == true) {
    glColor3f(1.0f, 1.0f, 0.5f);
		glBegin(GL_POLYGON);
	  glVertex2f(0.0f,0.0f);
	  glVertex2f(1.0f,0.0f);
		glVertex2f(1.0f,1.0f);
		glVertex2f(0.0f,1.5f);
		glEnd();
  }

   if (enable_square_ == true) {
  }
}


void CSimple_DrawView::OnDraw3DObject() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if( enable_cube_== true){
     glLineWidth(1.0f);
		 glColor3f(1.0f, 0.1f, 1.0f);
		 glutWireCube(2.0f);
	 }
  if (enable_torus_ == true) {
     glLineWidth(1.0f);
    glColor3f(1.0f,0.0f,0.0f);
		glutWireTorus(0.5f, 1.0f, 50, 50);	
  }
  if (enable_teaport_ == true) {
     glLineWidth(1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
		glutWireTeapot(2.0f);
  }
  if ( enable_lsahedron_ == true) {
     glLineWidth(1.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
		glutWireIcosahedron();
  }
  if (enable_sphere_ == true) {
    //DrawCylinder();
    DrawQuadric();
  }
}

void CSimple_DrawView::DrawQuadric() {
  SetupLighting();
  glColor3f(gl_red_color_ , gl_green_color_, gl_blue_color_);
  glLineWidth(1.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D , 5);
  GLUquadricObj* obj;
  obj = gluNewQuadric();
  gluQuadricNormals(obj, GLU_SMOOTH);
  gluQuadricTexture(obj, GL_TRUE);
  gluSphere(obj, 3.0f, 100, 100);
}

void CSimple_DrawView::DrawCylinder() {
  glColor3f(1.0f, 0.3f, 0.8f);
  //glLineWidth(1.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBlendFunc(GL_ONE, GL_ONE);
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  GLUquadricObj* obj;
  obj = gluNewQuadric();
  gluCylinder(obj, 1.0, 1.0, 2.0, 50, 50);
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);

}

void CSimple_DrawView::DrawCubeFull() {
  
}


void CSimple_DrawView::SetupLighting() {
  // khoi tao thuoc tinh material
  GLfloat matSpecular[] = {0.5f, 0.0f, 0.0f, 0.0f};
  // do lon cua diem sang value cang cao thi no cang nho
  GLfloat matShininess[] = {100.0f};
  // Phu vat lieu toan bo 
  GLfloat matAmbient[] = {0.25f, 0.25f, 0.25f, 1.0f};
  // phu vat lieu 1 phan (1 nua)
  GLfloat matDiffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};

  // goi ham xu ly tao chat lieu voi cac gia tri da duoc khai bao o tren
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
  glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);

  // Handle lightin
  // cho phep chieu sang
  glEnable(GL_LIGHTING);

  // chi dinh 1 huong chieu sang co ban
  GLfloat ambien1[] = {1.0f, 0.5f, 0.5f};
  GLfloat diffuse1[] = {1.0f, 0.5f, 0.5f};
  GLfloat specular1[] = {1.0f, 0.0f, 0.0f};
  GLfloat position1[] = {0.0f, 0.0f, 5.0f, 0.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambien1);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse1);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular1);
  glLightfv(GL_LIGHT0, GL_POSITION, position1);

  // cho phep huong chieu sang
  glEnable(GL_LIGHT0);
}