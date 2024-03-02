#ifndef __FILE_MAPPING_HPP_
#define __FILE_MAPPING_HPP__

#include <Windows.h>

#include "handle.hpp"
#include "buffer.hpp"
#include "common.hpp"
#include "exceptions.hpp"

template<size_t m_size>
class BaseFileMapping {
protected:
	UniqueHandle m_hFileMap;
	UniqueMapViewBuffer m_buffer;

public:
	BaseFileMapping() {}
	BaseFileMapping(HANDLE hFileMap) : m_hFileMap(hFileMap) {
		m_buffer = map_view_of_file(m_hFileMap.get(), m_size);
	}
	virtual ~BaseFileMapping() = 0;

public:
	size_t size() const { return m_size; }
	HANDLE handle() { return m_hFileMap.get(); }
	void* begin() { return m_buffer.begin(); }
	void* end() { return static_cast<uint8_t*>(m_buffer.begin()) + m_size; }
};

class UniqueFileMapping : public BaseFileMapping<size_t> {
public:
	UniqueFileMapping() : BaseFileMapping() {
		m_hFileMap = create_file_mapping(m_size);
		m_buffer = map_view_of_file(m_hFileMap.get(), m_size);
	}
	UniqueFileMapping(HANDLE hFileMap) : BaseFileMapping(hFileMap) {}

	UniqueFileMapping(const UniqueFileMapping& other) = delete;
	UniqueFileMapping& operator=(const UniqueFileMapping& other) = delete;
};

class UniqueInheritedFileMapping : public BaseFileMapping<size_t> {
public:
	UniqueInheritedFileMapping() {
		m_hFileMap = create_inherited_file_mapping(m_size);
		m_buffer = map_view_of_file(m_hFileMap.get(), m_size);
	}
	UniqueInheritedFileMapping(HANDLE hFileMap) : BaseFileMapping(hFileMap) {}

	UniqueInheritedFileMapping(const UniqueInheritedFileMapping& other) = delete;
	UniqueInheritedFileMapping& operator=(const UniqueInheritedFileMapping& other) = delete;
}

#endif // __FILE_MAPPING_HPP__
