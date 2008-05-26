/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#ifndef _mark_h_
#define _mark_h_

class CMarkArea
{
  struct Pair
  { int a,b; };
  int start;
  UINT n;
  CArray<Pair,Pair&> arr;

public:

  CMarkArea() : start(-1), n(0)
  { }

  void SetStart(int s)
  { ASSERT(s>=0); start = s; }

  void SetEnd(int end);

  bool IsStartSet()
  { return start != -1; }

  UINT GetSize()
  { return n; }

  bool GetPartition(UINT no, int &a, int &b);

  void Clear()
  {
    start = -1;
    n = 0;
    arr.RemoveAll();
  }
};

#endif
