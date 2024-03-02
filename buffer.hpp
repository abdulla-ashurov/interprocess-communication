#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include "Windows.h"

#include "details.hpp"

class UniqueMapViewBuffer {
private:
	void* m_buffer;

public:
	UniqueMapViewBuffer() : m_buffer(NULL) {}
	UniqueMapViewBuffer(void* buffer) : m_buffer(buffer) {}

	~UniqueMapViewBuffer() {
		details::checked_unmap_view_of_file(m_buffer);
	}

public:
	UniqueMapViewBuffer(const MapViewBuffer& other) = delete;
	UniqueMapViewBuffer& operator=(const MapViewBufffer& other) = delete;
	UniqueMapViewBuffer& operator=(void* buffer) {
		if (m_buffer != buffer) {
			details::checked_unmap_view_of_file(m_buffer);
			m_buffer = buffer;
		}

		return *this;
	}

public:
	void* begin() {
		return m_buffer;
	}
};

#endif // __BUFFER_HPP__
