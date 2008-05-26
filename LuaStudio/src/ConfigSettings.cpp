/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/


#include "StdAfx.h"
#include "ConfigSettings.h"
#include "IOWindow.h"
#include "ConfigSettings.h"
#include "MainFrm.h"
#include "LuaView.h"



LOGFONT* const CConfigSettings::fonts[]=
{
	&LuaSrcView::log_font_,
	&CIOWindow::log_font_,
	NULL
};

CFont* const CConfigSettings::cfonts[]=	// struktury CFont w ca³ym programie
{
	&LuaSrcView::font_,
	&CIOWindow::font_,
	//&CDeasmView::font_,
	NULL
};

COLORREF* CConfigSettings::text_color[]=
{
	&LuaSrcView::rgb_text_color_,
	&CIOWindow::rgb_text_color_,
	//&CDeasmView::rgb_instr_,
	NULL
};


COLORREF* CConfigSettings::bkgnd_color[]=
{
	&LuaSrcView::rgb_bkgnd_color_,
	&CIOWindow::rgb_backgnd_color_,
	//&CDeasmView::rgb_bkgnd_,
	NULL
};


COLORREF* CConfigSettings::color_syntax[]=
{
	&LuaSrcView::vrgb_color_syntax_[0],
	&LuaSrcView::vrgb_color_syntax_[1],
	&LuaSrcView::vrgb_color_syntax_[2],
	&LuaSrcView::vrgb_color_syntax_[3],
	&LuaSrcView::vrgb_color_syntax_[4],
	&LuaSrcView::vrgb_color_syntax_[5],
	0
};


BYTE* CConfigSettings::syntax_font_style[]=
{
	&LuaSrcView::vby_font_style_[0],
	&LuaSrcView::vby_font_style_[1],
	&LuaSrcView::vby_font_style_[2],
	&LuaSrcView::vby_font_style_[3],
	&LuaSrcView::vby_font_style_[4],
	&LuaSrcView::vby_font_style_[5],
	0
};
