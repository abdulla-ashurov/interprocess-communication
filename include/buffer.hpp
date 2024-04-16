#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include "Windows.h"

#include "details.hpp"

template <size_t m_size>
class UniqueMapViewBuffer {
private:
	void *m_buffer;

private:
	UniqueMapViewBuffer() : m_size(0), m_buffer(nullptr) {}

public:
	explicit UniqueMapViewBuffer(void *buffer) : m_buffer(buffer) {}

	~UniqueMapViewBuffer() {
		release();
	}

public:
	UniqueMapViewBuffer(const UniqueMapViewBuffer &) = delete;
	UniqueMapViewBuffer& operator=(const UniqueMapViewBuffer &) = delete;
	
	UniqueMapViewBuffer(UniqueMapViewBuffer &&r) : UniqueMapViewBuffer()  {
		swap(*this, r);
	}

	UniqueMapViewBuffer& operator=(UniqueMapViewBuffer &&r) {
		move(r);
		return *this;
	}

public:
	void move(UniqueMapViewBuffer &&other) {
		if (*this != other) {
			release();
			swap(*this, r);
		}
	}

	size_t size() const {  return m_size; }

	void* begin() { return m_buffer; }
	void* end() { return static_cast<uint8_t*>(m_buffer) + m_size; }

	friend void swap(UniqueMapViewBuffer<m_size> &, UniqueMapViewBuffer<m_size> &);

private:
	void release() {
		details::checked_unmap_view_of_file(m_buffer);
		m_size = 0;
	}
};


template<size_t m_size>
void swap(UniqueMapViewBuffer<m_size> &first, UniqueMapViewBuffer<m_size> &second) {
	std::swap(first.m_size, second.m_size);
	std::swap(first.m_buffer, second.m_buffer);
}

#endif // __BUFFER_HPP__
