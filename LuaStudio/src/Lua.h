#pragma once
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
//#include <boost/function/function1.hpp>
#include <exception>
#include <vector>


typedef std::vector<unsigned char> ProgBuf;


struct lua_exception : public std::exception
{
	lua_exception(const char* msg) : exception(msg)
	{}
};


namespace lua_details
{
	struct State;
}


class Lua : boost::noncopyable
{
public:
	Lua();
	~Lua();

	enum Event { Start, Running, NewLine, Finished };

	void SetCallback(const boost::function<void (Event, int)>& fn);

	// load file (parse, do not execute)
	void LoadFile(const char* file_path);
	bool LoadFile(const char* file_path, const char*& msg);

	// 'load' string
//	bool LoadBuffer(const char* source, const char*& msg);

	// dump current program into the buffer (as executable byte codes)
	void Dump(ProgBuf& program, bool debug);

	// execute
	int Call();

	// execute single line (current one) following calls, if any
	void StepInto();
	// execute current line, without entering any functions
	void StepOver();
	// start execution (it runs in a thread)
	void Run();
	// run till return from the current function
	void StepOut();

	std::string Status() const;

	bool IsRunning() const;		// is Lua program running now? (if not, maybe it stopped at the breakpoint)
	bool IsFinished() const;	// has Lua program finished execution?
	bool IsStopped() const;		// if stopped, it can be resumed (if not stopped, it's either running or done)

	// toggle breakpoint in given line
	bool ToggleBreakpoint(int line);

	// stop running program
	void Break();

	// get current call stack
	std::string GetCallStack() const;

	enum ValType { None= -1, Nil, Bool, LightUserData, Number, String, Table, Function, UserData, Thread };

	struct Value	// value on a virtual stack or elsewhere
	{
		Value() : type(None), type_name(0)
		{}

		ValType type;
		const char* type_name;
		std::string value;	// simplified string representation of value
	};

	struct Var
	{
		std::string name;	// variable's identifier
		Value v;
	};

	// get local vars of function at given 'level'
	bool GetLocalVars(std::vector<Var>& out, int level= 0) const;

	struct Field	// table entry
	{
		Value key;
		Value val;
	};

	typedef std::vector<Field> TableInfo;

	// get global vars
	bool GetGlobalVars(TableInfo& out, bool deep) const;

	typedef std::vector<Value> ValueStack;

	// read all values off virtual value stack
	bool GetValueStack(ValueStack& stack) const;

	struct StackFrame
	{
		StackFrame();
		void Clear();
		const char* SourcePath() const;

		enum Entry { Err, LuaFun, MainChunk, CFun, TailCall } type;
		std::string source;
		std::string name_what;
		int current_line;	// 1..N or 0 if not available
		// where it is defined (Lua fn)
		int line_defined;
		int last_line_defined;
	};
	// 
	typedef std::vector<StackFrame> CallStack;
	
	// get function call stack
	bool GetCallStack(CallStack& stack) const;

	// info about current function and source file (at the top of the stack)
	bool GetCurrentSource(StackFrame& top) const;

private:
	boost::scoped_ptr<lua_details::State> state_;
};
