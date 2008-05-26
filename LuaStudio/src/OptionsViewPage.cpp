/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// OptionsViewPage.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsViewPage.h"
#include "ConfigSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


COptionsViewPage::TextDef COptionsViewPage::text_[6];

/////////////////////////////////////////////////////////////////////////////
// COptionsViewPage property page

IMPLEMENT_DYNCREATE(COptionsViewPage, CPropertyPage)

COptionsViewPage::COptionsViewPage() : CPropertyPage(COptionsViewPage::IDD)
{
	//{{AFX_DATA_INIT(COptionsViewPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	subclassed_ = FALSE;
	selection_ = 0;

	for (int i= 0; i < sizeof(text_) / sizeof(text_[0]); i++)
	{
		text_[i].font.CreateFontIndirect(CConfigSettings::fonts[i]);
		text_[i].text = *CConfigSettings::text_color[i];
		text_[i].bkgnd = *CConfigSettings::bkgnd_color[i];
		text_[i].changed = 0;
	}
}


COptionsViewPage::~COptionsViewPage()
{
	for (int i= 0; i < sizeof(text_) / sizeof(text_[0]); i++)
	{
		text_[i].font.DeleteObject();
		text_[i].brush.DeleteObject();
	}
}


void COptionsViewPage::DoDataExchange(CDataExchange* DX)
{
	CPropertyPage::DoDataExchange(DX);
	//{{AFX_DATA_MAP(COptionsViewPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsViewPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsViewPage)
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_OPT_VIEW_WND, OnSelchangeViewWnd)
	ON_BN_CLICKED(IDC_OPT_VIEW_TXT_COL, OnViewTxtCol)
	ON_BN_CLICKED(IDC_OPT_VIEW_BKGND_COL, OnViewBkgndCol)
	ON_BN_CLICKED(IDC_OPT_VIEW_FONT_BTN, OnViewFontBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsViewPage message handlers

//#include "6502View.h"

HBRUSH COptionsViewPage::OnCtlColor(CDC* dc, CWnd* wnd, UINT ctl_color)
{
	if (ctl_color == CTLCOLOR_STATIC && wnd->GetDlgCtrlID() == IDC_OPT_VIEW_EXAMPLE)
	{
		text_[selection_].brush.DeleteObject();
		text_[selection_].brush.CreateSolidBrush(text_[selection_].bkgnd);
		//		LOGBRUSH lb= {BS_SOLID, text_[selection_].bkgnd, 0L};
		//		HBRUSH hbr= CreateBrushIndirect(&lb);
		dc->SelectObject(&text_[selection_].font);
		dc->SetTextColor(text_[selection_].text);
		dc->SetBkColor(text_[selection_].bkgnd);
		return text_[selection_].brush;
	}

	return CPropertyPage::OnCtlColor(dc, wnd, ctl_color);
}


BOOL COptionsViewPage::OnSetActive()
{
	CListBox *list= (CListBox *)GetDlgItem(IDC_OPT_VIEW_WND);

	if (!subclassed_)
	{
		rgb_text_col_ = text_[selection_].text;
		rgb_bkgnd_col_ = text_[selection_].bkgnd;
		color_button_text_.SubclassDlgItem(IDC_OPT_VIEW_TXT_COL,this);
		color_button_text_.SetColorRef(&rgb_text_col_);
		color_button_bkgnd_.SubclassDlgItem(IDC_OPT_VIEW_BKGND_COL,this);
		color_button_bkgnd_.SetColorRef(&rgb_bkgnd_col_);
		subclassed_ = TRUE;
	}

	if (list && list->GetCount() <= 0)
	{
		CString str;
		str.LoadString(IDS_OPT_VIEW_LIST);
		for (TCHAR *start= str.GetBuffer(0); ; )
		{
			TCHAR *lim= _tcschr(start,_T(';'));
			if (lim == NULL)
				break;
			*lim = 0;
			list->AddString(start);
			start = lim + 1;
		}
		str.ReleaseBuffer();
		list->SetCurSel(0);
		OnSelchangeViewWnd();
	}

	return CPropertyPage::OnSetActive();
}


void COptionsViewPage::OnSelchangeViewWnd()
{
	CListBox *list= (CListBox *)GetDlgItem(IDC_OPT_VIEW_WND);
	if (list == NULL)
		return;
	int sel= list->GetCurSel();
	if (sel < 0)
		return;
	selection_ = sel;
	CString text;
	text.LoadString(IDS_OPT_VIEW_EXAMPLE_1 + sel);
	SetDlgItemText(IDC_OPT_VIEW_EXAMPLE,text);
	rgb_text_col_ = text_[selection_].text;
	rgb_bkgnd_col_ = text_[selection_].bkgnd;
	color_button_text_.Invalidate();
	color_button_bkgnd_.Invalidate();
	LOGFONT lf;
	text_[selection_].font.GetLogFont(&lf);
	SetDlgItemText(IDC_OPT_VIEW_FONT_NAME,lf.lfFaceName);
}


void COptionsViewPage::OnViewTxtCol()
{
	CColorDialog dlg(rgb_text_col_,CC_FULLOPEN);
	if (dlg.DoModal() == IDOK && rgb_text_col_ != dlg.GetColor())
	{
		rgb_text_col_ = dlg.GetColor();
		text_[selection_].text = rgb_text_col_;
		text_[selection_].changed = TRUE;
		color_button_text_.Invalidate();
		repaint_example();
	}
}


void COptionsViewPage::OnViewBkgndCol()
{
	CColorDialog dlg(rgb_bkgnd_col_,CC_FULLOPEN);
	if (dlg.DoModal() == IDOK && rgb_bkgnd_col_ != dlg.GetColor())
	{
		rgb_bkgnd_col_ = dlg.GetColor();
		text_[selection_].bkgnd = rgb_bkgnd_col_;
		text_[selection_].changed |= 1;		// zmieniony kolor
		color_button_text_.Invalidate();
		repaint_example();
	}
}


void COptionsViewPage::repaint_example()
{
	HWND wnd;
	GetDlgItem(IDC_OPT_VIEW_EXAMPLE,&wnd);
	::InvalidateRect(wnd,NULL,TRUE);
}


void COptionsViewPage::OnViewFontBtn()
{
	LOGFONT lf;
	text_[selection_].font.GetLogFont(&lf);
	CFontDialog fnt(&lf, CF_SCREENFONTS | //CF_FIXEDPITCHONLY |
		CF_INITTOLOGFONTSTRUCT | CF_FORCEFONTEXIST | CF_SCRIPTSONLY);

	if (fnt.DoModal() == IDOK)
	{
		text_[selection_].font.DeleteObject();
		text_[selection_].font.CreateFontIndirect(&fnt.m_lf);
		SetDlgItemText(IDC_OPT_VIEW_FONT_NAME,fnt.m_lf.lfFaceName);
		text_[selection_].changed |= 2;		// zmieniony font
		repaint_example();
	}
}
