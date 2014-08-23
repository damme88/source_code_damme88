#pragma once


// DlgMaterialLight dialog

class DlgMaterialLight : public CDialogEx
{
	DECLARE_DYNAMIC(DlgMaterialLight)

public:
	DlgMaterialLight(GLfloat ambien[],
									 GLfloat specular[],
									 GLfloat diffuse[],
									 GLfloat shininess,CWnd* pParent = NULL);
	DlgMaterialLight(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgMaterialLight();

// Dialog Data
	enum { IDD = IDD_DLG_MAT_LIGHT };

	void EditAmbienRed();
	void EditAmbienGreen();
	void EditAmbienBlue();
	void EditAmbienAnpha();
	void EditSpecRed();
	void EditSpecGreen();
	void EditSpecBlue();
	void EditSpecAnpha();
	void EditDiffRed();
	void EditDiffGreen();
	void EditDiffBlue();
	void EditDiffAnpha();
	void EditShininess();
	GLfloat* GetAmbien () const {
		GLfloat *pAm = new GLfloat [4];
		pAm[0] = ambien_[0];
		pAm[1] = ambien_[1];
		pAm[2] = ambien_[2];
		pAm[3] = ambien_[3];
		return pAm;
	}
	GLfloat* GetSpecular() const {
		GLfloat *pSpec = new GLfloat [4];
		pSpec[0] = specular_[0];
	  pSpec[1] = specular_[1];
	  pSpec[2] = specular_[2];
	 	pSpec[3] = specular_[3];
		return pSpec;
	}

	GLfloat* GetDiffuse() const {
		GLfloat *pDiff = new GLfloat [4];
		pDiff[0] = diffuse_[0];
		pDiff[1] = diffuse_[1];
		pDiff[2] = diffuse_[2];
		pDiff[3] = diffuse_[3];
		return pDiff;
	}
	GLfloat GetShininess() const {return shininess_;}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	GLfloat ambien_[4];
	GLfloat specular_[4];
	GLfloat diffuse_[4];
	GLfloat shininess_;
	CEdit ambien_edt_[4];
	CEdit specular_edt_[4];
	CEdit diffuse_edt_[4];
	CEdit shininess_edt_;
};
