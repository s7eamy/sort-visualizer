CC := g++
FINAL_EXEC := vis.exe

SRC_DIR := ./source
BUILD_DIR := ./build
INC_DIR := ./include

OBJS := $(BUILD_DIR)/Drawing.o $(BUILD_DIR)/MergeSort.o $(BUILD_DIR)/main.o

INC_FLAGS := $(addprefix -I, $(INC_DIR))
LIB_FLAGS := -lmingw32 -LC:/mingw_dev_lib/lib -IC:/mingw_dev_lib/include -lSDL2main -lSDL2

$(BUILD_DIR)/$(FINAL_EXEC): $(OBJS)
	g++ $? -o $@ $(INC_FLAGS) $(LIB_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(INC_FLAGS) -c $^ -o $@

clean:
	rm $(BUILD_DIR)/*.o
	rm $(BUILD_DIR)/vis.exe