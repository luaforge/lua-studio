/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// OptionsViewPage.h : header file
//

#include "resource.h"
#include "ColorButton.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsViewPage dialog

class COptionsViewPage : public CPropertyPage
{
  CColorButton color_button_text_;
  CColorButton color_button_bkgnd_;
  BOOL subclassed_;
  int selection_;
  COLORREF rgb_bkgnd_col_;
  COLORREF rgb_text_col_;

  void repaint_example();

  DECLARE_DYNCREATE(COptionsViewPage)
    // Construction
public:
	struct TextDef
	{
		COLORREF text, bkgnd;
		CFont font;
		int changed;
		CBrush brush;
	};
	static TextDef text_[];

  COptionsViewPage();
  ~COptionsViewPage();
  
  // Dialog Data
  //{{AFX_DATA(COptionsViewPage)
  enum { IDD = IDD_PROPPAGE_VIEW };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(COptionsViewPage)
public:
  virtual BOOL OnSetActive();
protected:
  virtual void DoDataExchange(CDataExchange* DX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(COptionsViewPage)
  afx_msg HBRUSH OnCtlColor(CDC* dc, CWnd* wnd, UINT ctl_color);
  afx_msg void OnSelchangeViewWnd();
  afx_msg void OnViewTxtCol();
  afx_msg void OnViewBkgndCol();
  afx_msg void OnViewFontBtn();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
    
};
