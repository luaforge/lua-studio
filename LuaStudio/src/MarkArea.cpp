/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/


#include "StdAfx.h"
#include "MarkArea.h"


void CMarkArea::SetEnd(int end)
{
  ASSERT(start >= 0);		// przed 'SetEnd' musi byæ wywo³ane 'SetStart'
  ASSERT(end >= start);		// b³êdne krañce przedzia³ów
  if (end < start)		// b³êdne krañce przedzia³ów?
    return;

  Pair pair= {start,end};
  for (UINT i=0; i<n; i++)
  {
    if (arr[i].a > end || arr[i].b < start)
      continue;			// przedzia³y roz³¹czne
    if (arr[i].a <= start)
      if (arr[i].b >= end)
	return;			// nowa para mieœci siê w przedziale
      else
      {
	arr[i].b = end;		// przesuniêcie koñca przedzia³u
	return;
      }
    else if (arr[i].b <= end)
    {
      arr[i].a = start;		// przesuniêcie pocz¹tku przedzia³u
      return;
    }
    else
    {
      arr[i].a = start;		// poszerzenie ca³ego przedzia³u
      arr[i].b = end;
      return;
    }
  }
  arr.SetAtGrow(n,pair);
  n++;
}


bool CMarkArea::GetPartition(UINT no, int &a, int &b)
{
  if (no >= n)
    return FALSE;
  a = arr[no].a;
  b = arr[no].b;
  return true;
}
