/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#include "stdafx.h"
#include "FormatNums.h"


void CFormatNums::IncEditField(CWnd *ctrl, int iDelta, int iMin, int iMax)
{
  int num,old;
  NumFmt fmt;

  old = num = ReadNumber(ctrl,fmt);

  num += iDelta;
  if (num > iMax)
    num = iMax;
  else if (num < iMin)
    num = iMin;
  if (num != old)
    SetNumber(ctrl,num,fmt);
}


int CFormatNums::ReadNumber(CWnd *ctrl, NumFmt &fmt)
{
  TCHAR buf[32];
  int num= 0;
  if (ctrl==NULL)
    return num;

  ctrl->GetWindowText(buf,sizeof(buf)/sizeof(buf[0]));
  if (buf[0]==_T('$'))
  {
    fmt = NUM_HEX_DOL;
    if (sscanf(buf+1, _T("%X"),&num) <= 0)
      ;
  }
  else if (buf[0]==_T('0') && (buf[1]==_T('x') || buf[1]==_T('X')))
  {
    fmt = NUM_HEX_0X;
    if (sscanf(buf+2, _T("%X"),&num) <= 0)
      ;
  }
  else if (buf[0]>=_T('0') && buf[0]<=_T('9'))
  {
    fmt = NUM_DEC;
    if (sscanf(buf, _T("%d"),&num) <= 0)
      ;
  }
  else
    fmt = NUM_ERR;

  return num;
}


void CFormatNums::SetNumber(CWnd *ctrl, int num, NumFmt fmt)
{
  TCHAR buf[32];

  buf[0] = 0;

  switch (fmt)
  {
    case NUM_ERR:
    case NUM_HEX_0X:
      wsprintf(buf,_T("0x%04X"),num);
      break;
    case NUM_HEX_DOL:
      wsprintf(buf,_T("$%04X"),num);
      break;
    case NUM_DEC:
      wsprintf(buf,_T("%d"),num);
      break;
    default:
      ASSERT(FALSE);
  }

  if (ctrl)
  {
    ctrl->SetWindowText(buf);
    ctrl->UpdateWindow();
  }
}
