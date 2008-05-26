/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// Options.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Options.h"
#include "ConfigSettings.h"

//static const char *HELP_FILE_6502= "6502.hlp";

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern void AFX_CDECL DDX_HexDec(CDataExchange* DX, int IDC, unsigned int &num, bool word= true);

/////////////////////////////////////////////////////////////////////////////
// COptions

IMPLEMENT_DYNAMIC(COptions, CPropertySheet)

/*
COptions::COptions(UINT id_caption, CWnd* parent_wnd, UINT iSelectPage)
: CPropertySheet(id_caption, parent_wnd, iSelectPage)
{
}

COptions::COptions(LPCTSTR caption, CWnd* parent_wnd, UINT iSelectPage)
: CPropertySheet(caption, parent_wnd, iSelectPage)
{
}
*/

COptions::COptions(CWnd* parent_wnd, UINT iSelectPage)
: CPropertySheet(ID, parent_wnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW | PSH_HASHELP | PSH_USECALLBACK;
	m_psh.pfnCallback = &PropSheetProc;
//	AddPage(&sym_page_);
//	AddPage(&asm_page_);
//	AddPage(&edit_page_);
//	AddPage(&deasm_page_);
//	AddPage(&marks_page_);
//	AddPage(&view_page_);
	last_active_page_index_ = iSelectPage;
}

COptions::~COptions()
{
}


int CALLBACK COptions::PropSheetProc(HWND dlg, UINT msg, LPARAM lParam)
{
	if (msg == PSCB_INITIALIZED && ::IsWindow(dlg))
		CWnd::FromHandle(dlg)->ModifyStyleEx(0, WS_EX_CONTEXTHELP);  // w³¹czenie pomocy kontekstowej

	return 0;
}


int COptions::GetLastActivePage()
{
	return last_active_page_index_;
}


BEGIN_MESSAGE_MAP(COptions, CPropertySheet)
	//{{AFX_MSG_MAP(COptions)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptions message handlers

BOOL COptions::OnCommand(WPARAM wParam, LPARAM lParam)
{
	last_active_page_index_ = GetActiveIndex();
	return CPropertySheet::OnCommand(wParam, lParam);
}

#if 0

/////////////////////////////////////////////////////////////////////////////
// COptionsSymPage property page

IMPLEMENT_DYNCREATE(COptionsSymPage, CPropertyPage)

COptionsSymPage::COptionsSymPage() : CPropertyPage(COptionsSymPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsSymPage)
	IO_address_ = 0;
	IO_enable_ = FALSE;
	finish_ = -1;
	wnd_width_ = 0;
	wnd_height_ = 0;
	protect_memory_ = FALSE;
	prot_from_addr_ = 0;
	prot_to_addr_ = 0;
	//}}AFX_DATA_INIT
}

COptionsSymPage::~COptionsSymPage()
{
}

void COptionsSymPage::DoDataExchange(CDataExchange* DX)
{
	if (!DX->m_bSaveAndValidate)
	{
		CSpinButtonCtrl *cols;
		cols = (CSpinButtonCtrl *) GetDlgItem(IDC_OPT_SYM_W_SPIN);
		ASSERT(cols != NULL);
		cols->SetRange(1, 255);		// iloœæ kolumn terminala

		CSpinButtonCtrl *rows;
		rows = (CSpinButtonCtrl *) GetDlgItem(IDC_OPT_SYM_H_SPIN);
		ASSERT(rows != NULL);
		rows->SetRange(1, 255);		// iloœæ wierszy terminala
	}

	CPropertyPage::DoDataExchange(DX);
	//{{AFX_DATA_MAP(COptionsSymPage)
	DDX_Check(DX, IDC_OPT_SYM_IO_ENABLE, IO_enable_);
	DDX_Radio(DX, IDC_OPT_SYM_FIN_BRK, finish_);
	DDX_Text(DX, IDC_OPT_SYM_IO_WND_W, wnd_width_);
	DDX_Text(DX, IDC_OPT_SYM_IO_WND_H, wnd_height_);
	DDX_Check(DX, IDC_OPT_SYM_PROTECT_MEM, protect_memory_);
	//}}AFX_DATA_MAP
	//	DDX_HexDec(DX, IDC_OPT_SYM_IO_ADDR, IO_address_);
	DDV_MinMaxUInt(DX, IO_address_, 0, 65535);
	//	DDX_HexDec(DX, IDC_OPT_SYM_PROT_FROM, prot_from_addr_);
	DDV_MinMaxUInt(DX, prot_from_addr_, 0, 0xffff);
	//	DDX_HexDec(DX, IDC_OPT_SYM_PROT_TO, prot_to_addr_);
	DDV_MinMaxUInt(DX, prot_to_addr_, 0, 0xffff);
}


