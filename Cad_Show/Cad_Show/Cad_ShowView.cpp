
// Cad_ShowView.cpp : implementation of the CCad_ShowView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Cad_Show.h"
#endif

#include "Cad_ShowDoc.h"
#include "Cad_ShowView.h"
#include "Cad_Point.h"
#include "MainFrm.h"
#include "SampleOpengl.h"
#include "BasicConverts.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define M_PI 3.14

extern Triangle GLPoint ;
// CCad_ShowView

IMPLEMENT_DYNCREATE(CCad_ShowView, CView)

BEGIN_MESSAGE_MAP(CCad_ShowView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCad_ShowView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
  ON_WM_CREATE()
	ON_WM_SIZE()
  ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_RBUTTONUP()
  ON_WM_MOUSEWHEEL()
  ON_WM_MOUSEMOVE()
  ON_WM_MBUTTONDOWN()
  ON_WM_MBUTTONUP()
  ON_WM_KEYDOWN()
  ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
  ON_COMMAND_RANGE(ID_VIEW_HANDLE_START, ID_VIEW_ZOOM_OUT, OnHandleViewButton)
  ON_COMMAND_RANGE(ID_VIEW_HANDLE_MOVE_START, ID_VIEW_MOVE_RIGHT, OnHandleMoveButton)
  ON_COMMAND_RANGE(ID_VIEW_HANDLE_ROTATE_START, ID_ROTATE_RIGHT, OnHandleRotateButton)
  ON_COMMAND(ID_SHOW_BIG_COORDINATE, EnableShowBigCoordinate)
  ON_UPDATE_COMMAND_UI(ID_SHOW_BIG_COORDINATE, SetCheckBigCoordinate)
  ON_COMMAND(ID_RESET_CAD, OnHandleResetCad)
  ON_COMMAND(ID_EDIT_DELETE, DeleteCad)
	ON_COMMAND(ID_VIEW_FULL_SCREEN, ViewFullscreen)

END_MESSAGE_MAP()

// CCad_ShowView construction/destruction

CCad_ShowView::CCad_ShowView() :
  angle_x_(0.0),
  angle_y_(0.0),
  angle_z_(0.0),
  m_scaling(1.0),
  angle_x_cad_(0.0),
  angle_y_cad_(0.0),
  angle_z_cad_(0.0),
  angle_x_big_cdn_(0.0),
  angle_y_big_cdn_(0.0),
  angle_z_big_cdn_(0.0),
  x_position_(0.0),
  y_position_(0.0),
  m_nFontOffset(0),
  rotate_left_(FALSE),
  rotate_righit_(FALSE),
  middle_down_(FALSE),
  mode_cad_(0),
  red_color_(0.0f),
  green_color_(0.0f),
  blue_color_(0.0f),
  speed_rotate_(0.0f),
  is_check_rotate_(0.0),
  is_rot_x_(false),
  is_rot_y_(false),
  is_rot_z_(false),
  eye_x_ (0.0f),
  eye_y_(0.0f),
  eye_z_(0.0f),
  cen_x_(0.0f),
  cen_y_(0.0f),
  cen_z_(0.0f),
  up_x_(0.0f),
  up_y_(0.0f),
  up_z_(1.0f),
  lx_(0.0f),
  ly_(0.0f),
  lz_(0.0),
	xPos_(0.0),
	yPos_(0.0),
	zPos_(0.0),
  enable_big_coordinate_(false),
  is_check_coordiante_button_(false)
{
  rendering_rate_ = 1.0f;
  theta_ = 135.0f;
  phi_ = 45.0f;
	is_draw_sample_ = false;
  //infor_view_ = NULL;

	pAmbien_ = new GLfloat[4];
	pAmbien_[0] = 0.5f;
	pAmbien_[1] = 0.5f;
	pAmbien_[2] = 0.5f;
	pAmbien_[3] = 1.0f;

	pSpecular_ = new GLfloat[4];
	pSpecular_[0] = 0.5f;
	pSpecular_[1] = 0.5f;
	pSpecular_[2] = 0.5f;
	pSpecular_[3] = 1.0f;

	pDiff_ = new GLfloat[4];
	pDiff_[0] = 0.5f;
	pDiff_[1] = 0.5f;
	pDiff_[2] = 0.5f;
	pDiff_[3] = 1.0f;

	shininess_ = 50;
  is_create_terrain_ = false;
  p_terrain_ = NULL;
}

CCad_ShowView::~CCad_ShowView()
{
	if (pAmbien_ != NULL) {
		delete [] pAmbien_;
		pAmbien_ = NULL;
	}

	if (pSpecular_ != NULL) {
		delete [] pSpecular_;
		pSpecular_ = NULL;
	}
	if (pDiff_ != NULL) {
		delete [] pDiff_;
		pDiff_ = NULL;
	}
}

BOOL CCad_ShowView::PreCreateWindow(CREATESTRUCT& cs)
{
  //An OpenGL Window must be created with the following flags
  cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

int CCad_ShowView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;
  // call InitializeOpengl
  InitializeOpenGL();
  BuildAxisesList();
  return 0;
}

BOOL CCad_ShowView::InitializeOpenGL() {
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
  ::glClearColor(0.0, 0.0f, 0.0f, 0.0f);

  //Specify the back of the buffer as clear depth
  ::glClearDepth(1.0f);

  //Enable Depth Testing
  ::glEnable(GL_DEPTH_TEST);
  CreateOpenGLFont();

  //Load the model
  p_md2_model_ = MD2Model::load("tallguy.md2");
  if (p_md2_model_ != NULL) {
    p_md2_model_->setAnimation("run");
  }
  return true;
}

void CCad_ShowView::IniterTerrain()
{
  // Create terrain
  char* file_name = Converts::CStringToChar(file_img_terrain_);
  p_terrain_ = LoadTerrain(file_name, height_terrain_);
}

BOOL CCad_ShowView::SetupPixelFormat() {
  int nPixelFormat;
  CDC *dc = GetDC();
  DWORD dwflag;
  dwflag = PFD_DRAW_TO_WINDOW |           // Draw to window (not to bitmap)
    PFD_SUPPORT_OPENGL |           // Support OpenGL calls in window
    PFD_GENERIC_ACCELERATED|
    /* PFD_GENERIC_FORMAT|*/
    /*PFD_DEPTH_DONTCARE|*/
    PFD_DOUBLEBUFFER,              // Double-buffered mode
    PFD_TYPE_RGBA;                 // RGBA color mode

  PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), // Size of this structure
    1,                             // Version of this structure
    dwflag,
    32,                            // Want 32-bit color
    0,0,0,0,0,0,0,0,               // Ignore color bits setting
    32,                            // Accum bits
    0,0,0,0,                       // Ignore accum bits setting
    32,                            // Size of depth buffer
    0,                             // Not used here
    0,                             // Not used here
    PFD_MAIN_PLANE,                // Main Drawing Layer
    0,                             // Not used here
    0,0,0 };                       // Not used here

    // Choose a pixel format that best matches that described in pfd
    if( 0 == ( nPixelFormat = ::ChoosePixelFormat(dc->m_hDC, &pfd) ) ) {
      //CommonUtils::Alert(IDS_CHOOSEPIXELFORMATFAILED);
      AfxMessageBox(L"Choose pixel formal is failed");
      return false;
    }

