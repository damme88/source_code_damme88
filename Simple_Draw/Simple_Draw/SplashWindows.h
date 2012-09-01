#pragma once


// SplashWindows

class SplashWindows : public CWnd
{
	DECLARE_DYNAMIC(SplashWindows)

public:
	SplashWindows();
	virtual ~SplashWindows();

protected:
	DECLARE_MESSAGE_MAP()
private:
  static BOOL show_splash_windows_;
  static SplashWindows* splash_windows_;
  CBitmap bitmap_;

public:
  static BOOL ShowSplashWindows(UINT uTimeOut, UINT uBitmapID, CWnd* pParentWnd = NULL);
  static void EnableSplashWindows(BOOL enalbe_splash = TRUE);
  static BOOL PreTranslateAppMessage(MSG* pMsg);

protected:
  void HideSplashWindows();
  virtual void PostNcDestroy();
  afx_msg void OnPaint();
  afx_msg void OnTimer(UINT nIDEvent);
};


