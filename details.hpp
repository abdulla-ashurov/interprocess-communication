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
		return CreateFileMapping(
			INVALID_HANDLE_VALUE,		// hFile
			security_attr(true),		// lpFileMappingAttributes
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

	bool create_process(const std::wstring& cmd, PROCESS_INFORMATION& pi) {
		STARTUPINFO si;
		return CreateProcess(
			NULL,								// lpApplicationName
			const_cast<LPWSTR>(cmd.c_str()),	// lpCommandLine
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

	bool create_inherited_process(const std::wstring& cmd, PROCESS_INFORMATION& pi) {
		STARTUPINFO si = { sizeof(si) };
		SECURITY_ATTRIBUTES sa = create_security_attr(true);
		return CreateProcess(
			NULL,								// lpApplicationName
			const_cast<LPWSTR>(cmd.c_str()),	// lpCommandLine
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

	int format_message(const int err_code, char* errMsg) {
		return FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,				// dwFlags
			NULL,										// lpSource
			err_code,									// dwMessageId
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),	// dwLanguageId
			&errMsg,									// lpBuffer
			0,											// nSize
			NULL										// arguments
		);
	}

	// Free the buffer allocated by format_message
	void local_free(char* buffer) {
		if (buffer) {
			LocalFree(buffer);
		}
	}

	void checked_close_handle(HANDLE h) {
		if (h) {
			CloseHandle(h);
		}
	}

	void checked_unmap_view_of_file(void* buffer) {
		if (buffer) {
			UnmapViewOfFile(buffer);
		}
	}
}

#endif // __DETAILS_HPP__