#ifdef _DEBUG
    bool accel1 = false;
    bool accel2 = false;
    if(pfd.dwFlags & PFD_GENERIC_FORMAT){
      accel1 = true;
    }
    if(pfd.dwFlags & PFD_GENERIC_ACCELERATED){
      accel2 = true;
    }
    if(pfd.dwFlags & PFD_DEPTH_DONTCARE){
      accel1 = true;
    }
#endif

    // Set the pixel format for the device context
    if( TRUE != ::SetPixelFormat(dc->m_hDC, nPixelFormat, &pfd) ) {
      //CommonUtils::Alert(IDS_SETUPPIXELFORMATFAILED);
      AfxMessageBox(L"Choose pixel formal is failed");
      return false;
    }
    return true;
}

void CCad_ShowView::OnSize(UINT nType, int cx, int cy) {
  CView::OnSize(nType, cx, cy);
	GLdouble aspect_ratio;
	if ( 0 >= cx || 0 >= cy ) 
    return;

  //glViewport allow to select the full client area of window for opengl
  ::glViewport(0, 0, cx, cy);

  // compute the aspect ratio
  // this will keep all dimension scales equal
  aspect_ratio = (GLdouble)cx/(GLdouble)cy;
  cx_ = cx;
  cy_ = cy;

  // select the projection matrix and clear it
  ::glMatrixMode(GL_PROJECTION);
  ::glLoadIdentity();
  // select the viewing volume
  //::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);
  SetViewFrustum();
  // switch back to the model view matrix and clear it
  ::glMatrixMode(GL_MODELVIEW);
  ::glLoadIdentity();
}


void CCad_ShowView::SetViewFrustum() {
  double left_ = -(double)cx_ *0.5/ rendering_rate_;
  double right_ = (double)cx_ *0.5/ rendering_rate_;
  double top_ = (double)cy_ *0.5/ rendering_rate_;
  double bottom_ = -(double)cy_ *0.5/ rendering_rate_;

  double zfar = 20000/rendering_rate_;
  zfar = max(20000, rendering_rate_);
  glOrtho(left_, right_, bottom_, top_, -zfar, zfar);
}

BOOL CCad_ShowView::OnEraseBkgnd(CDC* pDC) {
    // TODO: Add your message handler code here and/or call default
    //comment out the original call
    //return CView::OnEraseBkgnd(pDC);
    //Tell Windows not to erase the background
    return TRUE;
}


