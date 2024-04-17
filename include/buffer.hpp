#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include "details.hpp"

class UniqueMapViewBuffer {
private:
	size_t m_size;
	void *m_buffer;

private:
	UniqueMapViewBuffer() : m_size(0), m_buffer(nullptr) {}

public:
	explicit UniqueMapViewBuffer(const size_t size, void *buffer) 
		: m_size(size), m_buffer(buffer) {}

	~UniqueMapViewBuffer() {
		release();
	}

public:
	UniqueMapViewBuffer(const UniqueMapViewBuffer &) = delete;
	UniqueMapViewBuffer& operator=(const UniqueMapViewBuffer &) = delete;

public:
	UniqueMapViewBuffer(UniqueMapViewBuffer &&r) : UniqueMapViewBuffer()  {
		std::swap(this->m_size, r.m_size);
		std::swap(this->m_buffer, r.m_buffer);
	}

	UniqueMapViewBuffer& operator=(UniqueMapViewBuffer &&r) {
		if (this != &r) {
			release();
			std::swap(this->m_size, r.m_size);
			std::swap(this->m_buffer, r.m_buffer);
		}
		return *this;
	}

public:
	size_t size() const {  return m_size; }

	void* begin() { return m_buffer; }
	void* end() { return static_cast<uint8_t*>(m_buffer) + m_size; }

private:
	void release() {
		details::checked_unmap_view_of_file(m_buffer);
		m_buffer = nullptr;
		m_size = 0;
	}
};

#endif // __BUFFER_HPP__
