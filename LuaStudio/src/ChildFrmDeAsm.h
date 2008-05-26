/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// ChildFrm.h : interface of the CChildFrameDeAsm class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _ChildFrameDeAsm_
#define _ChildFrameDeAsm_


class CChildFrameDeAsm : public CMDIChildWnd
{
  DECLARE_DYNCREATE(CChildFrameDeAsm)
public:
  CChildFrameDeAsm();

  // Attributes
public:

  // Operations
public:

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CChildFrameDeAsm)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* context);
	//}}AFX_VIRTUAL
  
  // Implementation
public:
  virtual ~CChildFrameDeAsm();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif
  
  // Generated message map functions
protected:
  //{{AFX_MSG(CChildFrameDeAsm)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
