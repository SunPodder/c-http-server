CC=gcc
SRC_DIR=src
BUILD_DIR=build

http: src/http.c src/response.c
	$(CC) $(SRC_DIR)/*.c -O3 -g -L $(SRC_DIR) -o $(BUILD_DIR)/http -lm
