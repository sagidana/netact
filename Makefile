CC = gcc
CFLAGS = -g -Wall -pthread

SRC_DIR = ./src
BIN_DIR = ./bin
HDR_DIR = ./headers
TARGET = $(BIN_DIR)/netact

all: $(SRC_DIR)/main.c $(BIN_DIR)/extractor.o $(BIN_DIR)/list.o
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_DIR)/main.c $(BIN_DIR)/extractor.o $(BIN_DIR)/list.o

$(BIN_DIR)/extractor.o: $(SRC_DIR)/extractor.c $(HDR_DIR)/extractor.h
	$(CC) $(CFLAGS) -c -o $(BIN_DIR)/extractor.o $(SRC_DIR)/extractor.c

$(BIN_DIR)/list.o: $(SRC_DIR)/list.c $(HDR_DIR)/list.h
	$(CC) $(CFLAGS) -c -o $(BIN_DIR)/list.o $(SRC_DIR)/list.c

clean:
	rm $(BIN_DIR)/*.o

