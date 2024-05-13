#ifndef __HANDLE_HPP__
#define __HANDLE_HPP__

#include "details.hpp"

class UniqueHandle {
private:
	HANDLE m_handle;

private:
	UniqueHandle() : m_handle(nullptr) {}

public:
	explicit UniqueHandle(HANDLE h) : m_handle(h) {}

	~UniqueHandle() {
		details::checked_close_handle(m_handle);
	}

public:
	UniqueHandle(const UniqueHandle &) = delete;
	UniqueHandle& operator=(const UniqueHandle &) = delete;

public:
	UniqueHandle(UniqueHandle &&r) : UniqueHandle() {
		swap(*this, r);
	}

	UniqueHandle& operator=(UniqueHandle &&r) {
		if (this != &r) {
			details::checked_close_handle(m_handle);
			swap(*this, r);
		}

		return *this;
	}

public:
	HANDLE handle() { return m_handle; }

	friend void swap(UniqueHandle &, UniqueHandle &);
};

void swap(UniqueHandle &first, UniqueHandle &second) {
	std::swap(first.m_handle, second.m_handle);
}

#endif // __HANDLE_HPP__
