/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// Proste wzorce stosów


template <class T> class CPtrStack : public CTypedPtrList< CObList, T* >
{
public:
  // Add element to top of stack
  void Push( T* newT )
  { AddHead( newT ); }

  // Peek at top element of stack
  T* Peek()
  { return IsEmpty() ? NULL : GetHead(); }

  // Pop top element off stack
  T* Pop()
  { return RemoveHead(); }

  void RemoveAll()
  { RemoveAll(); }
};



template <class T> class CStack : public CList< T, T >
{
public:
  // Add element to top of stack
  void Push( T newT )
  { AddHead( newT ); }

  // Peek at top element of stack
  T Peek()
  { return IsEmpty() ? NULL : GetHead(); }

  // Pop top element off stack
  T Pop()
  { return RemoveHead(); }

  void RemoveAll()
  { RemoveAll(); }
};