BEGIN_MESSAGE_MAP(COptionsSymPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsSymPage)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsSymPage message handlers



/////////////////////////////////////////////////////////////////////////////
// COptionsEditPage property page

IMPLEMENT_DYNCREATE(COptionsEditPage, CPropertyPage)

COptionsEditPage::COptionsEditPage() : CPropertyPage(COptionsEditPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsEditPage)
	auto_indent_ = FALSE;
	tab_step_ = 0;
	auto_syntax_ = FALSE;
	auto_uppercase_ = FALSE;
	file_new_ = FALSE;
	element_ = 0;
	//}}AFX_DATA_INIT
	color_changed_ = false;
}

COptionsEditPage::~COptionsEditPage()
{
}

void COptionsEditPage::DoDataExchange(CDataExchange* DX)
{
	if (!DX->m_bSaveAndValidate)
	{
		CSpinButtonCtrl *tab;
		tab = (CSpinButtonCtrl *) GetDlgItem(IDC_OPT_ED_TAB_SPIN);
		ASSERT(tab != NULL);
		tab->SetRange(2,32);		// krok tabulatora z zakresu 2..32
	}
	CPropertyPage::DoDataExchange(DX);
	//{{AFX_DATA_MAP(COptionsEditPage)
	DDX_Control(DX, IDC_OPT_ED_BOLD_FONT, btn_bold_);
	DDX_Control(DX, IDC_OPT_ED_COLOR, btn_color_);
	DDX_Control(DX, IDC_OPT_ED_ELEMENT, element_wnd_);
	DDX_Control(DX, IDC_OPT_ED_EXAMPLE, example_wnd_);
	DDX_Check(DX, IDC_OPT_ED_AUTO_INDENT, auto_indent_);
	DDX_Text(DX, IDC_OPT_ED_TAB_STEP, tab_step_);
	DDV_MinMaxInt(DX, tab_step_, 2, 32);
	DDX_Check(DX, IDC_OPT_ED_AUTO_SYNTAX, auto_syntax_);
	DDX_Check(DX, IDC_OPT_ED_AUTO_UPPER_CASE, auto_uppercase_);
	DDX_Check(DX, IDC_OPT_ED_NEW_FILE, file_new_);
	DDX_CBIndex(DX, IDC_OPT_ED_ELEMENT, element_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsEditPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsEditPage)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_OPT_ED_TAB_STEP, OnChangeTabStep)
	ON_BN_CLICKED(IDC_OPT_ED_COLOR_SYNTAX, OnColorSyntax)
	ON_CBN_SELCHANGE(IDC_OPT_ED_ELEMENT, OnSelChangeElement)
	ON_BN_CLICKED(IDC_OPT_ED_COLOR, OnEditColor)
	ON_BN_CLICKED(IDC_OPT_ED_BOLD_FONT, OnBoldFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsEditPage message handlers

BOOL COptionsEditPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// copy color settings
	example_wnd_.rgb_instruction_	= *CConfigSettings::color_syntax[0];
	example_wnd_.rgb_directive_		= *CConfigSettings::color_syntax[1];
	example_wnd_.rgb_comment_		= *CConfigSettings::color_syntax[2];
	example_wnd_.rgb_number_		= *CConfigSettings::color_syntax[3];
	example_wnd_.rgb_string_		= *CConfigSettings::color_syntax[4];
	example_wnd_.rgb_selection_		= *CConfigSettings::color_syntax[5];

	example_wnd_.vb_bold_[0]		= *CConfigSettings::syntax_font_style[0];
	example_wnd_.vb_bold_[1]		= *CConfigSettings::syntax_font_style[1];
	example_wnd_.vb_bold_[2]		= *CConfigSettings::syntax_font_style[2];
	example_wnd_.vb_bold_[3]		= *CConfigSettings::syntax_font_style[3];
	example_wnd_.vb_bold_[4]		= *CConfigSettings::syntax_font_style[4];

	OnSelChangeElement();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL COptionsEditPage::OnSetActive()
{
	// copy font settings
	example_wnd_.editor_font_		= COptionsViewPage::text_[0].font;
	example_wnd_.rgb_background_	= COptionsViewPage::text_[0].bkgnd;
	example_wnd_.rgb_text_			= COptionsViewPage::text_[0].text;

	return CPropertyPage::OnSetActive();
}


void COptionsEditPage::OnChangeTabStep()
{
}

void COptionsEditPage::OnColorSyntax()
{
}

void COptionsEditPage::OnBoldFont()
{
	if (bool* bold= GetFontStyle())
	{
		*bold = btn_bold_.GetCheck() > 0;
		example_wnd_.Invalidate();
		color_changed_ = true;
	}
}


bool* COptionsEditPage::GetFontStyle(int index)
{
	if (index >= 0 && index < 5)
		return &example_wnd_.vb_bold_[index];

	return 0;
}

bool* COptionsEditPage::GetFontStyle()
{
	return GetFontStyle(element_wnd_.GetCurSel());
}


void COptionsEditPage::OnEditColor()
{
	if (COLORREF* color= COptionsEditPage::GetColorElement())
	{
		CColorDialog dlg(*color, CC_FULLOPEN);

		if (dlg.DoModal() == IDOK && *color != dlg.GetColor())
		{
			*color = dlg.GetColor();
			btn_color_.Invalidate();
			example_wnd_.Invalidate();
			color_changed_ = true;
		}
	}
}


void COptionsEditPage::OnSelChangeElement()
{
	if (COLORREF* p= GetColorElement())
		btn_color_.SetColorRef(p);
	if (bool* bold= GetFontStyle())
	{
		btn_bold_.EnableWindow();
		btn_bold_.SetCheck(*bold ? 1 : 0);
	}
	else
	{
		btn_bold_.EnableWindow(false);
		btn_bold_.SetCheck(0);
	}
}


COLORREF* COptionsEditPage::GetColorElement(int index)
{
	switch (index)
	{
	case 0:
		return &example_wnd_.rgb_instruction_;
	case 1:
		return &example_wnd_.rgb_directive_;
	case 2:
		return &example_wnd_.rgb_comment_;
	case 3:
		return &example_wnd_.rgb_number_;
	case 4:
		return &example_wnd_.rgb_string_;
	case 5:
		return &example_wnd_.rgb_selection_;
	default:
		return 0;
	}
}

COLORREF* COptionsEditPage::GetColorElement()
{
	return GetColorElement(element_wnd_.GetCurSel());
}


/////////////////////////////////////////////////////////////////////////////
// COptionsAsmPage property page

IMPLEMENT_DYNCREATE(COptionsAsmPage, CPropertyPage)

COptionsAsmPage::COptionsAsmPage() : CPropertyPage(COptionsAsmPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsAsmPage)
	case_sensitive_ = -1;
	asm_instr_with_dot_ = -1;
	generate_listing_ = FALSE;
	listing_file_ = _T("");
	generateBRK_extra_byte_ = FALSE;
	brk_extra_byte_ = 0;
	//}}AFX_DATA_INIT
}