// CCad_ShowView drawing

void CCad_ShowView::OnDraw(CDC* /*pDC*/)
{
	CCad_ShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
  // Clear out the color & depth buffers
  ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	 glClearColor(red_color_, green_color_, blue_color_, 1.0f);
	
	// TODO: add draw code for native data here
  RenderScene();
	// Tell OpenGL to flush its pipeline
   UpdateInfoToOutput();
  ::glFinish();
	// Now Swap the buffers
  ::SwapBuffers( m_pDC->GetSafeHdc() );
	// TODO: add draw code for native data here
	// TODO: add draw code for native data here
}

// CCad_ShowView printing
void CCad_ShowView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCad_ShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCad_ShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCad_ShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCad_ShowView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCad_ShowView diagnostics

#ifdef _DEBUG
void CCad_ShowView::AssertValid() const
{
	CView::AssertValid();
}

void CCad_ShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCad_ShowDoc* CCad_ShowView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCad_ShowDoc)));
	return (CCad_ShowDoc*)m_pDocument;
}
#endif //_DEBUG



void CCad_ShowView::OnMouseMove(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  // Check if we have captured the mouse
  CRect rect;
  GetClientRect(rect);
  CView::OnMouseMove(nFlags, point);
  if (GetCapture() == this) {
    //Increment the object rotation angles
#if 0
    angle_x_ += (point.y - mouse_down_point_.y)/3.6;
    angle_z_ += (point.x - mouse_down_point_.x)/3.6;

    angle_x_cad_ += (point.y - mouse_down_point_.y)/3.6;
    angle_z_cad_ += (point.x - mouse_down_point_.x)/3.6;

    angle_x_big_cdn_ += (point.y - mouse_down_point_.y)/3.6;
    angle_z_big_cdn_ += (point.x - mouse_down_point_.x)/3.6;
#endif
    CalculateRotatefAngle(point);
  }
  mouse_down_point_ = point;
  if (middle_down_) {
    xPos_ -= (float)(middle_down_pos_.x -point.x); 
    yPos_ += (float)(middle_down_pos_.y -point.y);
    middle_down_pos_.x = point.x;
    middle_down_pos_.y = point.y;
    SendMessage(WM_PAINT, 0, 0);
    return;
  }
}

void CCad_ShowView::CalculateRotatefAngle(CPoint point) {
  int ix = point.x - mouse_down_point_.x;
  int iy = point.y - mouse_down_point_.y;
  float fAngle;
  if(abs(ix) > abs(iy)) {
    fAngle = ix * 180.0f / cx_;
    theta_ += fAngle;
    if (theta_ > 360)
			theta_ -= 360;
    if (theta_ < 360);
			theta_ += 360;
  } else {
    fAngle = iy * 180.0f / cy_;
    phi_ += fAngle;
    if(phi_ > 360)  
			phi_ -= 360;
    if(phi_ < -360) 
			phi_ += 360;
  }
  ::glMatrixMode( GL_MODELVIEW );
  ::glLoadIdentity();
}



BOOL CCad_ShowView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
  BOOL ret = FALSE ;
  if (zDelta >=0) {
    m_scaling *= 1.25f;
    ret = TRUE ;
  }
  else {
    m_scaling /= 1.25f;
    ret = TRUE ;
  }
  InvalidateRect(NULL,FALSE);
  //Set the mouse point
  mouse_down_point_ = point;
  CWnd::OnMouseWheel(nFlags, zDelta, point);
  return ret;
}

void CCad_ShowView::OnRButtonDown(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  mouse_down_point_ = point;
  SetCapture();
  CView::OnLButtonDown(nFlags, point);
 
}

void CCad_ShowView::OnRButtonUp(UINT nFlags, CPoint point)  {
  // TODO: Add your message handler code here and/or call default
  mouse_down_point_ = CPoint(0, 0);
  ReleaseCapture();
  CView::OnLButtonUp(nFlags, point);
}

void CCad_ShowView::OnMButtonDown(UINT nFlags, CPoint point) {
  CView::OnMButtonDown(nFlags, point);
  SendMessage(WM_PAINT, 0, 0);

  middle_down_= TRUE;
  middle_down_pos_= point;
	cursor_ = middle_down_cursor_;
}

void CCad_ShowView::OnMButtonUp(UINT nFlags, CPoint point) {
  CView::OnMButtonUp(nFlags, point);
  ReleaseCapture();
  middle_down_ = FALSE;
}

