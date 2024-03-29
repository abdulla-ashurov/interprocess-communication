#ifndef __DETAILS_HPP__
#define __DETAILS_HPP__

#include "Windows.h"

namespace details {
	SECURITY_ATTRIBUTES security_attr(const bool inherit_handle) {
		return SECURITY_ATTRIBUTES{
			sizeof(SECURITY_ATTRIBUTES),	// nLength
			NULL,					     	// lpSecurityDescriptor
			inherit_handle			     	// bInheritHandle
		};
	}

	HANDLE create_file_mapping(const size_t size) {
		return CreateFileMapping(
			INVALID_HANDLE_VALUE,	// hFile
			NULL,					// lpFileMappingAttributes
			PAGE_READWRITE,			// flProtect
			0,						// dwMaximumSizeHigh
			size,					// dwMaximumSizeLow
			NULL					// lpName
		);
	}

	HANDLE create_inherited_file_mapping(const size_t size) {
		SECURITY_ATTRIBUTES sa = security_attr(true);
		return CreateFileMapping(
			INVALID_HANDLE_VALUE,		// hFile
			&sa,						// lpFileMappingAttributes
			PAGE_READWRITE,				// flProtect
			0,							// dwMaximumSizeHigh
			size,						// dwMaximumSizeHigh
			NULL						// lpName
		);
	}

	void* map_view_of_file(HANDLE f_map, const size_t size) {
		return MapViewOfFile(
			f_map,					// hFileMappingObject
			FILE_MAP_ALL_ACCESS,	// dwDesiredAccess
			0,						// dwFileOffsetHigh
			0,						// dwFileOffsetLow
			size					// dwNumberOfBytesToMap
		);
	}

	bool create_process(const char *cmd, PROCESS_INFORMATION& pi) {
		STARTUPINFO si;
		return CreateProcessA(
			NULL,								// lpApplicationName
			const_cast<LPSTR>(cmd),				// lpCommandLine
			NULL,								// lpProcessAttributes
			NULL,								// lpThreadAttributes
			false,								// bInheritHandles
			NULL,								// dwCreationFlags
			NULL,								// lpEnvironment
			NULL,								// lpCurrentDirectory
			&si,								// lpStartupInfo
			&pi									// lpProcessInformation
		);
	}

	bool create_process(const wchar_t *cmd, PROCESS_INFORMATION& pi) {
		STARTUPINFOW si;
		return CreateProcessW(
			NULL,								// lpApplicationName
			const_cast<LPWSTR>(cmd),			// lpCommandLine
			NULL,								// lpProcessAttributes
			NULL,								// lpThreadAttributes
			false,								// bInheritHandles
			NULL,								// dwCreationFlags
			NULL,								// lpEnvironment
			NULL,								// lpCurrentDirectory
			&si,								// lpStartupInfo
			&pi									// lpProcessInformation
		);
	}

	bool create_inherited_process(const char *cmd, PROCESS_INFORMATION &pi) {
		STARTUPINFO si = { sizeof(si) };
		SECURITY_ATTRIBUTES sa = security_attr(true);
		return CreateProcessA(
			NULL,								// lpApplicationName
			const_cast<LPSTR>(cmd),				// lpCommandLine
			&sa,								// lpProcessAttributes
			&sa,								// lpThreadAttributes
			true,								// bInheritHandles
			NULL,								// dwCreationFlags
			NULL,								// lpEnvironment
			NULL,								// lpCurrentDirectory
			&si,								// lpStartupInfo
			&pi									// lpProcessInformation
		);
	}

	bool create_inherited_process(const wchar_t *cmd, PROCESS_INFORMATION &pi) {
	STARTUPINFOW si = { sizeof(si) };
	SECURITY_ATTRIBUTES sa = security_attr(true);
	return CreateProcessW(
		NULL,								// lpApplicationName
		const_cast<LPWSTR>(cmd),			// lpCommandLine
		&sa,								// lpProcessAttributes
		&sa,								// lpThreadAttributes
		true,								// bInheritHandles
		NULL,								// dwCreationFlags
		NULL,								// lpEnvironment
		NULL,								// lpCurrentDirectory
		&si,								// lpStartupInfo
		&pi									// lpProcessInformation
		);
	}

	int format_message(const int err_code, char *err_msg) {
		return FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,				// dwFlags
			NULL,										// lpSource
			err_code,									// dwMessageId
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),	// dwLanguageId
			err_msg,									// lpBuffer
			0,											// nSize
			NULL										// arguments
		);
	}

	// Free the buffer allocated by format_message
	void local_free(char *buffer) {
		if (buffer) {
			LocalFree(buffer);
		}
	}

	void checked_close_handle(HANDLE h) {
		if (h) {
			CloseHandle(h);
		}
	}

	void checked_unmap_view_of_file(void *buffer) {
		if (buffer) {
			UnmapViewOfFile(buffer);
		}
	}
}

#endif // __DETAILS_HPP__
