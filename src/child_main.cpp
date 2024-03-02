#include <iostream>

#include "file_mapping.hpp"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::wcout << "Please, provide FileMapping Handle to child process using CLI\n";
		return 1;
	}

	HANDLE hFileMap = (HANDLE)(std::stoi(argv[1]));
	std::wcout << "hFileMap: " << hFileMap << std::endl;

	const size_t MSG_LENGTH = 12;
	UniqueFileMapping<MSG_LENGTH> f_map(hFileMap);

	std::wcout << "Message from first process: " << (const char*)(f_map.begin());

	return 0;
}