void CCad_ShowView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
        // TODO: Add your message handler code here and/or call default
        switch (nChar)
        {
            case VK_UP:        yPos_ = yPos_ + 10.0f;
                                          break;
            case VK_DOWN:      yPos_ = yPos_ - 10.0f;
                                          break;
            case VK_LEFT:      xPos_ = xPos_ - 10.0f;
                                          break;
            case VK_RIGHT:     xPos_ = xPos_ + 10.0f;
                                          break;
						case VK_DELETE: {
							DeleteCad();
							InvalidateRect(NULL,FALSE);
							break;
						}
						case VK_ESCAPE : {
              middle_down_ = FALSE;
              ReleaseCapture();
							CMainFrame * main_frame = static_cast<CMainFrame*>(AfxGetMainWnd());
							main_frame->HandleEscape();
						}
        } 
        InvalidateRect(NULL,FALSE);
        CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCad_ShowView::RenderScene () {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glLoadIdentity();

	glTranslatef(xPos_, yPos_, zPos_);

	gluLookAt(cen_x_ + sin((theta_*M_PI)/180.0)*cos((phi_*M_PI)/180.0),
		cen_y_ + cos((theta_*M_PI)/180.0)*cos((phi_*M_PI)/180.0),
		cen_z_ + sin((phi_*M_PI)/180.0),
		cen_x_, cen_y_, cen_z_,
		up_x_,
		up_y_,
		up_z_*cos(phi_*M_PI/180.0f));
  // clear AntiAliasing
  glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  RenderSmallCoordinate();
 
  glPushMatrix();
  glTranslatef(x_position_, 0.0f, y_position_);
  glScalef(m_scaling, m_scaling, m_scaling);

  glRotatef(angle_x_big_cdn_, 1.0f, 0.0f, 0.0f);
  glRotatef(angle_y_big_cdn_, 0.0f, 1.0f, 0.0f);
  glRotatef(angle_z_big_cdn_, 0.0f, 0.0f, 1.0f);
  OnDrawCoordinateBig();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(x_position_, 0.0, y_position_);
  glScalef(m_scaling, m_scaling, m_scaling);
  glRotatef(angle_x_cad_, 1.0f, 0.0f, 0.0f);
	glRotatef(angle_y_cad_, 0.0f, 1.0f, 0.0f);
  glRotatef(angle_z_cad_, 0.0f, 0.0f, 1.0f);
  SetUpLight();
  DrawCad();
  DrawTerrain();
  //DrawModelMd2();
	// Draw Sample
	DrawSampleOpengl();
	// Draw Obj
  glPushMatrix();
  glTranslatef(0.0, 0.0, -20.0);
  glScalef(5.0f, 5.0f, 5.0f);
  glCallList(theApp.GetObjList());

  glTranslatef(5.0, 0.0, 0.0);
  //glScalef(10.0f, 10.0f, 10.0f);
  glCallList(theApp.GetObjList());

  glTranslatef(10.0, 0.0, 0.0);
  //glScalef(10.0f, 10.0f, 10.0f);
  glCallList(theApp.GetObjList());

  glPopMatrix();


  DisableSetupLigting();
  glPopMatrix();
}

void CCad_ShowView::UpdateInfoToOutput() {
	if (theta_ > 360.0f)
		theta_ -= 360.0f;
	if (theta_ < -360.0f)
	  theta_ += 360.0f;

	if (phi_ > 360.0f)
		phi_ -= 360.0f;
	if (phi_ < -360.0f)
	  phi_ += 360.0f;
#ifdef NO_USE_INFOBAR
  infor_view_->OnUpdateAngleAxis(theta_, phi_, 0.0);
	infor_view_->OnUpdateValueCam(cen_x_ + sin((theta_*M_PI)/180.0)*cos((phi_*M_PI)/180.0),
																cen_y_ + cos((theta_*M_PI)/180.0)*cos((phi_*M_PI)/180.0),
																cen_z_ + sin((phi_*M_PI)/180.0),
																cen_x_, cen_y_, cen_z_,
																up_x_,
																up_y_,
																up_z_*cos(phi_*M_PI/180.0f));
#endif
}

void CCad_ShowView::DrawCad() {
   if(theApp.GetStateDrawStl() == TRUE)
	 {
		 glColor3f(1.0f, 1.0f, 1.0f);
     if (mode_cad_ == POINT_MODE_CAD) {
       glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
       glPointSize(4.0f);
       DisableSetupLigting();
     } else if (mode_cad_ == WIRE_FRAME_MODE_CAD){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.0f);
        DisableSetupLigting();
     }
     else {
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     }

     long numbers = theApp.GetNumberOfPoint();
     for (unsigned long i = 0; i < numbers; i = i+3) 
     {
       glBegin(GL_POLYGON);
       glNormal3f(theApp.GetNormalVector()[i/3][0], theApp.GetNormalVector()[i/3][2],  theApp.GetNormalVector()[i/3][1]); 
       glVertex3f(theApp.GetTrianglePoint()->Vertex[i][0], theApp.GetTrianglePoint()->Vertex[i][1], theApp.GetTrianglePoint()->Vertex[i][2]);
		   glVertex3f(theApp.GetTrianglePoint()->Vertex[i+1][0], theApp.GetTrianglePoint()->Vertex[i+1][1], theApp.GetTrianglePoint()->Vertex[i+1][2]);
		   glVertex3f(theApp.GetTrianglePoint()->Vertex[i+2][0], theApp.GetTrianglePoint()->Vertex[i+2][1], theApp.GetTrianglePoint()->Vertex[i+2][2]);
		   glEnd();
		 }
	 }
}

