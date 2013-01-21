#pragma once



// DialogBar form view
class CCad_ShowDoc;
class DialogBar : public CFormView
{
	DECLARE_DYNCREATE(DialogBar)

protected:
	DialogBar();           // protected constructor used by dynamic creation
	virtual ~DialogBar();

public:
	enum { IDD = IDD_DIALOGBAR };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
// add new variable and function 
private:
  
protected:
  
public:
  CDialogBar *GetDocument();
  CView *GetDialogBarView();
  virtual void OnInitialUpdate();
};


