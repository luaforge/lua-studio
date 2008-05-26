/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// LuaSrcDoc.h : interface of the LuaSrcDoc class
//
/////////////////////////////////////////////////////////////////////////////
#ifdef USE_CRYSTAL_EDIT
	#include "CCrystalTextBuffer.h"
#endif
#include "scintilla-mfc/scintilladocview.h"


class LuaSrcDoc : public CScintillaDoc // CDocument
{
protected: // create from serialization only
  LuaSrcDoc();
  DECLARE_DYNCREATE(LuaSrcDoc)

// Attributes
public:
#ifdef USE_CRYSTAL_EDIT
	class CTextBuffer : public CCrystalTextBuffer
	{
	public:
		CDocument* owner_doc_;

		CTextBuffer() { owner_doc_ = 0; };

		virtual void SetModified(BOOL modified= TRUE)
		{ owner_doc_->SetModifiedFlag(modified); };
	};

	CTextBuffer text_buffer_;
	LOGFONT lf_normal_;

	void GetText(CString& text)		{ text_buffer_.GetText(text); }

	CCrystalTextBuffer* GetBuffer()		{ return &text_buffer_; }
#endif

// Operations
public:
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(LuaSrcDoc)
public:
	virtual BOOL OnNewDocument();
 // virtual void Serialize(CArchive& ar);
	//virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR path_name);
	//virtual BOOL OnSaveDocument(LPCTSTR path_name);
	//}}AFX_VIRTUAL

// Implementation
public:
  virtual ~LuaSrcDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  //{{AFX_MSG(LuaSrcDoc)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
