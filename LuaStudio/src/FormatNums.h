/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#ifndef _format_nums_
#define _format_nums_


class CFormatNums
{
public:
  enum NumFmt { NUM_ERR, NUM_DEC, NUM_HEX_0X, NUM_HEX_DOL };

  int ReadNumber(CWnd *ctrl, NumFmt &fmt);
  void SetNumber(CWnd *ctrl, int num, NumFmt fmt);
  void IncEditField(CWnd *ctrl, int iDelta, int iMin, int iMax);
};


#endif
