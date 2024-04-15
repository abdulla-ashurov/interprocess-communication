#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include "Windows.h"

#include "details.hpp"

template <size_t m_size>
class UniqueMapViewBuffer {
private:
	void *m_buffer;

public:
	explicit UniqueMapViewBuffer() : m_buffer(nullptr) {}
	explicit UniqueMapViewBuffer(void *buffer) : m_buffer(buffer) {}

	~UniqueMapViewBuffer() {
		details::checked_unmap_view_of_file(m_buffer);
	}

public:
	UniqueMapViewBuffer(const UniqueMapViewBuffer &) = delete;
	UniqueMapViewBuffer(UniqueMapViewBuffer &&r) : m_buffer(r.m_buffer) {
		r.m_buffer = nullptr;
	}

	UniqueMapViewBuffer& operator=(const UniqueMapViewBuffer &) = delete;
	UniqueMapViewBuffer& operator=(UniqueMapViewBuffer &&r) {
		if (this != &r) {
			details::checked_unmap_view_of_file(m_buffer);
			m_buffer = r.m_buffer;
			r.m_buffer = nullptr;
		}

		return *this;
	}

public:
	size_t size() const { return m_size; }
	
	void* begin() { return m_buffer; }
	void* end() { return static_cast<uint8_t*>(m_buffer) + m_size; }
};

#endif // __BUFFER_HPP__
