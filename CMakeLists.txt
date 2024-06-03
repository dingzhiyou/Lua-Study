cmake_minimum_required(VERSION 3.8)

project(lua_project)
set(CMAKE_CXX_FLAGS "$ENV{CXX_FALGS} -ggdb  -O0 -Werror")
set(CMAKE_CXX_COMPILE_FEATURES gcc)

include_directories(/usr/local/include/
                    )

link_directories(/usr/local/lib/
                )

add_executable(main code/main.cpp)
target_link_libraries(main -llua)


add_executable(test_cout test/test_cout.cpp)

SET(EXECUTABLE_OUTPUT_PATH   ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)