COptionsAsmPage::~COptionsAsmPage()
{
}

void COptionsAsmPage::DoDataExchange(CDataExchange* DX)
{ 
	CPropertyPage::DoDataExchange(DX);
	//{{AFX_DATA_MAP(COptionsAsmPage)
	DDX_Radio(DX, IDC_OPT_ASM_CASE_Y, case_sensitive_);
	DDX_Radio(DX, IDC_OPT_ASM_INSTR_DOT, asm_instr_with_dot_);
	DDX_Check(DX, IDC_OPT_ASM_GENERATE_LIST, generate_listing_);
	DDX_Text(DX, IDC_OPT_ASM_FILE_LISTING, listing_file_);
	DDX_Check(DX, IDC_OPT_ASM_GENERATE_BYTE, generateBRK_extra_byte_);
	//}}AFX_DATA_MAP
	//  DDX_Text(DX, IDC_OPT_ASM_EXTRA_BYTE, brk_extra_byte_);
	// DDX_HexDec(DX, IDC_OPT_ASM_EXTRA_BYTE, brk_extra_byte_, false);
	DDV_MinMaxUInt(DX,brk_extra_byte_,0,0xFF);
}


BEGIN_MESSAGE_MAP(COptionsAsmPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsAsmPage)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_OPT_ASM_CHOOSE_FILE, OnOptAsmChooseFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsAsmPage message handlers


