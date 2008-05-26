/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// Bezpieczny przydzielacz pamiêci


template<class T> class MemPtr : class CObject
{
  T* ptr;

public:

  MemPtr(size_t size= 1)
  {
    ASSERT(size>0);
    ptr = new T[size];
  }

  ~MemPtr()
  { delete [] ptr; }

  operator T* ()
  { return ptr; }
};
