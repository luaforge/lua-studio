/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/


#include "stdafx.h"
#include "M6502.h"
#include "DialAsmStat.h"


class CInputWnd : CWnd
{
  void open(const CString &fname);
  void close();
  void seek_to_begin();
  LPTSTR read_line(LPTSTR str, UINT max_len);
  int get_line_no();
  const CString &get_file_name();
};


LPTSTR CInputWnd::read_line(LPTSTR str, UINT max_len)
{
  int ret= SendMessage(WM_USER_GET_NEXT_LINE, WPARAM(max_len), LPARAM(str));
  ASSERT(ret);
  return str;
}


int CInputWnd::get_line_no()
{
  int no;
  int ret= SendMessage(WM_USER_GET_LINE_NO, 0, LPARAM(&no));
  ASSERT(ret);
  return no;
}


const CString &CInputWnd::get_file_name()
{
  CString fname;
  int ret= SendMessage(WM_USER_GET_TITLE, WPARAM(_MAX_PATH), LPARAM(fname.GetBuffer(_MAX_PATH+1)));
  fname.ReleaseBuffer();
  ASSERT(ret);
  return fname;
}
