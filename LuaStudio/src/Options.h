/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#include "ColorButton.h"
#include "OptionsViewPage.h"
#include "SyntaxExample.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsSymPage dialog

class COptionsSymPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsSymPage)

// Construction
public:
	COptionsSymPage();
	~COptionsSymPage();

// Dialog Data
	//{{AFX_DATA(COptionsSymPage)
	enum { IDD = 1 }; //IDD_PROPPAGE_SYMULATOR };
	UINT	IO_address_;
	BOOL	IO_enable_;
	int	finish_;
	int	wnd_width_;
	int	wnd_height_;
	BOOL	protect_memory_;
	UINT	prot_from_addr_;
	UINT	prot_to_addr_;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsSymPage)
protected:
	virtual void DoDataExchange(CDataExchange* DX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsSymPage)
	afx_msg BOOL OnHelpInfo(HELPINFO* help_info);
	afx_msg void OnContextMenu(CWnd* wnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// COptionsEditPage dialog

class COptionsEditPage : public CPropertyPage
{
  DECLARE_DYNCREATE(COptionsEditPage)

public:
//  void OnChangeFont();

  // Construction
public:
  COptionsEditPage();
  ~COptionsEditPage();

	// Dialog Data
	//{{AFX_DATA(COptionsEditPage)
	enum { IDD = IDD_PROPPAGE_EDITOR };
	CButton	btn_bold_;
	CColorButton btn_color_;
	CComboBox	element_wnd_;
	CSyntaxExample example_wnd_;
	BOOL	auto_indent_;
	int	tab_step_;
	BOOL	auto_syntax_;
	BOOL	auto_uppercase_;
	BOOL	file_new_;
	int		element_;
	//}}AFX_DATA
	bool color_changed_;

	COLORREF* GetColorElement(int index);
	bool* GetFontStyle(int index);

  // Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(COptionsEditPage)
	public:
	virtual BOOL OnSetActive();
	protected:
  virtual void DoDataExchange(CDataExchange* DX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(COptionsEditPage)
  afx_msg BOOL OnHelpInfo(HELPINFO* help_info);
  afx_msg void OnContextMenu(CWnd* wnd, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeTabStep();
	afx_msg void OnColorSyntax();
	afx_msg void OnSelChangeElement();
	afx_msg void OnEditColor();
	afx_msg void OnBoldFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	COLORREF* GetColorElement();
	bool* GetFontStyle();
};

/////////////////////////////////////////////////////////////////////////////
// COptionsAsmPage dialog

class COptionsAsmPage : public CPropertyPage
{
  DECLARE_DYNCREATE(COptionsAsmPage)
    
    // Construction
public:
  COptionsAsmPage();
  ~COptionsAsmPage();
  
  // Dialog Data
  //{{AFX_DATA(COptionsAsmPage)
  enum { IDD = 1 }; //IDD_PROPPAGE_ASSEMBLY };
  int	case_sensitive_;
  int	asm_instr_with_dot_;
  BOOL	generate_listing_;
  CString listing_file_;
  BOOL	generateBRK_extra_byte_;
  UINT	brk_extra_byte_;
  //}}AFX_DATA


  // Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(COptionsAsmPage)
protected:
  virtual void DoDataExchange(CDataExchange* DX);    // DDX/DDV support
  //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(COptionsAsmPage)
  afx_msg BOOL OnHelpInfo(HELPINFO* help_info);
  afx_msg void OnContextMenu(CWnd* wnd, CPoint point);
  afx_msg void OnOptAsmChooseFile();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// COptionsDeasmPage dialog

class COptionsDeasmPage : public CPropertyPage
{
  CColorButton color_button_address_;
  CColorButton color_button_code_;
//  CColorButton color_button_instr_;
  bool subclassed_;

  DECLARE_DYNCREATE(COptionsDeasmPage)

public:
  COLORREF rgb_address_;
  COLORREF rgb_code_;
//  COLORREF rgb_instr_;
  bool color_changed_;

  // Construction
public:
  COptionsDeasmPage();
  ~COptionsDeasmPage();
  
  // Dialog Data
  //{{AFX_DATA(COptionsDeasmPage)
  enum { IDD = 1 }; //IDD_PROPPAGE_DEASM };
  BOOL	show_code_;
  //}}AFX_DATA
  
  
  // Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(COptionsDeasmPage)
public:
  virtual BOOL OnSetActive();
protected:
  virtual void DoDataExchange(CDataExchange* DX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(COptionsDeasmPage)
  afx_msg void OnAddrColButton();
  afx_msg void OnCodeColButton();
  afx_msg BOOL OnHelpInfo(HELPINFO* help_info);
  afx_msg void OnContextMenu(CWnd* wnd, CPoint point);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
    
};


/////////////////////////////////////////////////////////////////////////////
// COptionsMarksPage dialog

class COptionsMarksPage : public CPropertyPage
{
  CColorButton color_button_pointer_;
  CColorButton color_button_breakpoint_;
  CColorButton color_button_error_;
  bool subclassed_;

  DECLARE_DYNCREATE(COptionsMarksPage)

public:
  COLORREF rgb_pointer_;
  COLORREF rgb_breakpoint_;
  COLORREF rgb_error_;
  bool color_changed_;
  bool font_changed_;
  LOGFONT log_font_;

  // Construction
public:
  COptionsMarksPage();
  ~COptionsMarksPage();
  
  // Dialog Data
  //{{AFX_DATA(COptionsMarksPage)
  enum { IDD = IDD_PROPPAGE_GENERAL };
  int proc6502_;
  UINT	bus_width_;
  //}}AFX_DATA


  // Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(COptionsMarksPage)
public:
  virtual BOOL OnSetActive();
protected:
  virtual void DoDataExchange(CDataExchange* DX);    // DDX/DDV support
  //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(COptionsMarksPage)
  afx_msg void OnBrkpColButton();
  afx_msg void OnErrColButton();
  afx_msg void OnPtrColButton();
  afx_msg BOOL OnHelpInfo(HELPINFO* help_info);
  afx_msg void OnContextMenu(CWnd* wnd, CPoint point);
  afx_msg void OnOptFontBtn();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// COptions

class COptions : public CPropertySheet
{
  int last_active_page_index_;

  static int CALLBACK PropSheetProc(HWND dlg, UINT msg, LPARAM lParam);
//  static LRESULT CALLBACK EditDlgProc(HWND dlg, UINT msg, WPARAM wParam, LPARAM lParam);
//  static LRESULT (CALLBACK *pfn_old_proc_)(HWND,UINT,WPARAM,LPARAM);
//  static LRESULT CALLBACK ClassDlgProc(HWND dlg, UINT msg, WPARAM wParam, LPARAM lParam);
//  static LRESULT (CALLBACK *pfn_old_class_proc_)(HWND,UINT,WPARAM,LPARAM);

  DECLARE_DYNAMIC(COptions)

  enum { ID = IDS_OPTIONS };
  // Construction
public:
  COptions(CWnd* parent_wnd, UINT iSelectPage= 0);
//  COptions(UINT id_caption, CWnd* parent_wnd = NULL, UINT iSelectPage = 0);
//  COptions(LPCTSTR caption, CWnd* parent_wnd = NULL, UINT iSelectPage = 0);

  // Attributes
public:
  static DWORD arr_ids_[];
  //COptionsAsmPage asm_page_;
  //COptionsEditPage edit_page_;
  //COptionsSymPage sym_page_;
  //COptionsDeasmPage deasm_page_;
  //COptionsMarksPage marks_page_;
  //COptionsViewPage view_page_;

  // Operations
public:
  int GetLastActivePage();

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(COptions)
protected:
  virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
  //}}AFX_VIRTUAL

  // Implementation
public:
  virtual ~COptions();

  // Generated message map functions
protected:
  //{{AFX_MSG(COptions)
  afx_msg BOOL OnHelpInfo(HELPINFO* help_info);
  afx_msg void OnContextMenu(CWnd* wnd, CPoint point);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