/////////////////////////////////////////////////////////////////////////////
// COptionsDeasmPage property page

IMPLEMENT_DYNCREATE(COptionsDeasmPage, CPropertyPage)

COptionsDeasmPage::COptionsDeasmPage() : CPropertyPage(COptionsDeasmPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsDeasmPage)
	show_code_ = FALSE;
	//}}AFX_DATA_INIT
	subclassed_ = FALSE;
	color_changed_ = FALSE;
}

COptionsDeasmPage::~COptionsDeasmPage()
{
}

void COptionsDeasmPage::DoDataExchange(CDataExchange* DX)
{
	CPropertyPage::DoDataExchange(DX);
	//{{AFX_DATA_MAP(COptionsDeasmPage)
	DDX_Check(DX, IDC_OPT_DA_CODE, show_code_);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDeasmPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsDeasmPage)
	ON_BN_CLICKED(IDC_OPT_DA_ADDR_COL, OnAddrColButton)
	ON_BN_CLICKED(IDC_OPT_DA_CODE_COL, OnCodeColButton)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDeasmPage message handlers

void COptionsDeasmPage::OnAddrColButton()
{
	CColorDialog dlg(rgb_address_,CC_FULLOPEN);
	if (dlg.DoModal() == IDOK && rgb_address_ != dlg.GetColor())
	{
		rgb_address_ = dlg.GetColor();
		color_changed_ = TRUE;
		color_button_address_.InvalidateRect(NULL);
	}
}


void COptionsDeasmPage::OnCodeColButton()
{
	CColorDialog dlg(rgb_code_,CC_FULLOPEN);
	if (dlg.DoModal() == IDOK && rgb_code_ != dlg.GetColor())
	{
		rgb_code_ = dlg.GetColor();
		color_changed_ = TRUE;
		color_button_code_.InvalidateRect(NULL);
	}
}


BOOL COptionsDeasmPage::OnSetActive()
{
	if (!subclassed_)
	{
		color_button_address_.SubclassDlgItem(IDC_OPT_DA_ADDR_COL,this);
		color_button_address_.SetColorRef(&rgb_address_);
		color_button_code_.SubclassDlgItem(IDC_OPT_DA_CODE_COL,this);
		color_button_code_.SetColorRef(&rgb_code_);
		//    color_button_instr_.SubclassDlgItem(IDC_OPT_DA_INSTR_COL,this);
		//    color_button_instr_.SetColorRef(&rgb_instr_);
		subclassed_ = TRUE;
	}
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// COptionsMarksPage property page

IMPLEMENT_DYNCREATE(COptionsMarksPage, CPropertyPage)

COptionsMarksPage::COptionsMarksPage() : CPropertyPage(COptionsMarksPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsMarksPage)
	proc6502_ = -1;
	bus_width_ = 16;
	//}}AFX_DATA_INIT
	subclassed_ = FALSE;
	color_changed_ = FALSE;
	font_changed_ = FALSE;
}