void CCad_ShowView::DrawModelMd2()
{
  if (p_md2_model_ != NULL) 
  {
    glEnable(GL_TEXTURE_2D);
    double z_value = 40.0;
    if (p_terrain_)
    {
       z_value += p_terrain_->get_height(100, 100 + 1);
    }

    glPushMatrix();
    glTranslatef(100.0, 100.0, z_value);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(2.0f, 2.0f, 2.0f);
    p_md2_model_->draw();
    glPopMatrix();
  }
  glDisable(GL_TEXTURE_2D);

  //Advance the animation
  if (p_md2_model_ != NULL) {
    p_md2_model_->advance(0.0025f);
  }
}
void CCad_ShowView::DrawTerrain()
{
  if (is_create_terrain_)
  {
    glPushMatrix();
    glTranslatef(-(float)(p_terrain_->get_width() - 1) / 2, -(float)(p_terrain_->get_length() - 1) / 2, 0.0f);
    glColor3f(0.3f, 0.4f, 0.2f);
    int length = p_terrain_->get_length();
    int with = p_terrain_->get_width();
    for(int z = 0; z < length - 1; z++) 
    {

      if (mode_cad_ == WIRE_FRAME_MODE_CAD)
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }
      else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }

      glBegin(GL_TRIANGLE_STRIP);
      for(int x = 0; x < with; x++) 
      {
        Vector3d normal = p_terrain_->get_normal(x, z);
        glNormal3f(normal[0], normal[2], normal[1]);
        glVertex3f(x, z, p_terrain_->get_height(x, z));

        normal = p_terrain_->get_normal(x, z + 1);
        glNormal3f(normal[0], normal[2], normal[1]);
        glVertex3f(x, z + 1, p_terrain_->get_height(x, z + 1));
      }
      glEnd();
    }
    glPopMatrix();
  }
}

void CCad_ShowView::DeleteCad() {
	is_draw_sample_ = false;
  theApp.SetStatusDrawCad(FALSE);
  theApp.FreePoint();
  InvalidateRect(NULL, FALSE);
}

// draw label "X" "Y" "Z"
void CCad_ShowView::CreateOpenGLFont() {
  CFont m_font;
  m_font.CreateFont( -16,               // Height Of Font 
                       0,               // Width Of Font 
                       0,               // Angle Of Escapement 
                       0,               // Orientation Angle 
                       FW_NORMAL,       // Font Weight 
                       FALSE,           // Italic 
                       FALSE,           // Underline 
                       FALSE,           // Strikeout 
                       ANSI_CHARSET,              // Character Set Identifier 
                       OUT_TT_PRECIS,             // Output Precision 
                       CLIP_DEFAULT_PRECIS,       // Clipping Precision 
                       DEFAULT_QUALITY,           // Output Quality 
                       FF_DONTCARE|DEFAULT_PITCH, // Family And Pitch 
                       _T("Arial"));
  CFont* m_pOldFont = GetDC()->SelectObject(&m_font); 
  m_editCLTip = glGenLists(256);
  m_textTip = glGenLists(256);
  wglUseFontBitmaps(m_pDC->m_hDC, 0, 255, m_editCLTip);
  wglUseFontBitmaps(m_pDC->m_hDC, 0, 255, m_textTip);
  GetDC()->SelectObject(m_pOldFont); 
} 

void CCad_ShowView::DrawStringAt(double x, double y, double z, char* s) {
  size_t length = strlen(s);
  if (length > 0 && s) {
    glRasterPos3d(x, y , z);
    glListBase(m_textTip);
    glCallLists(length, GL_UNSIGNED_BYTE, (const GLvoid*)s);
  }
}


void CCad_ShowView::SetUpLight() {
  glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LESS);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pAmbien_);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pSpecular_);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pDiff_);
  glMateriali(GL_FRONT, GL_SHININESS, shininess_);

  GLfloat position[] = {10000.0f, 10000.0f, 50000.0f, 1.0f};
  GLfloat global_ambient[] = { 0.8f, 0.8f, 0.8f, 1 };

  float MatAmbientBack[]  = {0.1f, 0.2f, 0.0f, 1.0f};
  glMaterialfv(GL_BACK, GL_AMBIENT, MatAmbientBack);


 	glEnable(GL_LIGHTING);
 	glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE); //this is good command for light

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#if 0
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); 
  /********clear AntiAliasing - Back Face*******************/
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  /************clear AntiAliasing*Back Face ****************/
#endif
}


