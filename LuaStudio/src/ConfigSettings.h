/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#ifndef _config_settings_
#define _config_settings_


struct CConfigSettings
{
  static LOGFONT* const fonts[];	// struktury LOGFONT w ca³ym programie
  static CFont* const cfonts[];	// struktury CFont w ca³ym programie
  static COLORREF* text_color[];
  static COLORREF* bkgnd_color[];
  static COLORREF* color_syntax[];
  static BYTE* syntax_font_style[];
};


#endif
