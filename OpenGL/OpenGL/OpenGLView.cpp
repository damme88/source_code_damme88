// OpenGLView.cpp : implementation of the COpenGLView class


#include "stdafx.h"
#include "OpenGL.h"

#include "OpenGLDoc.h"
#include "OpenGLView.h"
#include "Struct.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern Triangle GLPoint ;
long  num  = 30000; 
// COpenGLView
IMPLEMENT_DYNCREATE(COpenGLView, CView)


/******************************************************************************
* Phan xu ly thong diep cua Windows trong MFC
* Thuc hien viec anh xa cac message nhan duoc tuong ung voi ham can goi den 
******************************************************************************/

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	// Xu ly thong diep cho viec tao windows, goi den ham OnCreate
	ON_WM_CREATE()
	// Xu ly anh xa thong diep kich thuoc windows va goi ham OnSize
	ON_WM_SIZE()

	ON_WM_ERASEBKGND()
	// Xu ly thong diep khi an mot phim bat ky tren ban phim 
	ON_WM_KEYDOWN()
	// Xu ly khi an vao node tien len tren keyboard
	ON_WM_LBUTTONDOWN()
	// Xu ly khi an vao node lui xuong tren keyboard
	ON_WM_LBUTTONUP()
	// Xu ly khi keo re chuot
	ON_WM_MOUSEMOVE()
	// Xu ly thong diep khi an vao bieu tuong x mau do cua cua so
	ON_WM_DESTROY()
	// Xu ly khi an vao item Print cua File tren menu bar
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	// Xu ly cac item thuoc menu Draw 3D
	ON_COMMAND(ID_DRAW3D_WRITECUBE,&COpenGLView::WriteCube)
	ON_COMMAND(ID_DRAW3D_WRITELCOSAHEDRON,&COpenGLView::WritelCosahedron)
	ON_COMMAND(ID_DRAW3D_WRITETEAPORT,&COpenGLView::WriteTeaport)
	ON_COMMAND(ID_DRAW3D_WRITETORUS,&COpenGLView::WriteTorus)

	// Xu ly cac item thuoc menu Draw2d
	ON_COMMAND(ID_DRAW2D_POINT,&COpenGLView::OnPoint)
	ON_COMMAND(ID_DRAW2D_LINES,&COpenGLView::OnLines)
	ON_COMMAND(ID_DRAW2D_POLYGON,&COpenGLView::OnPolygon)
	ON_COMMAND(ID_DRAW2D_TRIANGLE,&COpenGLView::OnTriangle)

	// Xu ly item OXY OXYZ thuoc menu Hepl

	ON_COMMAND(ID_HETOADO_DCOXY,&COpenGLView::OnOXY)
	ON_COMMAND(ID_HETOADO_DCOXYZ,&COpenGLView::OnOXYZ)


END_MESSAGE_MAP()


// Dinh nghia cac ham khoi tao va cac ham huy
COpenGLView::COpenGLView()
{
	// Cac bien nay la bien xac dinh toa do cua vat the
	// Ban dau phai gan value cho no
	 m_xAngle	=	0.0f ;
	 m_yAngle	=	0.0f ;
	 m_xPos		=	0.0f;
	 m_yPos		=	0.0f;
	 m_zoom		=	0.0f ;

	 m_bPoint	=	FALSE ;
	 m_bLine	=	FALSE ;
   m_bPolygon =	FALSE ;
   m_bTriangle=	FALSE ;

	 m_bOXY		= FALSE	  ;
	 m_bOXYZ	= FALSE   ;

	 m_bCube	=	FALSE ;
	 m_bTorus	=	FALSE ;
	 m_bTeaport	=	FALSE ;
	 m_blsahedron =	FALSE ;
	

}

// Dinh nghia ham huy cua Class COpenGLView
COpenGLView::~COpenGLView()
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

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// command nay cho phep OpenGL duoc su dung trong MFC
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

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{	
	if (CView::OnCreate(lpCreateStruct) == -1){
        return -1;
	}
	// Goi ham khoi tao trang thai dau tien cua  ung dung 
    InitializeOpenGL();
    return 0;
}



/******************************************************************************
* Function Name		: InitializeOpenGL
* Purpose			: Khoi tao trang thai dau tien cua ung dung
* Input Param		: Ko co
* Output Param		: return true hoac false
* Writer			: Damme88 - Developer phamtoanbonmat@gmail
* Time				: Sunday 27/05/2012.
*
******************************************************************************/

BOOL COpenGLView::InitializeOpenGL()
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
    ::glClearColor(0.0f,0.0f,0.0f,0.0f);

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

