// SplashWindows.cpp : implementation file
//

#include "stdafx.h"
#include "Simple_Draw.h"
#include "SplashWindows.h"


// SplashWindows

IMPLEMENT_DYNAMIC(SplashWindows, CWnd)
BOOL SplashWindows::show_splash_windows_;
SplashWindows* SplashWindows::splash_windows_;

SplashWindows::SplashWindows()
{

}

SplashWindows::~SplashWindows()
{
  ASSERT(splash_windows_ == this);
  splash_windows_ = NULL;
}


BEGIN_MESSAGE_MAP(SplashWindows, CWnd)
  ON_WM_PAINT()
  ON_WM_TIMER()
END_MESSAGE_MAP()


void SplashWindows::EnableSplashWindows(BOOL enable_splash) {
  show_splash_windows_ = enable_splash;
}

BOOL SplashWindows::ShowSplashWindows(UINT uTimeOut, UINT uBitmapID, CWnd* pParentWnd /*= NULL*/)
{
	ASSERT(uTimeOut && uBitmapID);
	
	if (!show_splash_windows_|| splash_windows_ != NULL) {
		return FALSE;
	}

	// Allocate a new splash screen, and create the window.
	splash_windows_ = new SplashWindows;

	if (!splash_windows_->bitmap_.LoadBitmap(uBitmapID)) {
		return FALSE;
	}

	BITMAP bm;
	splash_windows_->bitmap_.GetBitmap(&bm);

	CString strWndClass = AfxRegisterWndClass(0,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW));

	if (!splash_windows_->CreateEx(0, strWndClass, NULL, WS_POPUP | WS_VISIBLE,
		0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL))
	{
		TRACE0("Failed to create splash screen.\n");
		delete splash_windows_;
		return FALSE;
	}

	// Center the window.
	splash_windows_->CenterWindow();
	splash_windows_->UpdateWindow();

	// Set a timer to destroy the splash screen.
	splash_windows_->SetTimer(1, uTimeOut, NULL);
  Sleep(uTimeOut);
	return TRUE;
}


BOOL SplashWindows::PreTranslateAppMessage(MSG *pMsg)
{
	if ( splash_windows_== NULL)
		return FALSE;

	// If we get a keyboard or mouse message, hide the splash screen.
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		splash_windows_->HideSplashWindows();
		return TRUE;	// message handled here
	}

	return FALSE;	// message not handled
}

void SplashWindows::HideSplashWindows()
{
	// Destroy the window, and update the mainframe.
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();
}

void SplashWindows::PostNcDestroy()
{
	// Free the C++ class.
	delete this;
}

void SplashWindows::OnPaint()
{
	CPaintDC dc(this);

	CDC dcImage;
	if (dcImage.CreateCompatibleDC(&dc))
	{
		BITMAP bm;
		bitmap_.GetBitmap(&bm);

		// Paint the image.
		CBitmap* pOldBitmap = dcImage.SelectObject(&bitmap_);
		dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
		dcImage.SelectObject(pOldBitmap);
	}
}

void SplashWindows::OnTimer(UINT nIDEvent)
{
	// Destroy the splash screen window.
	HideSplashWindows();
}

// SplashWindows message handlers


