// SampleOpengl.cpp : implementation file
//

#include "stdafx.h"
#include "Cad_Show.h"
#include "SampleOpengl.h"
#include "afxdialogex.h"


// SampleOpengl dialog

IMPLEMENT_DYNAMIC(SampleOpengl, CDialogEx)

SampleOpengl::SampleOpengl(CWnd* pParent /*=NULL*/)
	: CDialogEx(SampleOpengl::IDD, pParent)
{

}

SampleOpengl::~SampleOpengl()
{
}

void SampleOpengl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_SAMPLE_OPENGL, combox_sample_);
	DDX_Control(pDX, IDC_PICTURE_SAMPLE, image_sample_);
}


BEGIN_MESSAGE_MAP(SampleOpengl, CDialogEx)
	ON_CBN_SELENDOK(IDC_CB_SAMPLE_OPENGL, SelectItemCombox)
END_MESSAGE_MAP()


// SampleOpengl message handlers
BOOL SampleOpengl::OnInitDialog() {
  if (CDialogEx::OnInitDialog() == FALSE)
		return FALSE;
	InitComboxSamples();
}

void SampleOpengl::InitComboxSamples() {
	combox_sample_.AddString(_T("Tearpot"));
	combox_sample_.AddString(_T("Cube"));
	combox_sample_.AddString(_T("Sphere"));
	combox_sample_.AddString(_T("Torus"));
  combox_sample_.AddString(_T("Cone"));
	combox_sample_.AddString(_T("Tetrahedron"));
	combox_sample_.AddString(_T("Icosahedron"));
	combox_sample_.AddString(_T("Dodecahedron"));
	combox_sample_.AddString(_T("Octahedron"));
	combox_sample_.SetCurSel(0);
	current_sample_ = 0;
	LoadBitmapSample(current_sample_);
}

void SampleOpengl::SelectItemCombox() {
	current_sample_ = combox_sample_.GetCurSel();
	LoadBitmapSample(current_sample_);
}

void SampleOpengl::LoadBitmapSample(unsigned int sam_type) {
  switch (sam_type) {
	case SampleStyle::kTearpot: {
		cbitmap_.Detach();
		cbitmap_.LoadBitmap(IDB_BITMAP_SAM_TEARPOT);
		image_sample_.SetBitmap((HBITMAP)cbitmap_);
		break;
	}
	case SampleStyle::kCube: {
		cbitmap_.Detach();
		cbitmap_.LoadBitmap(IDB_BITMAP_SAM_CUBE);
		image_sample_.SetBitmap((HBITMAP)cbitmap_);
		break;
	}
	case SampleStyle::kTorus:{
		cbitmap_.Detach();
		cbitmap_.LoadBitmap(IDB_BITMAP_SAM_TORUS);
		image_sample_.SetBitmap((HBITMAP)cbitmap_);
		break;
		}
	case SampleStyle::kSphere: {
		cbitmap_.Detach();
		cbitmap_.LoadBitmap(IDB_BITMAP_SAM_SPHERE);
		image_sample_.SetBitmap((HBITMAP)cbitmap_);
		break;
		}
	case SampleStyle::kCone: {
		cbitmap_.Detach();
		cbitmap_.LoadBitmap(IDB_BITMAP_SAM_CONE);
		image_sample_.SetBitmap((HBITMAP)cbitmap_);
		break;
		}
	case SampleStyle::kDodecahedron: {
		cbitmap_.Detach();
		cbitmap_.LoadBitmap(IDB_BITMAP_SAM_DODECA);
		image_sample_.SetBitmap((HBITMAP)cbitmap_);
		break;
		}
	case SampleStyle::kIcosahedron: {
		cbitmap_.Detach();
		cbitmap_.LoadBitmap(IDB_BITMAP_SAM_ICOSE);
		image_sample_.SetBitmap((HBITMAP)cbitmap_);
		break;
		}
	case SampleStyle::kOctahedron: {
		cbitmap_.Detach();
		cbitmap_.LoadBitmap(IDB_BITMAP_SAM_OCTAHE);
		image_sample_.SetBitmap((HBITMAP)cbitmap_);
		break;
		}
	case SampleStyle::kTetrahedron: {
		cbitmap_.Detach();
		cbitmap_.LoadBitmap(IDB_BITMAP_SAM_TETRAHE);
		image_sample_.SetBitmap((HBITMAP)cbitmap_);
		break;
		}
	}
}