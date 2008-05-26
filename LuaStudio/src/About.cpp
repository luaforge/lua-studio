/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#include "StdAfx.h"
#include "About.h"


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* DX)
{
	CDialog::DoDataExchange(DX);

	DDX_Control(DX, IDC_TITLE, title_ctrl_);
	DDX_Text(DX, IDC_ABOUT_VER, version_string_);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
  ON_WM_ERASEBKGND()
  ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



BOOL CAboutDlg::OnInitDialog()
{
	if (HRSRC rsrc= ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION))
		if (HGLOBAL global = ::LoadResource(AfxGetResourceHandle(), rsrc))
		{
			VS_FIXEDFILEINFO* ver= (VS_FIXEDFILEINFO *)((char *)::LockResource(global) + 0x28);
			if (ver->dwSignature == 0xfeef04bd)
				version_string_.Format(IDS_ABOUT_VER,
				(int)HIWORD(ver->dwProductVersionMS), (int)LOWORD(ver->dwProductVersionMS),
				(int)HIWORD(ver->dwProductVersionLS), (int)LOWORD(ver->dwProductVersionLS));

			::FreeResource(global);
		}

	about_.Attach(::LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_ABOUT), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION));

	CDialog::OnInitDialog();

	LOGFONT lf;
	title_ctrl_.GetFont()->GetLogFont(&lf);

	GetFont()->GetLogFont(&lf);
	//  CClientDC dc(this);
	//    lf.lfHeight = -MulDiv(9, dc.GetDeviceCaps(LOGPIXELSY), 96);
	lf.lfWeight = 700;      // bold
	lf.lfHeight -= 2;		// larger
	title_font_.CreateFontIndirect(&lf);
	title_ctrl_.SetFont(&title_font_);

	web_page_link_.SubclassDlgItem(IDC_LINK, this, "http://lua-studio.luaforge.net");
	lua_org_link_.SubclassDlgItem(IDC_LINK_LUA, this, "http://www.lua.org/");

	return true;
}


BOOL CAboutDlg::OnEraseBkgnd(CDC* dc)
{
	CRect rect(0,0,0,0);
	GetClientRect(rect);

	dc->FillSolidRect(rect, RGB(255,255,255));	// white to match image

	// bitmap (x, y) location in the dialog
	CPoint pos(180, 40);

	DIBSECTION bmp;
	if (about_.m_hObject && about_.GetObject(sizeof bmp, &bmp) && bmp.dsBm.bmBits)
	{
		dc->SetStretchBltMode(COLORONCOLOR);

		::StretchDIBits(*dc, pos.x, pos.y, bmp.dsBm.bmWidth, bmp.dsBm.bmHeight,
			0, 0, bmp.dsBm.bmWidth, bmp.dsBm.bmHeight, bmp.dsBm.bmBits,
			reinterpret_cast<BITMAPINFO*>(&bmp.dsBmih), DIB_RGB_COLORS, SRCCOPY);
	}

	return true;
}


HBRUSH CAboutDlg::OnCtlColor(CDC* dc, CWnd* wnd, UINT ctlColor)
{
	if (wnd == &web_page_link_)
		return web_page_link_.CtlColor(dc, ctlColor);
	else if (wnd == &lua_org_link_)
		return lua_org_link_.CtlColor(dc, ctlColor);
	else
		return static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
}
