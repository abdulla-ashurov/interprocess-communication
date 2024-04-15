#ifndef __HANDLE_HPP__
#define __HANDLE_HPP__

#include "Windows.h"

#include "details.hpp"

class UniqueHandle {
private:
	HANDLE m_handle;

public:
	explicit UniqueHandle() : m_handle(nullptr) {}
	explicit UniqueHandle(HANDLE h) : m_handle(h) {}

	~UniqueHandle() {
		details::checked_close_handle(m_handle);
	}

public:
	UniqueHandle(const UniqueHandle &) = delete;	
	UniqueHandle(UniqueHandle &&r) : m_handle(r.m_handle) {
		r.m_handle = nullptr;
	}

	UniqueHandle& operator=(const UniqueHandle &) = delete;
	UniqueHandle& operator=(UniqueHandle &&r) {
		if (this != &r) {
			details::checked_close_handle(m_handle);
			m_handle = r.m_handle;
			r.m_handle = nullptr;
		}

		return *this;
	}

public:
	HANDLE handle() { return m_handle; }
};

#endif // __HANDLE_HPP__
