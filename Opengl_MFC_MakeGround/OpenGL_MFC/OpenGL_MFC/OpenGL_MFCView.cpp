
// OpenGL_MFCView.cpp : implementation of the COpenGL_MFCView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL_MFC.h"
#endif

#include "OpenGL_MFCDoc.h"
#include "OpenGL_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define LENGTH_AXIS 100000
#define LENGTH_GROUND 500

// COpenGL_MFCView

IMPLEMENT_DYNCREATE(COpenGL_MFCView, CView)

BEGIN_MESSAGE_MAP(COpenGL_MFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGL_MFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
  ON_WM_RBUTTONDOWN()
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

// COpenGL_MFCView construction/destruction

COpenGL_MFCView::COpenGL_MFCView():
  x_position_(0.0f),
  y_position_(0.0f),
  angle_x_(-60.0f),
  angle_y_(0.0f),
  angle_z_(-135.0f),
  angle_x_ob_(-60.0f),
  angle_y_ob_(0.0f),
  angle_z_ob_(-135.0f)
{
	// TODO: add construction code here
  m_OrthoRangeLeft = -1.5f;
	m_OrthoRangeRight = 1.5f;
	m_OrthoRangeBottom = -1.5f;
	m_OrthoRangeTop = 1.5f;
	m_OrthoRangeNear = -20.0f;
	m_OrthoRangeFar = 100.0f;
  m_scaling = 0.25f;
	cx_ = 0;
	cy_ = 0;
	rendering_rate_ = 1.0f;
	m_theta = 60.0;
	m_phi = 60.0;
	pGround_ = new Ground3D(1000, 800, 0, 5);
	pHouse_ = new House(50.0, 50.0, 100.0);
}

COpenGL_MFCView::~COpenGL_MFCView()
{
	if (pGround_ != NULL) {
		delete pGround_;
		pGround_ = NULL;
	}
	if (pHouse_ != NULL) {
		delete pHouse_;
		pHouse_ = NULL;
	}
}

BOOL COpenGL_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
  //An OpenGL Window must be created with the following flags
  cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

int COpenGL_MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;
  // call InitializeOpengl
  InitializeOpenGL();
  return 0;
}

BOOL COpenGL_MFCView::InitializeOpenGL() {
 //Get a DC for Client Area;
  m_pDC = new CClientDC(this);
  if (m_pDC == NULL) {
    MessageBox(L"Error Obtaining DC");
    return FALSE;
  }
  if (!SetupPixelFormat())
    return FALSE;
  // Create Rendering Context
  m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
  if (m_hRC == 0 ){
    MessageBox(L"Error Creating RC");
    return FALSE;
  }
  //Make the RC Current
  if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE) {
    MessageBox(L"Error making RC Current");
    return FALSE;
  }
  //Specify Black as the clear color
  ::glClearColor(0.0f,0.0f,0.0f,0.0f);

  //Specify the back of the buffer as clear depth
  ::glClearDepth(1.0f);

  //Enable Depth Testing
  ::glEnable(GL_DEPTH_TEST);

	// Enable color tracking
	::glEnable(GL_COLOR_MATERIAL);
	::glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	::glShadeModel(GL_SMOOTH);
	// Setup lighting and material

  //listId_ = pHouse_->MakeHouse();
	OnLoadTexture();
}

BOOL COpenGL_MFCView::SetupPixelFormat() {
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
  if (m_nPixelFormat == 0) {
        return FALSE;
  }
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE) {
    return FALSE;
  }
  return TRUE;
}

void COpenGL_MFCView::OnSize(UINT nType, int cx, int cy) {
  CView::OnSize(nType, cx, cy);
	GLdouble aspect_ratio; 
	if ( 0 >= cx || 0 >= cy ) 
    return;
	cx_ = cx;
	cy_ = cy;

  // select the full client area
  ::glViewport(0, 0, cx, cy);

  ::glMatrixMode(GL_PROJECTION);
  ::glLoadIdentity();

  ::glMatrixMode(GL_MODELVIEW);
  ::glLoadIdentity();
}


void COpenGL_MFCView::SetViewFrustum() {
	double left_ = -(double)cx_ *0.5/ rendering_rate_;
	double right_ = (double)cx_ *0.5/ rendering_rate_;
	double top_ = (double)cy_ *0.5/ rendering_rate_;
	double bottom_ = -(double)cy_ *0.5/ rendering_rate_;

	double zfar = 1000/rendering_rate_;
	zfar = max(1000, rendering_rate_);
	glOrtho(left_, right_, bottom_, top_, -zfar, zfar);
}


