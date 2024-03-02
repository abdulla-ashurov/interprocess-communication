#include <string>
#include <sstream>

#include "process.hpp"
#include "file_mapping.hpp"

/*
 * This program illustrates how to create inherited FileMapping object
 * and inherite it to child process using CMD.
 */

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Please, provide correct list of arguments" << std::endl;
		std::cout << "CLI example: arg_count child_proces_app_name" << std::endl;
		return 1;
	}

	try {
		std::string msg("Hello World!");
		const size_t MSG_LENGTH = 12;
		UniqueInheritedFileMapping<MSG_LENGTH> f_map;

		strcpy(static_cast<char*>(f_map.begin()), msg.c_str());

		std::wstringstream cmd;
		cmd << argv[1] << (UINT_PTR)(f_map.handle());

		Process process(cmd.str());
		process.join();
	}
	catch (BaseWinApiExceptions &e) {
		std::cout << "Error: " << e.what();
	}

	return 0;
}
