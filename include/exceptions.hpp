#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include "common.hpp"

class BaseWinApiException {
private:
	int m_err_code;
public:
	explicit BaseWinApiException(const int err_code) : m_err_code(err_code) {}

	std::string what() const {
		return error_message(m_err_code);
	}
};

class FileMappingException : public std::exception {
public:
	explicit FileMappingException() : std::exception() {}
	explicit FileMappingException(const char *err_msg) : std::exception(err_msg) {}

	const char* what() const {
		std::string base_err_msg(std::exception::what());
		std::string detailed_err_msg(BaseWinApiException(GetLastError()).what());
		return (base_err_msg + "\n" + detailed_err_msg).c_str();
	}
};

class ProcessException : public std::exception {
public:
	explicit ProcessException() : std::exception() {}
	explicit ProcessException(const char *err_msg) : std::exception(err_msg) {}

	const char* what() const {
		std::string base_err_msg(std::exception::what());
		std::string detailed_err_msg(BaseWinApiException(GetLastError()).what());
		return (base_err_msg + "\n" + detailed_err_msg).c_str();
	}
};

#endif // __EXCEPTIONS_HPP__