void CCad_ShowView::DisableSetupLigting() {
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glDisable(GL_POINT_SMOOTH);
  glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
}

void CCad_ShowView::RenderSmallCoordinate() {

  CRect rect;
  GetClientRect(rect);
  CPoint pt;
  pt.x = 66;
  pt.y = rect.Height() - 66;

  GLdouble model_view[16];
  GLdouble projection[16];
  GLint viewport[4];
  glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetIntegerv(GL_VIEWPORT, viewport);

  GLfloat winx = (float)pt.x;
  GLfloat winy = (float)viewport[3] - (float)pt.y;
  GLfloat winz = 0.01;
  //glReadPixels(pt.x, int(winy), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);

  GLdouble glpt[3] = {0.0, 0.0, 0.0};
  gluUnProject(winx, winy, winz,
               model_view, projection, viewport,
               glpt, glpt + 1, glpt + 2);
  glPushMatrix();
  glTranslatef(glpt[0], glpt[1], glpt[2]);
  glRotatef(angle_x_, 1.0f, 0.0f, 0.0f); 
  glRotatef(angle_y_, 0.0f, 1.0f, 0.0f);
  glRotatef(angle_z_, 0.0f, 0.0f, 1.0f);
  glCallList(m_nAxisesList);
  glPopMatrix();
}

void CCad_ShowView::OnDrawCoordinateBig() {
  if (enable_big_coordinate_ == true) {
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0*VALUE_AXIS, 0.0f, 0.0f);
    glVertex3f(VALUE_AXIS, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, VALUE_AXIS, 0.0f);
    glVertex3f(0.0f, -1.0*VALUE_AXIS, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, VALUE_AXIS);
    glVertex3f(0.0f, 0.0f, -1*VALUE_AXIS);
    glEnd();
  }
}

void CCad_ShowView::EnableShowBigCoordinate() {
  if (is_check_coordiante_button_ == false) {
    enable_big_coordinate_ = true;
    is_check_coordiante_button_ = true;
  } else {
    enable_big_coordinate_ = false;
    is_check_coordiante_button_ = false;
  }
  InvalidateRect(NULL, FALSE);
}

void CCad_ShowView::SetCheckBigCoordinate(CCmdUI* cmd) {
  if (is_check_coordiante_button_ == false) {
    cmd->SetCheck(false);
  } else {
    cmd->SetCheck(true);
  }
  InvalidateRect(NULL, FALSE);
}

