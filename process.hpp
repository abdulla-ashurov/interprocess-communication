#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include <iostream>
#include <string>

#include "Windows.h"

#include "common.hpp"

class BaseProcess {
protected:
	PROCESS_INFORMATION m_pi;

public:
	BaseProcess(const std::wstring& cmd) : m_pi{ NULL } {}

	~BaseProcess() {
		details::checked_close_handle(m_pi.hProcess);
		details::checked_close_handle(m_pi.hThread);
	}

public:
	BaseProcess(const BaseProcess& other) = delete;
	BaseProcess& operator=(const BaseProcess& other) = delete;

public:
	void detach() {}
	void join() { WaitForSingleObject(m_pi.hProcess, INFINITE); }
};

class Process : public BaseProcess {
public:
	Process(const std::wstring& cmd) {
		create_process(cmd, m_pi);
	}
};

class InheritedProcess : public BaseProcess {
public:
	InheritedProcess(const std::wstring& cmd) {
		create_inherited_process(cmd, m_pi);
	}
};

#endif // __PROCESS_HPP__