COptionsMarksPage::~COptionsMarksPage()
{
}

void COptionsMarksPage::DoDataExchange(CDataExchange* DX)
{
	if (!DX->m_bSaveAndValidate)
	{
		CSpinButtonCtrl *tab;
		tab = (CSpinButtonCtrl *) GetDlgItem(IDC_OPT_BUS_SPIN);
		ASSERT(tab != NULL);
		tab->SetRange(10,16);		// wielkoœæ szyny adresowej
	}

	CPropertyPage::DoDataExchange(DX);
	//{{AFX_DATA_MAP(COptionsMarksPage)
	DDX_Radio(DX, IDC_OPT_6502, proc6502_);
	DDX_Text(DX, IDC_OPT_BUS_WIDTH, bus_width_);
	DDV_MinMaxUInt(DX, bus_width_, 10, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsMarksPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsMarksPage)
	ON_BN_CLICKED(IDC_OPT_MARK_BRKP_COL, OnBrkpColButton)
	ON_BN_CLICKED(IDC_OPT_MARK_ERR_COL, OnErrColButton)
	ON_BN_CLICKED(IDC_OPT_MARK_PTR_COL, OnPtrColButton)
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_OPT_FONT_BTN, OnOptFontBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsMarksPage message handlers

void COptionsMarksPage::OnBrkpColButton()
{
	CColorDialog dlg(rgb_breakpoint_,CC_FULLOPEN);
	if (dlg.DoModal() == IDOK && rgb_breakpoint_ != dlg.GetColor())
	{
		rgb_breakpoint_ = dlg.GetColor();
		color_changed_ = TRUE;
		color_button_breakpoint_.InvalidateRect(NULL);
	}
}

void COptionsMarksPage::OnErrColButton()
{
	CColorDialog dlg(rgb_error_,CC_FULLOPEN);
	if (dlg.DoModal() == IDOK && rgb_error_ != dlg.GetColor())
	{
		rgb_error_ = dlg.GetColor();
		color_changed_ = TRUE;
		color_button_breakpoint_.InvalidateRect(NULL);
	}
}

void COptionsMarksPage::OnPtrColButton()
{
	CColorDialog dlg(rgb_pointer_,CC_FULLOPEN);
	if (dlg.DoModal() == IDOK && rgb_pointer_ != dlg.GetColor())
	{
		rgb_pointer_ = dlg.GetColor();
		color_changed_ = TRUE;
		color_button_breakpoint_.InvalidateRect(NULL);
	}
}

BOOL COptionsMarksPage::OnSetActive()
{
	if (!subclassed_)
	{
		color_button_pointer_.SubclassDlgItem(IDC_OPT_MARK_PTR_COL,this);
		color_button_pointer_.SetColorRef(&rgb_pointer_);
		color_button_breakpoint_.SubclassDlgItem(IDC_OPT_MARK_BRKP_COL,this);
		color_button_breakpoint_.SetColorRef(&rgb_breakpoint_);
		color_button_error_.SubclassDlgItem(IDC_OPT_MARK_ERR_COL,this);
		color_button_error_.SetColorRef(&rgb_error_);
		subclassed_ = TRUE;
	}
	return CPropertyPage::OnSetActive();
}

void COptionsMarksPage::OnOptFontBtn()
{
	CFontDialog fnt(&log_font_,CF_SCREENFONTS | CF_FIXEDPITCHONLY |
		CF_INITTOLOGFONTSTRUCT | CF_FORCEFONTEXIST | CF_SCRIPTSONLY);

	if (fnt.DoModal() == IDOK)
	{
		font_changed_ = TRUE;
		log_font_ = fnt.m_lf;
		SetDlgItemText(IDC_OPT_FONT_NAME, log_font_.lfFaceName);
	}
}


DWORD COptions::arr_ids_[]=
{
	IDC_OPT_SYM_FIN_BRK,	      0xA0000 + IDC_OPT_SYM_FIN_BRK,
	IDC_OPT_SYM_FIN_FF,	      0xA0000 + IDC_OPT_SYM_FIN_FF,
	IDC_OPT_SYM_FIN_RTS,	      0xA0000 + IDC_OPT_SYM_FIN_RTS,
	IDC_OPT_SYM_IO_ADDR,	      0xA0000 + IDC_OPT_SYM_IO_ADDR,
	IDC_OPT_SYM_IO_ENABLE,      0xA0000 + IDC_OPT_SYM_IO_ENABLE,
	IDC_OPT_SYM_IO_WND_W,       0xA0000 + IDC_OPT_SYM_IO_WND_W,
	IDC_OPT_SYM_IO_WND_H,	      0xA0000 + IDC_OPT_SYM_IO_WND_H,
	IDC_OPT_SYM_WND_TXT_COL,    0xA0000 + IDC_OPT_SYM_WND_TXT_COL,
	IDC_OPT_SYM_WND_BGND_COL,   0xA0000 + IDC_OPT_SYM_WND_BGND_COL,
	IDC_OPT_SYM_FONT_BTN,	      0xA0000 + IDC_OPT_SYM_FONT_BTN,
	IDC_OPT_SYM_FONT_NAME,      0xA0000 + IDC_OPT_SYM_FONT_NAME,

	IDC_OPT_ASM_CASE_N,	      0xA0000 + IDC_OPT_ASM_CASE_N,
	IDC_OPT_ASM_CASE_Y,	      0xA0000 + IDC_OPT_ASM_CASE_Y,
	IDC_OPT_ASM_INSTR_DOT,      0xA0000 + IDC_OPT_ASM_INSTR_DOT,
	IDC_OPT_ASM_GENERATE_LIST,  0xA0000 + IDC_OPT_ASM_GENERATE_LIST,
	IDC_OPT_ASM_FILE_LISTING,   0xA0000 + IDC_OPT_ASM_FILE_LISTING,
	IDC_OPT_ASM_GENERATE_BYTE,  0xA0000 + IDC_OPT_ASM_GENERATE_BYTE,
	IDC_OPT_ASM_EXTRA_BYTE,     0xA0000 + IDC_OPT_ASM_EXTRA_BYTE,
	IDC_OPT_ASM_CHOOSE_FILE,    0xA0000 + IDC_OPT_ASM_CHOOSE_FILE,

	IDC_OPT_DA_ADDR_COL,	      0xA0000 + IDC_OPT_DA_ADDR_COL,
	IDC_OPT_DA_CODE,	      0xA0000 + IDC_OPT_DA_CODE,
	IDC_OPT_DA_CODE_COL,	      0xA0000 + IDC_OPT_DA_CODE_COL,
	IDC_OPT_DA_INSTR_COL,	      0xA0000 + IDC_OPT_DA_INSTR_COL,

	IDC_OPT_ED_AUTO_INDENT,     0xA0000 + IDC_OPT_ED_AUTO_INDENT,
	IDC_OPT_ED_AUTO_SYNTAX,     0xA0000 + IDC_OPT_ED_AUTO_SYNTAX,
	IDC_OPT_ED_AUTO_UPPER_CASE, 0xA0000 + IDC_OPT_ED_AUTO_UPPER_CASE,
	IDC_OPT_ED_FONT_BTN,	      0xA0000 + IDC_OPT_ED_FONT_BTN,
	IDC_OPT_ED_FONT_NAME,	      0xA0000 + IDC_OPT_ED_FONT_NAME,
	IDC_OPT_ED_NEW_FILE,	      0xA0000 + IDC_OPT_ED_NEW_FILE,
	IDC_OPT_ED_TAB_SPIN,	      0xA0000 + IDC_OPT_ED_TAB_STEP,
	IDC_OPT_ED_TAB_STEP,	      0xA0000 + IDC_OPT_ED_TAB_STEP,

	IDC_OPT_MARK_BRKP_COL,      0xA0000 + IDC_OPT_MARK_BRKP_COL,
	IDC_OPT_MARK_ERR_COL,	      0xA0000 + IDC_OPT_MARK_ERR_COL,
	IDC_OPT_MARK_PTR_COL,	      0xA0000 + IDC_OPT_MARK_PTR_COL,
	IDC_OPT_6502,		      0xA0000 + IDC_OPT_6502,
	IDC_OPT_65C02,	      0xA0000 + IDC_OPT_65C02,
	IDC_OPT_BUS_SPIN,	      0xA0000 + IDC_OPT_BUS_WIDTH,
	IDC_OPT_BUS_WIDTH,	      0xA0000 + IDC_OPT_BUS_WIDTH,
	0,0
};
#endif

DWORD COptions::arr_ids_[]=
{
	0,0
};

BOOL COptionsSymPage::OnHelpInfo(HELPINFO *help_info)
{
	::WinHelp(HWND(help_info->hItemHandle), AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, (DWORD)(void*)COptions::arr_ids_);
	return TRUE;
}


BOOL COptionsDeasmPage::OnHelpInfo(HELPINFO* help_info)
{
	::WinHelp(HWND(help_info->hItemHandle), AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, (DWORD)(void*)COptions::arr_ids_);
	return TRUE;
}


BOOL COptionsEditPage::OnHelpInfo(HELPINFO* help_info)
{
	::WinHelp(HWND(help_info->hItemHandle), AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, (DWORD)(void*)COptions::arr_ids_);

	return TRUE;
}


BOOL COptionsMarksPage::OnHelpInfo(HELPINFO* help_info)
{
	::WinHelp(HWND(help_info->hItemHandle), AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, (DWORD)(void*)COptions::arr_ids_);

	return TRUE;
}


BOOL COptionsAsmPage::OnHelpInfo(HELPINFO* help_info)
{
	::WinHelp(HWND(help_info->hItemHandle), AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, (DWORD)(void*)COptions::arr_ids_);

	return TRUE;
}


BOOL COptions::OnHelpInfo(HELPINFO* help_info)
{	
	return TRUE;
	//  return CPropertySheet::OnHelpInfo(help_info);
}



void COptionsSymPage::OnContextMenu(CWnd* wnd, CPoint point)
{
	::WinHelp(wnd->GetSafeHwnd(), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU, (DWORD)(void*)COptions::arr_ids_);
}


void COptions::OnContextMenu(CWnd* wnd, CPoint point)
{
	::WinHelp(wnd->GetSafeHwnd(), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU, (DWORD)(void*)COptions::arr_ids_);
}


void COptionsAsmPage::OnContextMenu(CWnd* wnd, CPoint point)
{
	::WinHelp(wnd->GetSafeHwnd(), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU, (DWORD)(void*)COptions::arr_ids_);
}


void COptionsDeasmPage::OnContextMenu(CWnd* wnd, CPoint point)
{
	::WinHelp(wnd->GetSafeHwnd(), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU, (DWORD)(void*)COptions::arr_ids_);
}


void COptionsEditPage::OnContextMenu(CWnd* wnd, CPoint point)
{
	::WinHelp(wnd->GetSafeHwnd(), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU, (DWORD)(void*)COptions::arr_ids_);
}


void COptionsMarksPage::OnContextMenu(CWnd* wnd, CPoint point)
{
	::WinHelp(wnd->GetSafeHwnd(), AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU, (DWORD)(void*)COptions::arr_ids_);
}

#if 0
void COptionsAsmPage::OnOptAsmChooseFile()
{
	CString filter;
	filter.LoadString(IDS_ASM_OPT_LIST_FILES);
	CFileDialog dlg(TRUE,_T("lst"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter);
	if (dlg.DoModal() != IDOK)
		return;
	SetDlgItemText(IDC_OPT_ASM_FILE_LISTING,dlg.GetPathName());
}

#endif