void CCad_ShowView::BuildAxisesList()
{
  m_nAxisesList = glGenLists(1);        // gen list
	glNewList(m_nAxisesList, GL_COMPILE);

	glLineWidth(2.0f);          // make OX axis
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(30.0, 0.0, 0.0);

	glColor3ub(0, 255, 0);      // make OY axis
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 30.0, 0.0);
			
	glColor3ub(0, 0, 255);     // make OZ axis
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 30.0);
	glEnd();
	

	glColor3ub(255, 255, 255);
  DrawStringAt(40, 0.0, 0.0, "X");
	DrawStringAt(0.0, 40, 0.0, "Y");
	DrawStringAt(0.0, 0.0, 40, "Z");

  // make X Arrow 
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslatef(30.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glutSolidCone(2, 10, 10, 10);
	glPopMatrix();

  // Make Y Arrow
	glPushMatrix();
	glColor3ub(0, 255, 0);
	glTranslatef(0.0, 30.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(2, 10, 10, 10);
	glPopMatrix();

	//Make Z Arrow
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslatef(0.0, 0.0, 30);
	glutSolidCone(2, 10, 10, 10);
	glPopMatrix();
 glEndList();
}

void CCad_ShowView::SetColorForBackGround(float red_value, float green_value, float blue_value) {
  red_color_ = red_value;
  green_color_ = green_value;
  blue_color_ = blue_value;
  InvalidateRect(NULL, FALSE);
}


void CCad_ShowView::OnDestroy() {
  theApp.FreePoint();
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

// if don't use OnTime so can this use to replace
void CCad_ShowView::OnAnimation() {
  //return;
  if (is_check_rotate_ == TRUE) {
    angle_x_cad_ += speed_rotate_  + 0.5f;
    angle_z_cad_ += speed_rotate_  + 0.5f;
    if (angle_x_cad_ >= 360.0f) {
      angle_x_cad_ = 0.0f;
    } 
    if (angle_x_cad_ >= 360.0f) {
      angle_z_cad_ = 0.0f;
    }
  }
}

void CCad_ShowView::OnTimer(UINT_PTR nIDEvent) {
  //return ; // do not use Ontimer to make rotation for cad
  switch (nIDEvent) {
  case 0:
    break;
  case 1: {   // use when SetTime(1,...) is called
    SetRotateForCad();
   }
    break;
  default: break;
  }
  //CView::OnTimer(nIDEvent);
  InvalidateRect(NULL, FALSE);
}

void CCad_ShowView::SetRotateForCad() {
  //if (theApp.GetTrianglePoint() != NULL || is_draw_sample_) {
    if (is_rot_x_ == true) {
      angle_x_cad_ += speed_rotate_ + 0.5f;
    }
    if (is_rot_y_ == true) {
      angle_y_cad_ += speed_rotate_ + 0.5f;
    }
    if (is_rot_z_ == true) {
      angle_z_cad_ += speed_rotate_ + 0.5f;
    }
    if (angle_x_cad_ >= 360.0f) {
      angle_x_cad_ = 0.0f;
    }
    if (angle_y_cad_ >= 360.0f) {
      angle_y_cad_ = 0.0f;
    }
    if (angle_z_cad_ >= 360.0f) {
      angle_z_cad_ = 0.0f;
    }
 // }
}

void CCad_ShowView::OnHandleViewButton(UINT nID) {
  if (nID == ID_VIEW_TOP) {
#if 0       
    angle_x_ = 0.0f;
    angle_y_ = 0.0f;
    angle_z_ = 0.0f;

    angle_x_cad_ = 0.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = 0.0f;

    angle_x_big_cdn_ = 0.0f;
    angle_y_big_cdn_ = 0.0f;
    angle_z_big_cdn_ = 0.0f;
#else
    phi_ = 90.0;
    theta_ = 180.0;
    ::glMatrixMode( GL_MODELVIEW );
    ::glLoadIdentity();
#endif
  }

  if (nID == ID_VIEW_BOTTOM) {
#if 0
    angle_x_ = -180.0f;
    angle_y_ = 0.0f;
    angle_z_ = 0.0f;

    angle_x_cad_ = -180.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = 0.0f;

    angle_x_big_cdn_ = -180.0f;
    angle_y_big_cdn_ = 0.0f;
    angle_z_big_cdn_ = 0.0f;
#else
    phi_ = 270.0;
    theta_ = 180.0;
    ::glMatrixMode( GL_MODELVIEW );
    ::glLoadIdentity();
#endif
  }

  if (nID == ID_VIEW_BACK) {
#if 0
    angle_x_ = -90.0f;
    angle_y_ = 0.0f;
    angle_z_ = 90.0f;

    angle_x_cad_ = -90.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = 90.0f;

    angle_x_big_cdn_ = -90.0f;
    angle_y_big_cdn_ = 0.0f;
    angle_z_big_cdn_ = 90.0f;
#else
    phi_ = 0.0;
    theta_ = 0.0;
    ::glMatrixMode( GL_MODELVIEW );
    ::glLoadIdentity();
#endif
  }

  if (nID == ID_VIEW_FRONT) {
#if 0
    angle_x_ = -90.0f;
    angle_y_ = 0.0f;
    angle_z_ = -90.0f;

    angle_x_cad_ = -90.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = -90.0f;

    angle_x_big_cdn_ = -90.0f;
    angle_y_big_cdn_ = 0.0f;
    angle_z_big_cdn_ = -90.0f;
#else
    phi_ = 0.0;
    theta_ = - 180.0;
    ::glMatrixMode( GL_MODELVIEW );
    ::glLoadIdentity();
#endif
  }

  if (nID == ID_VIEW_RIGHT) {
#if 0
    angle_x_ = -90.0f;
    angle_y_ = 0.0f;
    angle_z_ = -180.0f;

    angle_x_cad_ = -90.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = -180.0f;

    angle_x_big_cdn_ = -90.0f;
    angle_y_big_cdn_ = 0.0f;
    angle_z_big_cdn_ = -180.0f;
#else
    phi_ = 0.0;
    theta_ = 90.0;
    ::glMatrixMode( GL_MODELVIEW );
    ::glLoadIdentity();
#endif
  }

  if (nID == ID_VIEW_LEFT) {
#if 0
    angle_x_ = -90.0f;
    angle_y_ = 0.0f;
    angle_z_ = 0.0f;

    angle_x_cad_ = -90.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = 0.0f;

    angle_x_big_cdn_ = -90.0f;
    angle_y_big_cdn_ = 0.0f;
    angle_z_big_cdn_ = 0.0f;
#else
    phi_ = 0.0;
    theta_ = -90.0;
    ::glMatrixMode( GL_MODELVIEW );
    ::glLoadIdentity();
#endif
  }

  if (nID == ID_VIEW_ISO) {
#if 0
    angle_x_ = -60.0f;
    angle_y_ = 0.0f;
    angle_z_ = -135.0f;

    angle_x_cad_ = -60.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = -135.0f;

    angle_x_big_cdn_ = -60.0f;
    angle_y_big_cdn_ = 0.0f;
    angle_z_big_cdn_ = -135.0f;
#else
  theta_ = 135.0f;
  phi_ = 45.0f;
  ::glMatrixMode( GL_MODELVIEW );
  ::glLoadIdentity();
#endif
  }

  if (nID == ID_VIEW_ZOOM_IN) {
    m_scaling *= 1.25f;  // zoom +
  }
  if (nID == ID_VIEW_ZOOM_OUT) {
    m_scaling /= 1.25f; // zoom -
  }
  InvalidateRect(NULL, FALSE);
}

void CCad_ShowView::OnHandleMoveButton(UINT nID) {
  if (theApp.GetTrianglePoint()) {
    if (nID == ID_VIEW_MOVE_DOWN) {
      yPos_ -= 10.0f;
    }
    if (nID ==ID_VIEW_MOVE_UP) {
      yPos_ += 10.0f;
    }
    if (nID == ID_VIEW_MOVE_LEFT) {
      xPos_ -= 10.0f;
    }
    if (nID == ID_VIEW_MOVE_RIGHT) {
      xPos_ += 10.0f;
    }
  }
  InvalidateRect(NULL, FALSE);
}

void CCad_ShowView::OnHandleRotateButton(UINT nID) {
  
}

void CCad_ShowView::OnHandleResetCad() {
  angle_x_ = 0.0f;
  angle_y_ = 0.0f;
  angle_z_ = .0f;

  angle_x_cad_ = 0.0f;
  angle_y_cad_ = 0.0f;
  angle_z_cad_ = 0.0f;

  angle_x_big_cdn_ = 0.0f;
  angle_y_big_cdn_ = 0.0f;
  angle_z_big_cdn_ = 0.0f;
  theta_ = 135.0f;
  phi_ = 45.0f;
  x_position_ = 0.0f;
  y_position_ = 0.0f;
	xPos_ = 0.0f;
	yPos_ = 0.0f;
  InvalidateRect(NULL, FALSE);
}

// CCad_ShowView message handlers
void CCad_ShowView::ViewFullscreen() {
	CMainFrame* main_frame = static_cast<CMainFrame*>(AfxGetMainWnd());
	main_frame->OnViewFullscreen();
}

void CCad_ShowView::DrawSampleOpengl() {
#if 1
  if (is_draw_sample_) {
		if (mode_cad_ == ModelCad::SOLID_MODE_CAD) {
			SetUpLight();
			switch(sample_style_) {
			case SampleStyle::kTearpot:
				glPushMatrix();
				glRotatef(90.0, 1.0, 0.0, 0.0);
				glutSolidTeapot(30.0);
				glPopMatrix();
					break;
			case SampleStyle::kTorus:
				glutSolidTorus(30.0, 50, 16, 256);
				break;
			case SampleStyle::kCube:
				glutSolidCube(30.0);
				break;
			case SampleStyle::kSphere:
				glutSolidSphere(30.0, 16, 256);
				break;
			case SampleStyle::kCone:
				glutSolidCone(30.0, 50.0, 32, 128);
				break;
			case SampleStyle::kDodecahedron:
				glScaled(10.0, 10.0, 10.0);
				glutSolidDodecahedron();
				break;
			case SampleStyle::kIcosahedron:
				glScaled(10.0, 10.0, 10.0);
				glutSolidIcosahedron();
				break;
			case SampleStyle::kOctahedron:
				glScaled(10.0, 10.0, 10.0);
				glutSolidOctahedron();
				break;
			case SampleStyle::kTetrahedron:
				glScaled(10.0, 10.0, 10.0);
				glutSolidTetrahedron();
				break;
			default:
				break;
			}
		} else if (mode_cad_ == ModelCad::WIRE_FRAME_MODE_CAD) {
			DisableSetupLigting();
			switch(sample_style_) {
			case SampleStyle::kTearpot:
				glPushMatrix();
				glRotatef(90.0, 1.0, 0.0, 0.0);
				glutWireTeapot(30.0);
				glPopMatrix();
				break;
			case SampleStyle::kTorus:
				glutWireTorus(30.0, 50, 16, 256);
				break;
			case SampleStyle::kCube:
				glutWireCube(30.0);
				break;
			case SampleStyle::kSphere:
				glutWireSphere(30.0, 16, 256);
				break;
			case SampleStyle::kCone:
				glutWireCone(30.0, 50.0, 32, 128);
				break;
			case SampleStyle::kDodecahedron:
				glScaled(10.0, 10.0, 10.0);
				glutWireDodecahedron();
				break;
			case SampleStyle::kIcosahedron:
				glScaled(10.0, 10.0, 10.0);
				glutWireIcosahedron();
				break;
			case SampleStyle::kOctahedron:
				glScaled(10.0, 10.0, 10.0);
				glutWireOctahedron();
				break;
			case SampleStyle::kTetrahedron:
				glScaled(10.0, 10.0, 10.0);
				glutWireTetrahedron();
				break;
			default:
				break;
			}
		}
	}
#endif
}