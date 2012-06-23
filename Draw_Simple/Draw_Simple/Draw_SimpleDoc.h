
// Draw_SimpleDoc.h : interface of the CDraw_SimpleDoc class
//


#pragma once


class CDraw_SimpleDoc : public CDocument
{
protected: // create from serialization only
	CDraw_SimpleDoc();
	DECLARE_DYNCREATE(CDraw_SimpleDoc)

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
	virtual ~CDraw_SimpleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


