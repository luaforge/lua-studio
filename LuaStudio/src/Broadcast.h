/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#ifndef _broadcast_
#define _broadcast_


class CBroadcast
{
public:
  enum WinMsg
  {
    WM_USER_OFFSET = WM_APP + 0x100,
    WM_USER_EXIT_DEBUGGER =	WM_USER_OFFSET,
    WM_USER_START_DEBUGGER,
    WM_USER_UPDATE_REG_WND,
    WM_USER_PROG_MEM_CHANGED,
    WM_USER_REMOVE_ERR_MARK,
	WM_USER_NEW_LINE,
	WM_APP_OUTPUT
  };

  static void SendMessageToViews(UINT msg, WPARAM wParam= 0, LPARAM lParam= 0);
  static void SendMessageToPopups(UINT msg, WPARAM wParam= 0, LPARAM lParam= 0);
};

#endif
