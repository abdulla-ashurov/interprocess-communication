#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <string>

#include "handle.hpp"
#include "buffer.hpp"
#include "details.hpp"
#include "exceptions.hpp"

SECURITY_ATTRIBUTES create_security_attr(const bool inherit_handle = false) {
	return details::security_attr(inherit_handle);
}

UniqueHandle create_file_mapping(const size_t size) {
	HANDLE hFileMap = details::create_file_mapping(size);
	if (hFileMap == NULL) {
		throw FileMappingException("Cannot create file mapping object");
	}

	return UniqueHandle(hFileMap);
}

UniqueHandle create_inherited_file_mapping(const size_t size) {
	HANDLE hFileMap = details::create_inherited_file_mapping(size);
	if (hFileMap == NULL) {
		throw FileMappingException("Cannot create inherited file mapping object");
	}

	return UniqueHandle(hFileMap);
}

UniqueMapViewBuffer map_view_of_file(UniqueHandle &f_map, const size_t size) {
	void *buffer = details::map_view_of_file(f_map.get(), size);
	if (buffer == NULL) {
		throw FileMappingException("Cannot map view of file");
	}

	return UniqueMapViewBuffer(buffer);
}

void create_process(const std::wstring &cmd, PROCESS_INFORMATION &pi) {
	if (!details::create_process(cmd, pi)) {
		throw ProcessException("Cannot create a new child process");
	}
}

void create_inherited_process(const std::wstring &cmd, PROCESS_INFORMATION &pi) {
	if (!details::create_inherited_process(cmd, pi)) {
		throw ProcessException("Cannot create a new child process with inherited handles");
	}
}

std::string winapi_error_message(const size_t err_code) {
	std::string err_msg;
	char* out_err_msg(NULL);
	if (details::format_message(err_code, out_err_msg)) {
		err_msg = out_err_msg;
	}
	details::local_free(out_err_msg);

	return err_msg;
}

#endif // __COMMON_HPP__