BOOL COpenGLView::SetupPixelFormat()
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

void COpenGLView::OnSize(UINT nType, int cx, int cy) 
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
	gluLookAt (1.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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

BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) 
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

void COpenGLView::OnDestroy() 
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


/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/

void COpenGLView::OnDraw(CDC* /*pDC*/)
{
	COpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc){
		return;
	}
	// Clear out the color & depth buffers
    ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	RenderScene();
	 // Tell OpenGL to flush its pipeline
    ::glFinish();
	 // Now Swap the buffers
    ::SwapBuffers( m_pDC->GetSafeHdc() );
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

void COpenGLView::RenderScene ()
{
	 glLoadIdentity();
	 // Do xa gan 
     glTranslatef(m_xPos, m_yPos, m_zoom-10.0f);
	 // Do nghieng
     glRotatef(m_xAngle+3.0f, 1.0f,0.0f,0.0f);
	   glRotatef(m_yAngle-3.0f, 0.0f,1.0f,0.0f);
      float a[3];
      a[0] = 1.0f/sqrt(2.0f);
      a[1] = a[0];
      a[2] = 5.0f;

	 if(m_bOXYZ == TRUE)
	 {	
	 // Truc OX co mau do 
		glColor3f(1.0f,0.0f,0.0f);
		glPointSize(3.0f);
		glBegin(GL_LINES);
			 glVertex3f(0.0f,0.0f,0.0f);
			 glVertex3f(3.0f,0.0f,0.0f);
		glEnd();
	// Truc OY co mau xanh la cay
		glColor3f(0.0f,1.0f,0.0f);
		glPointSize(3.0f);  
		glBegin(GL_LINES);
			 glVertex3f(0.0f,0.0f,0.0f);
			 glVertex3f(0.0f,3.0f,0.0f);
		glEnd();
	// Truc OZ co mau xanh nuoc bien 
		glColor3f(0.0f,0.0f,1.0f);
		glPointSize(3.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,3.0f);
		glEnd();
	 }

	 if(m_bOXY == TRUE)
	 {
	 // Truc OX co mau do 
		glColor3f(1.0f,0.0f,0.0f);
		glPointSize(3.0f);
		glBegin(GL_LINES);
			 glVertex2f(0.0f,0.0f);
			 glVertex2f(2.0f,0.0f);
		glEnd();
	// Truc OY co mau xanh la cay
		glColor3f(0.0f,1.0f,0.0f);
		glPointSize(3.0f);
		glBegin(GL_LINES);
			 glVertex2f(0.0f,0.0f);
			 glVertex2f(0.0f,2.0f);
		glEnd();	 
	 }
	 // Ve ra mot hinh lap phuong 
	 if(m_bCube == TRUE){
		 glColor3f(1.0f,0.0f,1.0f);
		 glutWireCube(1.0f);
	 }
	 if(m_bTeaport == TRUE){
		glColor3f(1.0f,0.0f,0.0f);
		glutWireTeapot(1.0f);
	 }
	 if(m_blsahedron == TRUE){
		 glColor3f(1.0f,0.0f,1.0f);
		glutWireIcosahedron();
	 }
	 if(m_bTorus == TRUE){
		glColor3f(1.0f,0.5f,0.0f);
		glutWireTorus(0.5f, 1.0f, 50, 50);	
	 }

	 // Draw 2D
	 if(m_bPoint == TRUE){
		 glColor3f(1.0f,0.0f,0.0f);
		 glPointSize(3.0f);
		 glBegin(GL_POINTS);
			 glVertex2f(0.0f,0.0f);
			 glVertex2f(1.0f,0.0f);
		 glEnd();
	 }
	 if(m_bLine == TRUE){
		 glColor3f(0.0f,1.0f,0.0f);
		 glPointSize(3.0f);
		 glBegin(GL_LINES);
			 glVertex2f(0.0f,0.0f);
			 glVertex2f(1.0f,0.0f);
		 glEnd();
	 }
	 if(m_bPolygon == TRUE){
	 	 glColor3f(1.0f,1.0f,0.5f);
		 glBegin(GL_POLYGON);
			glVertex2f(0.0f,0.0f);
			glVertex2f(1.0f,0.0f);
			glVertex2f(1.0f,1.0f);
			glVertex2f(0.0f,1.0f);
		 glEnd();
	 }
	 if(m_bTriangle == TRUE)
	 {
	 	 glColor3f(1.0f,0.0f,1.0f);
		 glBegin(GL_TRIANGLES);
			glVertex2f(1.0f,0.0f);
			glVertex2f(1.0f,0.5f);
			glVertex2f(0.5f,0.5f);
		glEnd();
	 }

	 if(theApp.m_bDrawData == TRUE)
	 {
		 long unsigned int i=0;
		 glColor3f(1.0f,0.0f,1.0f);
		 for (i=0;i<num;i=i+3)
		 {
		 glBegin(GL_POLYGON);
		 glVertex3f(GLPoint.Vertex[i][0],GLPoint.Vertex[i][1],GLPoint.Vertex[i][2]);
		 glVertex3f(GLPoint.Vertex[i+1][0],GLPoint.Vertex[i+1][1],GLPoint.Vertex[i+1][2]);
		 glVertex3f(GLPoint.Vertex[i+2][0],GLPoint.Vertex[i+2][1],GLPoint.Vertex[i+2][2]);
		 glEnd();
		 }
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
void COpenGLView::OnOXY()
{
	m_bOXY = TRUE ;
	m_bOXYZ=FALSE ;
	InvalidateRect(NULL,FALSE);
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
void COpenGLView::OnOXYZ()
{
	m_bOXYZ = TRUE ;
	m_bOXY=FALSE ;
	InvalidateRect(NULL,FALSE);
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
void COpenGLView::WriteCube()
{
	m_bCube		= TRUE	;
	m_bTorus	= FALSE ;	
	m_bTeaport	= FALSE ;
	m_blsahedron= FALSE ;
	InvalidateRect(NULL,FALSE);
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
void COpenGLView::WritelCosahedron()
{
	m_bCube		= FALSE	;
	m_bTorus	= FALSE ;	
	m_bTeaport	= FALSE ;
	m_blsahedron= TRUE ;
	InvalidateRect(NULL,FALSE);
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
void COpenGLView::WriteTeaport()
{
	m_bCube		= FALSE	;
	m_bTorus	= FALSE ;	
	m_bTeaport	= TRUE ;
	m_blsahedron= FALSE ;
	InvalidateRect(NULL,FALSE);
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
void COpenGLView::WriteTorus()
{
	m_bCube		= FALSE	;
	m_bTorus	= TRUE ;	
	m_bTeaport	= FALSE ;
	m_blsahedron= FALSE  ;
    InvalidateRect(NULL,FALSE);
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
void COpenGLView::OnPoint()
{
	m_bPoint = TRUE ;
	m_bLine	 = FALSE ;
	m_bPolygon	= FALSE ;
	m_bTriangle = FALSE ;
	InvalidateRect(NULL,FALSE);
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
void COpenGLView::OnLines()
{
	m_bPoint = FALSE ;
	m_bLine	 = TRUE ;
	m_bPolygon	= FALSE ;
	m_bTriangle = FALSE ;
	InvalidateRect(NULL,FALSE);
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
void COpenGLView::OnPolygon()
{
	m_bPoint = FALSE ;
	m_bLine	 = FALSE ;
	m_bPolygon	= TRUE ;
	m_bTriangle = FALSE ;
	InvalidateRect(NULL,FALSE);
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
void COpenGLView::OnTriangle()
{
	m_bPoint = FALSE ;
	m_bLine	 = FALSE ;
	m_bPolygon	= FALSE ;
	m_bTriangle = TRUE ;
	InvalidateRect(NULL,FALSE);
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
void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
        // TODO: Add your message handler code here and/or call default
        switch (nChar)
        {
            case VK_UP:        m_yPos = m_yPos + 0.1f;
                                          break;
            case VK_DOWN:      m_yPos = m_yPos - 0.1f;
                                          break;
            case VK_LEFT:      m_xPos = m_xPos - 0.1f;
                                          break;
            case VK_RIGHT:     m_xPos = m_xPos + 0.1f;
                                          break;
			case VK_NUMPAD1:    m_zoom = m_zoom + 0.2f;
										  break;
			case VK_NUMPAD2:    m_zoom = m_zoom - 0.2f;
										  break;
           default:                       break;
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

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
        // TODO: Add your message handler code here and/or call default
        m_MouseDownPoint=point;
        SetCapture();
        CView::OnLButtonDown(nFlags, point);
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

void COpenGLView::OnLButtonUp(UINT nFlags, CPoint point) 
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

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
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



/******************************************************************************
* Function Name		:
* Purpose			:
* Input Param		:
* Output Param		:
* Writer			:
* Time				:
*
******************************************************************************/

BOOL COpenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
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

void COpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
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

void COpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDoc* COpenGLView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDoc)));
	return (COpenGLDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLView message handlers
