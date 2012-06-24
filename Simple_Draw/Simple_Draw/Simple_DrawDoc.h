
// Simple_DrawDoc.h : interface of the CSimple_DrawDoc class
//


#pragma once


class CSimple_DrawDoc : public CDocument
{
protected: // create from serialization only
	CSimple_DrawDoc();
	DECLARE_DYNCREATE(CSimple_DrawDoc)

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
	virtual ~CSimple_DrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


