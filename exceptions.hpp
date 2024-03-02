#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include <string>

#include <Windows.h>

#include "common.hpp"

class BaseWinApiExceptions : public std::exceptions {
private:
	int m_err_code;
public:
	BaseWinApiExceptions(const int err_code) : m_err_code(err_code) {}

	std::string what() const {
		return error_message(m_err_code);
	}
};

#endif // __EXCEPTIONS_HPP__
