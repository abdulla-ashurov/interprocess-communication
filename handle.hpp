#ifndef __HANDLE_HPP__
#define __HANDLE_HPP__

#include "Windows.h"

#include "detials.hpp"

class UniqueHandle {
private:
	HANDLE m_handle;

public:
	UniqueHandle() : m_handle(NULL) {}
	UniqueHandle(HANDLE h) : m_handle(h) {}

	~UniqueHandle() {
		details::checked_close_handle(h);
	}

public:
	UniqueHandle(const UniqueHandle& other) = delete;
	UniqueHandle& operator=(const UniqueHandle& other) = delete;
	UniqueHandle& operator=(HANDLE h) {
		if (m_handle != h) {
			details::checked_close_handle(h);
			m_handle = h;
		}

		return *this;
	}

public:
	HANDLE get() {
		return m_handle;
	}
};

#endif // __HANDLE_HPP__
