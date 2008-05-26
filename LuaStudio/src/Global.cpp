/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#include "StdAfx.h"
#include "Global.h"
#include "Broadcast.h"
#include <io.h>
#include <fcntl.h>


CGlobal::CGlobal()
{
	debugger_.reset(new Debugger());

	// redirect 'stdout' to the pipe

	char path[MAX_PATH];
	::GetTempPath(MAX_PATH, path);
	char temp[MAX_PATH];
	::GetTempFileName(path, "lu-", ::GetTickCount(), temp);

	// open stdout first, or else dup2 won't work
	if (freopen(temp, "w", stdout) == 0)
		throw std::exception("error redirecting stdout to temp file");

	if (_pipe(stdout_fds_, 0, _O_BINARY) != 0 || _dup2(stdout_fds_[1], _fileno(stdout)) != 0)
		throw std::exception("error redirecting stdout to the pipe");

	// no buffering for stdout, to make output window refresh instant
	setvbuf(stdout, NULL, _IONBF, 0);

	//TODO: delete temp
	::DeleteFile(temp);

	output_position_ = 0;
	output_.reserve(200);

	thread_ = ::AfxBeginThread(ReadStdoutText, this, 0, 0, CREATE_SUSPENDED);
	if (thread_ == 0)
		throw std::exception("cannot create worker thread");
	thread_->m_bAutoDelete = false;
	thread_->ResumeThread();
}


CGlobal::~CGlobal()
{
	//TODO: close the pipe without hanging
	//_close(stdout_fds_[0]);
	//_close(stdout_fds_[1]);

//	::WaitForSingleObject(thread_, 10);
	thread_->ExitInstance();
}

// worker thread sitting on a pipe and reading redirected 'stdout' text
UINT AFX_CDECL CGlobal::ReadStdoutText(LPVOID self)
{
	CGlobal* obj= static_cast<CGlobal*>(self);

	for (;;)
	{
		const size_t chunk= 1024;
		char buf[chunk];
		int len= _read(obj->stdout_fds_[0], buf, chunk);

		if (len == -1)
			break;

		obj->BufferOutput(buf, len);
	}

	return 0;
}


void CGlobal::BufferOutput(const char* buf, int len)
{
	if (len <= 0)
		return;

	CSingleLock lock(&lock_output_, true);

	output_.insert(output_.end(), buf, buf + len);

	lock.Unlock();

	// notify clients

	CBroadcast::SendMessageToPopups(CBroadcast::WM_APP_OUTPUT);
}


void CGlobal::GetOutput(std::vector<char>& out)
{
	CSingleLock lock(&lock_output_, true);

	if (output_position_ > output_.size())
	{
		ASSERT(false);
		output_position_ = output_.size();
	}

	out.assign(output_.begin() + output_position_, output_.end());

	output_position_ = output_.size();
}


void CGlobal::ClearOutput()
{
	CSingleLock lock(&lock_output_, true);

	output_position_ = 0;
	output_.clear();

	lock.Unlock();

	CBroadcast::SendMessageToPopups(CBroadcast::WM_APP_OUTPUT);
}

//-----------------------------------------------------------------------------

Debugger& CGlobal::GetDebugger() const
{
	return *debugger_;
}