void COpenGL_MFCView::ViewDirection() {
	Vector3D gradien;
	Vector3D cam_up;
	Vector3D temp;
	// unit vector oz
	Vector3D oz(0, 0, 1);

	// convert phi and theta to radian to speed is not fast
	double theta = m_theta*M_PI/180.0;     // theta_ is x rotation
	double phi = m_phi*M_PI/180.0; // theta_ is y rotation

	// At first time phi = 60 and theta = 60
	// oz replace position oy
	gradien.v[0] = cos(theta)*sin(phi);  // get eye_x when cam rotate
	gradien.v[1] = sin(theta)*sin(phi);  // get eye_y when cam rotate
	gradien.v[2] = cos(phi);           // get eye_z when cam rotate


	if((m_phi < 180 && m_phi > 0) || m_phi < -180) {
		temp = oz*gradien; // if  (oz->gradien) is same clock direction
		// direction of tem is top->bottom (- direction)
	} else {
		temp = gradien*oz; // else : direction of tem is bottom ->top (+ direction)
	}

	if(temp.abs() < 0.01) {
		cam_up.v[0] = - cos(phi);
		cam_up.v[1] =  - sin(phi);
		cam_up.v[2] = 0.0;
	} else {
		cam_up = gradien*temp;
	}
	cam_up = cam_up.Unit();
	gluLookAt(gradien.v[0], gradien.v[1], gradien.v[2],
		        0, 0, 0,
		        cam_up.v[0], cam_up.v[1], cam_up.v[2]);
}


BOOL COpenGL_MFCView::OnEraseBkgnd(CDC* pDC) {
    // TODO: Add your message handler code here and/or call default
    //comment out the original call
    //return CView::OnEraseBkgnd(pDC);
    //Tell Windows not to erase the background
    return TRUE;
}


// COpenGL_MFCView drawing

void COpenGL_MFCView::OnDraw(CDC* /*pDC*/)
{
	COpenGL_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
  // Clear out the color & depth buffers
  ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// TODO: add draw code for native data here
  RenderScene();
	// Tell OpenGL to flush its pipeline
  ::glFinish();
	// Now Swap the buffers
  ::SwapBuffers( m_pDC->GetSafeHdc() );
	// TODO: add draw code for native data here
	// TODO: add draw code for native data here
}


void COpenGL_MFCView::OnDestroy() {
  CView::OnDestroy();
  // TODO: Add your message handler code here
	//Make the RC non-current
  if(::wglMakeCurrent (0,0) == FALSE) 
    MessageBox(_T("Could not make RC non-current"));
	//Delete the rendering context
  if(::wglDeleteContext (m_hRC)==FALSE) 
    MessageBox(_T("Could not delete RC"));
  //Delete the DC
  if(m_pDC)
    delete m_pDC;
  //Set it to NULL
  m_pDC = NULL;
}

// COpenGL_MFCView printing
void COpenGL_MFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}
#ifdef USE_FUNCTION_PRINT
BOOL COpenGL_MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGL_MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGL_MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

#endif //USE_FUNCTION_PRINT

void COpenGL_MFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGL_MFCView diagnostics

#ifdef _DEBUG
void COpenGL_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGL_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGL_MFCDoc* COpenGL_MFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGL_MFCDoc)));
	return (COpenGL_MFCDoc*)m_pDocument;
}
#endif //_DEBUG

// COpenGL_MFCView message handlers

/*************************************************** new implement************/

void COpenGL_MFCView::OnRButtonUp(UINT nFlags, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);  // Create menu cut copy paste
  mouse_down_point_ = CPoint(0, 0);
  ReleaseCapture();
  //CView::OnLButtonUp(nFlags, point);
}

void COpenGL_MFCView::OnRButtonDown(UINT nFlags, CPoint point) {
   mouse_down_point_ = point;
  SetCapture();
  //CView::OnLButtonDown(nFlags, point);
}

void COpenGL_MFCView::OnLButtonDown(UINT nFlags, CPoint point) {
  //TODO
}

void COpenGL_MFCView::OnLButtonUp(UINT nFlags, CPoint point) {
  //TODO
}

void COpenGL_MFCView::OnMouseMove(UINT nFlags, CPoint point) {
  if (GetCapture() == this) {
		int deltax = point.x - mouse_down_point_.x;
		// convert deltax into o
		float anglex = deltax*180.0/cx_;
		// phi is angle of camera, it is not angle of model
		// when mouse move from left to right so camera move from right to left
		m_theta -= anglex;
		if(m_theta > 360) {
			m_theta = m_theta - 360;
		} else if( m_theta < - 360) {
			m_theta = m_theta + 360;
		}

		int deltay = (double)(point.y - mouse_down_point_.y);
		// convert delta into o
		float angley = deltay*180.0/cy_;
		m_phi -= angley;
		if(m_phi > 360) {
			m_phi = m_phi - 360;
		} else if( m_phi < - 360) {
			m_phi = m_phi + 360;
		}
			mouse_down_point_ = point;
	}
	InvalidateRect(NULL,FALSE);
	CView::OnMouseMove(nFlags, point);
}

BOOL COpenGL_MFCView::OnMouseWheel(UINT nFlags, short zDetal, CPoint point) {
  BOOL ret = FALSE ;
	if (zDetal >= 0) {
		rendering_rate_ *= 1.50f;
		ret = TRUE ;
	} else {
		rendering_rate_ /= 1.5f;
		ret = TRUE ;
	}
  InvalidateRect(NULL,FALSE);
  //Set the mouse point
  mouse_down_point_ = point;
  CWnd::OnMouseWheel(nFlags, zDetal, point);
  return  ret;
}

