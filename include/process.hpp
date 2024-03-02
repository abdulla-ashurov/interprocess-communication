#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include "common.hpp"

class BaseProcess {
protected:
	PROCESS_INFORMATION m_pi;

public:
	explicit BaseProcess(const std::wstring &cmd) : m_pi{ NULL } {}

	~BaseProcess() {
		details::checked_close_handle(m_pi.hProcess);
		details::checked_close_handle(m_pi.hThread);
	}

public:
	BaseProcess(const BaseProcess &) = delete;
	BaseProcess& operator=(const BaseProcess &) = delete;

public:
	void detach() {}
	void join() { 
		WaitForSingleObject(m_pi.hProcess, INFINITE); 
	}
};

class Process : public BaseProcess {
public:
	explicit Process(const std::wstring &cmd) : BaseProcess(cmd) {
		create_process(cmd, m_pi);
	}
};

class InheritedProcess : public BaseProcess {
public:
	explicit InheritedProcess(const std::wstring &cmd) : BaseProcess(cmd) {
		create_inherited_process(cmd, m_pi);
	}
};

#endif // __PROCESS_HPP__
