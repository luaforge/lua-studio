/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// SyntaxExample.cpp : implementation file
//

#include "stdafx.h"
#include "SyntaxExample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSyntaxExample

CSyntaxExample::CSyntaxExample()
{
	tab_stop_ = 8;
	editor_font_ = 0;

	rgb_background_ = RGB(255,255,255);
	rgb_text_ = rgb_instruction_ = rgb_directive_ =
		rgb_comment_ = rgb_number_ = rgb_string_ = rgb_selection_ = RGB(0,0,0);

	vb_bold_[0] = vb_bold_[1] = vb_bold_[2] = vb_bold_[3] = vb_bold_[4] = false;
}

CSyntaxExample::~CSyntaxExample()
{
}


BEGIN_MESSAGE_MAP(CSyntaxExample, CButton)
	//{{AFX_MSG_MAP(CSyntaxExample)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyntaxExample message handlers

void CSyntaxExample::DrawItem(LPDRAWITEMSTRUCT draw_item_struct)
{
	if (draw_item_struct->itemAction != ODA_DRAWENTIRE)
		return;

	CRect rect;
	GetClientRect(rect);
	CDC* dc= CDC::FromHandle(draw_item_struct->hDC);
	if (dc == 0)
		return;

	//Redraw(dc, draw_item_struct->rcItem, false);
	rect.DeflateRect(1, 1);
	dc->FillSolidRect(rect, rgb_background_);

	static const TCHAR* vszText[]=
	{
		_T("\4; Example code \7snippet"),
		_T("\1IO_PutC\t= \5$e001"),
		_T("\t\3.ORG \5$0600"),
		_T("\t\2LDA\1 #\6'a'"),
		_T("\t\2STA\1 IO_PutC"),
		_T("\1str\t\3.STR \6\"Hello World\""),
		_T("\t\2LDA\1 #>str"),
		_T("\t\2LDX\1 #<str"),
		_T("\t\2JSR\1 PrintS"),
		_T("\t\2BRK"),
		0
	};

	CFont bold_fnt;
	HGDIOBJ old_font= 0;
	if (editor_font_)
	{
		old_font = ::SelectObject(*dc, editor_font_);

		LOGFONT lf;
		if (::GetObject(editor_font_, sizeof lf, &lf))
		{
			lf.lfWeight = FW_BOLD;
			bold_fnt.CreateFontIndirect(&lf);
		}
	}

	int dy= 16;
	int dx= 16;
	TEXTMETRIC tm;
	if (dc->GetTextMetrics(&tm))
	{
		dy = tm.tmHeight + tm.tmInternalLeading + tm.tmExternalLeading;
		dx = tm.tmAveCharWidth;
	}

	dc->SetBkMode(OPAQUE);

	int tab_stop= tab_stop_ ? tab_stop_ : 1;

	int y= rect.top;
	for (const char** ppcszText= vszText; *ppcszText != 0; ++ppcszText)
	{
		const TCHAR* text= *ppcszText;
		int length= _tcslen(text);

		int x= rect.left;
		int idx= 0;
		COLORREF rgb_text= rgb_text_;
		COLORREF rgb_back= rgb_background_;
		HFONT font= editor_font_;
		bool color_change= true;
		for (int i= 0; i < length; ++i)
		{
			TCHAR c= text[i];

			if (c == '\t')
			{
				x += (tab_stop - idx % tab_stop) * dx;
				continue;
			}

			if (c < ' ')	// special control char?
			{
				rgb_back = rgb_background_;
				switch (c)
				{
				case 1: rgb_text = rgb_text_;		font = editor_font_; break;
				case 2: rgb_text = rgb_instruction_;	font = vb_bold_[0] ? bold_fnt : editor_font_; break;
				case 3: rgb_text = rgb_directive_;	font = vb_bold_[1] ? bold_fnt : editor_font_; break;
				case 4: rgb_text = rgb_comment_;		font = vb_bold_[2] ? bold_fnt : editor_font_; break;
				case 5: rgb_text = rgb_number_;		font = vb_bold_[3] ? bold_fnt : editor_font_; break;
				case 6: rgb_text = rgb_string_;		font = vb_bold_[4] ? bold_fnt : editor_font_; break;
				case 7: rgb_back = rgb_selection_;	break;
				default:
					ASSERT(false);
					break;
				}
				color_change = true;
				continue;
			}
			else
				++idx;

			if (color_change)
			{
				if (font)
					::SelectObject(*dc, font);
				dc->SetTextColor(rgb_text);
				dc->SetBkColor(rgb_back);
				color_change = false;
			}

			dc->TextOut(x, y, &c, 1);
			x += dx;
		}

		y += dy;

	}

	if (old_font)
		::SelectObject(*dc, old_font);

	COLORREF rgb_frame= RGB(192,192,192);
	rect.InflateRect(1, 1);
	dc->Draw3dRect(rect, rgb_frame, rgb_frame);
}


BOOL CSyntaxExample::OnEraseBkgnd(CDC* dc)
{
	return true;
}