void COpenGL_MFCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar) {
	case VK_UP:
		y_position_ += 15.0f;
		InvalidateRect(NULL,FALSE);
		break;
	case VK_DOWN:
		y_position_ -= 15.0f;
		InvalidateRect(NULL,FALSE);
		break;
	case VK_LEFT:
		x_position_ -= 15.0f;
		InvalidateRect(NULL,FALSE);
		break;
	case VK_RIGHT:
		x_position_ += 15.0f;
		InvalidateRect(NULL,FALSE);
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void COpenGL_MFCView::RenderScene () {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	SetViewFrustum();

	glTranslatef(x_position_, y_position_, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ViewDirection();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0);
	DrawCoordinate();
	glPopMatrix();


	for (int i = 0; i < 8; i ++) {
		glPushMatrix();
		//OnEnableLight();
		glTranslatef(-400.0 + i*80, 0.0, pHouse_->GetHeigh()/2.0);
		//glColor3f(1.0, 1.0, 0.0);
		pHouse_->MakeHouse();
		glPopMatrix();
	}
	//OnDisableLight();
	DrawGround();
}


void COpenGL_MFCView::DrawGround() {
	pGround_->MakeGround3D();
}

void COpenGL_MFCView::OnLoadTexture() {
	//Create Texture Names
	glGenTextures(2, m_texture);
	LoadTexture(L"TAB.bmp",  0);
	LoadTexture(L"hs22.bmp", 1);
	if (pGround_)
		pGround_->SetTextureData(m_texture[0]);
	if (pHouse_)
		pHouse_->SetTexture(m_texture[1]);
}

void COpenGL_MFCView::LoadTexture(CString file_name, int text_name )
{
	// load texture 
	AUX_RGBImageRec *texture;
	int length = file_name.GetLength();
	LPWSTR lpstr = LPWSTR( file_name.GetBuffer(length));
	file_name.ReleaseBuffer();
	texture = auxDIBImageLoad(lpstr);
	if (!texture) {
		AfxMessageBox(L"Picture cout not be loaded");
		exit(1);
	}

	glBindTexture(GL_TEXTURE_2D, m_texture[text_name]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture->sizeX,
		texture->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
		texture->data);
}


void COpenGL_MFCView::DrawCoordinate() {
  // Draw coordinate
  glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex3f(LENGTH_AXIS, 0.0f, 0.0f);
  glVertex3f(-1*LENGTH_AXIS, 0.0f, 0.0f);
  glEnd();

  glColor3f(0.0f, 1.0f, 0.0f);
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex3f(0.0f, LENGTH_AXIS, 0.0f);
  glVertex3f(0.0f, -1*LENGTH_AXIS, 0.0f);
  glEnd();

  glColor3f(0.0f, 0.0f, 1.0f);
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex3f(0.0f, 0.0, LENGTH_AXIS);
  glVertex3f(0.0f, 0.0f, -1*LENGTH_AXIS);
  glEnd();
}

void COpenGL_MFCView::OnEnableLight() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE); 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DIFFUSE);

	glEnable(GL_POINT_SMOOTH);
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	// glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	GLfloat m_SceneAmbient1[]  = {0.2f,0.2f,0.2f,1.0f};
	GLfloat m_SceneDiffuse1[]  = {0.7f,0.7f,0.7f,1.0f};
	GLfloat m_SceneSpecular1[] = {0.2f,0.2f,0.2f,1.0f};
	//GLfloat m_ScenePosition1[] = {gradient_.v[0], gradient_.v[1], gradient_.v[2],0.0f};
	GLfloat m_ScenePosition1[] = {0.0f, 0.5f, -1.0f,0.0f};
	GLfloat m_SceneDirection1[]= {0.0f,0.0f,1.0f,0.0f};
	GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; 
	GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
	GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0};
	GLfloat mShininess[] = {60}; //set the shininess of the 

	glLightfv(GL_LIGHT0, GL_AMBIENT, m_SceneAmbient1); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_SceneDiffuse1); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_SceneSpecular1); 
	//	glLightfv(GL_LIGHT0, GL_POSITION, m_ScenePosition1);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,20.0f);

	GLfloat material_ambient[] = {1.0f ,1.0f , 1.0f ,1.0f};
	GLfloat material_specular[] = {1.0f ,1.0f ,1.0f ,1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);

	glMaterialfv(GL_FRONT, GL_SHININESS, mShininess);
}

void COpenGL_MFCView::OnDisableLight() {
  glDisable(GL_LIGHTING);
  glDisable(GL_CULL_FACE);
}

int COpenGL_MFCView::MakeObject() {
  GLuint id = glGenLists(1);  // make list to use CallList
  glNewList(id, GL_COMPILE);
  // Function draw object is called at here
  glutSolidCube(100.0);
  glEndList();
  return id;
}