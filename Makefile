CC := g++
FINAL_EXEC := vis.exe

SRC_DIR := ./source
BUILD_DIR := ./build

LIB_FLAGS := -lmingw32 -LC:/mingw_dev_lib/lib -IC:/mingw_dev_lib/include -lSDL2main -lSDL2

$(BUILD_DIR)/$(FINAL_EXEC): $(BUILD_DIR)/main.o
	g++ $? -o $@ $(LIB_FLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	g++ -c $^ -o $@

clean:
	rm $(BUILD_DIR)/main.o
	rm $(BUILD_DIR)/vis.exe