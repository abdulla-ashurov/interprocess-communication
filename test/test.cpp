#include "catch_amalgamated.hpp"

#include "../include/buffer.hpp"
#include "../include/handle.hpp"

TEST_CASE("Test UniqueMapViewBuffer class") {
    SECTION("Test UniqueMapViewBuffer move constructor") {
        const size_t SIZE = 20;
        UniqueMapViewBuffer buffer1(SIZE, details::map_view_of_file(details::create_file_mapping(SIZE), SIZE));
        REQUIRE(buffer1.size() == SIZE);

        const size_t expected_size = buffer1.size();
        void *expected_beg = buffer1.begin();
        
        UniqueMapViewBuffer buffer2(std::move(buffer1));
        REQUIRE(buffer2.size() == expected_size);
        REQUIRE(buffer2.begin() == expected_beg);

        REQUIRE(buffer1.size() == 0);
        REQUIRE(buffer1.begin() == nullptr);
    }

    SECTION("Test UniqueMapViewBuffer operator=") {
        const size_t SIZE = 20;
        UniqueMapViewBuffer buffer1(SIZE, details::map_view_of_file(details::create_file_mapping(SIZE), SIZE));
        UniqueMapViewBuffer buffer2(SIZE, details::map_view_of_file(details::create_file_mapping(SIZE), SIZE));
        
        const size_t expected_size = buffer1.size();
        void *expected_beg = buffer1.begin();

        buffer2 = std::move(buffer1);
        REQUIRE(buffer2.size() == expected_size);
        REQUIRE(buffer2.begin() == expected_beg);

        REQUIRE(buffer1.size() == 0);
        REQUIRE(buffer1.begin() == nullptr);
    }
}

TEST_CASE("Test UniqueHandle class") {
    SECTION("Test UniqueHandle move constructor") {
        UniqueHandle handle1(details::create_file_mapping(20));
        HANDLE expected_handle = handle1.handle();

        UniqueHandle handle2(std::move(handle1));
        REQUIRE(handle2.handle() == expected_handle);
        REQUIRE(handle1.handle() == nullptr);
    }

    SECTION("Test UniqueHandle operator=") {

    }
}