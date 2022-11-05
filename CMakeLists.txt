Project(SimpleHTTPServer)
cmake_minimum_required(VERSION 3.0)

add_executable(http src/http.c src/mime.c src/response.c src/utils.c)
