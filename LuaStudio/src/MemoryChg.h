/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#if !defined(AFX_MEMORYCHG_H__82E05821_16FE_11D1_A91F_444553540000__INCLUDED_)
#define AFX_MEMORYCHG_H__82E05821_16FE_11D1_A91F_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MemoryChg.h : header file
//

#include "resource.h"
#include "OutputMem.h"

/////////////////////////////////////////////////////////////////////////////
// CMemoryChg dialog

class CMemoryChg : public CDialog
{
  COutputMem& mem_;

  void Modify();
// Construction
public:
  CMemoryChg(COutputMem& mem, CWnd* parent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CMemoryChg)
  enum { IDD = IDD_MEMORY_CHG };
  UINT	addr_;
  int	data_;
  int	byte_;
  BOOL	signed_;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMemoryChg)
protected:
  virtual void DoDataExchange(CDataExchange* DX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CMemoryChg)
  afx_msg void OnChangeMemoryAddr();
  afx_msg void OnMemorySigned();
  afx_msg void OnMemoryByte();
  afx_msg void OnMemoryWord();
  virtual void OnOK();
  afx_msg void OnMemoryChg();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYCHG_H__82E05821_16FE_11D1_A91F_444553540000__INCLUDED_)
