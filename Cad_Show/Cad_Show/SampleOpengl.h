#pragma once
#include "afxwin.h"


// SampleOpengl dialog

class SampleOpengl : public CDialogEx
{
	DECLARE_DYNAMIC(SampleOpengl)

public:
	SampleOpengl(CWnd* pParent = NULL);   // standard constructor
	virtual ~SampleOpengl();

// Dialog Data
	enum { IDD = IDD_DLG_SAMPLE };
	enum SampleStyle {
		kTearpot = 0,
		kCube = 1,
		kSphere = 2,
		kTorus = 3,
		kCone = 4,
		kTetrahedron = 5,
		kIcosahedron = 6,
		kDodecahedron = 7,
		kOctahedron = 8,
	};
public:
	void InitComboxSamples();
	unsigned int GetCurrentSample() {return current_sample_;}
	void LoadBitmapSample(unsigned int sam_type);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void SelectItemCombox();


protected:
	CComboBox combox_sample_;
	unsigned current_sample_;
	CStatic image_sample_;
	CBitmap cbitmap_;
};
