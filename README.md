# interprocess-communication

[![Test](https://github.com/abdulla-ashurov/interprocess-communication/actions/workflows/test.yml/badge.svg?branch=main)](https://github.com/abdulla-ashurov/interprocess-communication/actions/workflows/test.yml)

## Example

This program illustrates how to create inherited FileMapping object and inherite it to child process using CMD.

```cpp
// parent_main.cpp

#include <string>
#include <sstream>

#include "../include/process.hpp"
#include "../include/file_mapping.hpp"

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
```

```cpp
// child_main.cpp

#include <iostream>

#include "../include/file_mapping.hpp"

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
```
