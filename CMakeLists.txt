cmake_policy(SET CMP0048 NEW)

Project(SimpleHTTPServer VERSION 1.0.3 LANGUAGES C)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(src)
add_subdirectory(src/hash-table)
add_subdirectory(src/mime)


cmake_policy(SET CMP0079 NEW)

target_link_libraries(http PUBLIC MIME)
target_link_libraries(http PUBLIC HashTable)

