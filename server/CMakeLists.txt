# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.10)
project (server)

find_package (Threads)

# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../thirdparty/SQLiteCpp)

# Poco Library setup
find_library(Poco_LIBRARIES NAMES PocoFoundation PocoJSON PocoUtil PocoNet PocoSQL)

if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()



add_executable(server "./server.cpp")
target_link_libraries(server 
    # SQLiteCpp
    # sqlite3
    ${CMAKE_THREAD_LIBS_INIT}
    PocoFoundation PocoJSON PocoUtil PocoNet
    # dl
    )