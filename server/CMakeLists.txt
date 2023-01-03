# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.10)
project (server)

# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../thirdparty/SQLiteCpp)

target_link_libraries(server 
    # SQLiteCpp
    # sqlite3
    pthread
    dl
    )



add_executable(server "./server.cpp")