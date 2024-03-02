#ifndef __FILE_MAPPING_HPP_
#define __FILE_MAPPING_HPP__

#include "common.hpp"

template <size_t m_size>
class BaseFileMapping {
protected:
	UniqueHandle m_hFileMap;
	UniqueMapViewBuffer m_buffer;

public:
	explicit BaseFileMapping() {}
	explicit BaseFileMapping(HANDLE hFileMap) : m_hFileMap(hFileMap) {
		m_buffer = map_view_of_file(m_hFileMap, m_size);
	}
	virtual ~BaseFileMapping() = 0;

public:
	BaseFileMapping(const BaseFileMapping &) = delete;
	BaseFileMapping(BaseFileMapping &&r) 
		: m_hFileMap(std::move(r.m_hFileMap)), m_buffer(std::move(r.m_buffer)) {}

	BaseFileMapping& operator=(const BaseFileMapping &) = delete;
	BaseFileMapping& operator=(BaseFileMapping &&r) {
		m_hFileMap = std::move(r.m_hFileMap);
		m_buffer = std::move(r.m_buffer);

		return *this;
	}

public:
	size_t size() const { return m_size; }
	HANDLE handle() { return m_hFileMap.get(); }
	void* begin() { return m_buffer.begin(); }
	void* end() { return static_cast<uint8_t*>(m_buffer.begin()) + m_size; }
};

template <size_t m_size>
class UniqueFileMapping : public BaseFileMapping<size_t> {
public:
	explicit UniqueFileMapping() : BaseFileMapping() {
		m_hFileMap = create_file_mapping(m_size);
		m_buffer = map_view_of_file(m_hFileMap, m_size);
	}
	explicit UniqueFileMapping(HANDLE hFileMap) : BaseFileMapping(hFileMap) {}

public:
	UniqueFileMapping(const UniqueFileMapping &) = delete;
	UniqueFileMapping(UniqueFileMapping &&r) : BaseFileMapping(r) {}

	UniqueFileMapping& operator=(const UniqueFileMapping &) = delete;
	UniqueFileMapping& operator=(UniqueFileMapping &&r) {
		if (this != &r) {
			BaseFileMapping::operator=(r);
		}

		return *this;
	}
};

template <size_t m_size>
class UniqueInheritedFileMapping : public BaseFileMapping<size_t> {
public:
	explicit UniqueInheritedFileMapping() {
		m_hFileMap = create_inherited_file_mapping(m_size);
		m_buffer = map_view_of_file(m_hFileMap, m_size);
	}
	explicit UniqueInheritedFileMapping(HANDLE hFileMap) : BaseFileMapping(hFileMap) {}

public:
	UniqueInheritedFileMapping(const UniqueInheritedFileMapping &) = delete;
	UniqueInheritedFileMapping(UniqueInheritedFileMapping &&r) : BaseFileMapping(r) {}
	
	UniqueInheritedFileMapping& operator=(const UniqueInheritedFileMapping &) = delete;
	UniqueInheritedFileMapping& operator=(UniqueInheritedFileMapping &&r) {
		if (this != &r) {
			BaseFileMapping::operator=(r);
		}

		return *this;
	}
};

#endif // __FILE_MAPPING_HPP
