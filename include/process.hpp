#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include "common.hpp"

class BaseProcess {
protected:
	PROCESS_INFORMATION m_pi;

	explicit BaseProcess(const std::string &cmd) : m_pi{ NULL } {}
	explicit BaseProcess(const std::wstring &cmd) : m_pi{ NULL } {}

	~BaseProcess() {
		details::checked_close_handle(m_pi.hThread);
		details::checked_close_handle(m_pi.hProcess);
	}

public:
	void detach() {}
	void join() { 
		WaitForSingleObject(m_pi.hProcess, INFINITE); 
	}
};

class Process : public BaseProcess {
public:
	explicit Process(const std::string &cmd) : BaseProcess(cmd) {
		create_process(cmd, m_pi);
	}
	explicit Process(const std::wstring &cmd) : BaseProcess(cmd) {
		create_process(cmd, m_pi);
	}
};

class InheritedProcess : public BaseProcess {
public:
	explicit InheritedProcess(const std::string &cmd) : BaseProcess(cmd) {
		create_inherited_process(cmd, m_pi);
	}
	explicit InheritedProcess(const std::wstring &cmd) : BaseProcess(cmd) {
		create_inherited_process(cmd, m_pi);
	}
};

#endif // __PROCESS_HPP__
