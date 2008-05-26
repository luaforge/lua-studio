/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

// LogBuffer.h: interface for the CLogBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGBUFFER_H__F7F5D1B0_569C_4E6D_A034_D79FB77DB930__INCLUDED_)
#define AFX_LOGBUFFER_H__F7F5D1B0_569C_4E6D_A034_D79FB77DB930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>

// Logging class: recording consecutive items in the buffer overwriting
// old values

template <class T>
class CLogBuffer
{
public:
	CLogBuffer(int size= 1000)
	{ buffer_.resize(size); head_ = &buffer_[0]; full_ = false; }

	~CLogBuffer() {}

	// record item
	void Record(const T& t)
	{
		*head_++ = t;
		if (head_ > &buffer_.back())
		{
			head_ = &buffer_.front();
			full_ = true;
		}
	}

	// no of items recorded
	int GetCount() const
	{
		return full_ ? buffer_.size() : head_ - &buffer_[0];
	}

	// get n-th item
	const T& operator [] (int index) const
	{
		ASSERT(index >= 0 && index < GetCount());
		const T* start= full_ ? head_ : &buffer_.front();
		start += index;
		if (start > &buffer_.back())
			return start[0 - buffer_.size()];
		else
			return *start;
	}

	// empty buffer
	void Clear()
	{
		head_ = &buffer_.front();
		full_ = false;
	}

private:
	std::vector<T> buffer_;
	T* head_;
	bool full_;
};

#endif // !defined(AFX_LOGBUFFER_H__F7F5D1B0_569C_4E6D_A034_D79FB77DB930__INCLUDED_)
