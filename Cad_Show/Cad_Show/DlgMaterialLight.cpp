// DlgMaterialLight.cpp : implementation file
//

#include "stdafx.h"
#include "Cad_Show.h"
#include "DlgMaterialLight.h"
#include "afxdialogex.h"


// DlgMaterialLight dialog

IMPLEMENT_DYNAMIC(DlgMaterialLight, CDialogEx)

DlgMaterialLight::DlgMaterialLight(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgMaterialLight::IDD, pParent)
{
}

DlgMaterialLight::DlgMaterialLight(GLfloat ambien[], GLfloat specular[],
	                                 GLfloat diffuse[],GLfloat shininess,
																	 CWnd* pParent /*=NULL*/)
: CDialogEx(DlgMaterialLight::IDD, pParent) {

	ambien_[0] = ambien[0];
	ambien_[1] = ambien[1];
	ambien_[2] = ambien[2];
	ambien_[3] = ambien[3];

	specular_[0] = specular[0];
	specular_[1] = specular[1];
	specular_[2] = specular[2];
  specular_[3] = specular[3];

	diffuse_[0] = diffuse[0];
	diffuse_[1] = diffuse[1];
	diffuse_[2] = diffuse[2];
	diffuse_[3] = diffuse[3];
	shininess_ = shininess;
}

DlgMaterialLight::~DlgMaterialLight()
{
}

void DlgMaterialLight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_EDT_AM_RED, ambien_edt_[0]);
  DDX_Control(pDX, IDC_EDT_AM_GREEN, ambien_edt_[1]);
  DDX_Control(pDX, IDC_EDT_AM_BLUE, ambien_edt_[2]);
	DDX_Control(pDX, IDC_EDT_AM_ANPHA, ambien_edt_[3]);
  DDX_Control(pDX, IDC_EDT_SPEC_RED, specular_edt_[0]);
  DDX_Control(pDX, IDC_EDT_SPEC_GREEN, specular_edt_[1]);
  DDX_Control(pDX, IDC_EDT_SPEC_BLUE, specular_edt_[2]);
  DDX_Control(pDX, IDC_EDT_SPEC_ANPHA, specular_edt_[3]);
  DDX_Control(pDX, IDC_EDT_DIFF_RED, diffuse_edt_[0]);
  DDX_Control(pDX, IDC_EDT_DIFF_GREEN, diffuse_edt_[1]);
  DDX_Control(pDX, IDC_EDT_DIFF_BLUE, diffuse_edt_[2]);
	DDX_Control(pDX, IDC_EDT_DIFF_ANPHA, diffuse_edt_[3]);
  DDX_Control(pDX, IDC_EDT_SHININESS, shininess_edt_);
}


BEGIN_MESSAGE_MAP(DlgMaterialLight, CDialogEx)
	ON_EN_CHANGE(IDC_EDT_AM_RED, EditAmbienRed)
	ON_EN_CHANGE(IDC_EDT_AM_GREEN, EditAmbienGreen)
	ON_EN_CHANGE(IDC_EDT_AM_BLUE, EditAmbienBlue)
	ON_EN_CHANGE(IDC_EDT_AM_ANPHA, EditAmbienAnpha)
	ON_EN_CHANGE(IDC_EDT_SPEC_RED, EditSpecRed)
	ON_EN_CHANGE(IDC_EDT_SPEC_GREEN, EditSpecGreen)
	ON_EN_CHANGE(IDC_EDT_SPEC_BLUE, EditSpecBlue)
	ON_EN_CHANGE(IDC_EDT_SPEC_ANPHA, EditSpecAnpha)
	ON_EN_CHANGE(IDC_EDT_DIFF_RED, EditDiffRed)
	ON_EN_CHANGE(IDC_EDT_DIFF_GREEN, EditDiffGreen)
	ON_EN_CHANGE(IDC_EDT_DIFF_BLUE, EditDiffBlue)
	ON_EN_CHANGE(IDC_EDT_DIFF_ANPHA, EditDiffAnpha)
	ON_EN_CHANGE(IDC_EDT_SHININESS, EditShininess)
