// OpenGLDoc.h : interface of the COpenGLDoc class
//


#pragma once


class COpenGLDoc : public CDocument
{
protected: // create from serialization only
	COpenGLDoc();
	DECLARE_DYNCREATE(COpenGLDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~COpenGLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