END_MESSAGE_MAP()


// DlgMaterialLight message handlers


BOOL DlgMaterialLight::OnInitDialog() {
  CDialogEx::OnInitDialog();
	CString str;
	str.Format(_T("%f"), ambien_[0]);
	ambien_edt_[0].SetWindowText(str);

	str.Format(_T("%f"), ambien_[1]);
	ambien_edt_[1].SetWindowText(str);

	str.Format(_T("%f"), ambien_[2]);
	ambien_edt_[2].SetWindowText(str);

	str.Format(_T("%f"), ambien_[3]);
	ambien_edt_[3].SetWindowText(str);

	str.Format(_T("%f"), specular_[0]);
	specular_edt_[0].SetWindowText(str);

	str.Format(_T("%f"), specular_[1]);
	specular_edt_[1].SetWindowText(str);

	str.Format(_T("%f"), specular_[2]);
	specular_edt_[2].SetWindowText(str);

	str.Format(_T("%f"), specular_[3]);
	specular_edt_[3].SetWindowText(str);

	str.Format(_T("%f"), diffuse_[0]);
	diffuse_edt_[0].SetWindowText(str);

	str.Format(_T("%f"), diffuse_[1]);
	diffuse_edt_[1].SetWindowText(str);

	str.Format(_T("%f"), diffuse_[2]);
	diffuse_edt_[2].SetWindowText(str);

	str.Format(_T("%f"), diffuse_[3]);
	diffuse_edt_[3].SetWindowText(str);

	str.Format(_T("%f"), shininess_);
	shininess_edt_.SetWindowText(str);

	UpdateData(FALSE);
	return TRUE;
}

void DlgMaterialLight::EditAmbienRed() {
	CString str = _T("");
	ambien_edt_[0].GetWindowText(str);
	ambien_[0] = _tstof(str);
}
void DlgMaterialLight::EditAmbienGreen() {
	CString str = _T("");
	ambien_edt_[1].GetWindowText(str);
	ambien_[1] = _tstof(str);
}
void DlgMaterialLight::EditAmbienBlue() {
	CString str = _T("");
	ambien_edt_[2].GetWindowText(str);
	ambien_[2] = _tstof(str);
}
void DlgMaterialLight::EditAmbienAnpha() {
	CString str = _T("");
	ambien_edt_[3].GetWindowText(str);
	ambien_[3] = _tstof(str);
}
void DlgMaterialLight::EditSpecRed() {
	CString str = _T("");
	specular_edt_[0].GetWindowText(str);
	specular_[0] = _tstof(str);
}
void DlgMaterialLight::EditSpecGreen() {
	CString str = _T("");
	specular_edt_[1].GetWindowText(str);
	specular_[1] = _tstof(str);
}
void DlgMaterialLight::EditSpecBlue() {
	CString str = _T("");
	specular_edt_[2].GetWindowText(str);
	specular_[2] = _tstof(str);
}
void DlgMaterialLight::EditSpecAnpha() {
	CString str = _T("");
	specular_edt_[3].GetWindowText(str);
	specular_[3] = _tstof(str);
}
void DlgMaterialLight::EditDiffRed() {
	CString str = _T("");
	diffuse_edt_[0].GetWindowText(str);
	diffuse_[0] = _tstof(str);
}
void DlgMaterialLight::EditDiffGreen() {
	CString str = _T("");
	diffuse_edt_[1].GetWindowText(str);
	diffuse_[1] = _tstof(str);
}
void DlgMaterialLight::EditDiffBlue() {
	CString str = _T("");
	diffuse_edt_[2].GetWindowText(str);
	diffuse_[2] = _tstof(str);
}
void DlgMaterialLight::EditDiffAnpha() {
	CString str = _T("");
	diffuse_edt_[3].GetWindowText(str);
	diffuse_[3] = _tstof(str);
}
void DlgMaterialLight::EditShininess() {
	CString str = _T("");
	shininess_edt_.GetWindowText(str);
	shininess_ = _tstof(str);
}