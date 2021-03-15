FINAL_EXEC := vis
CC := g++

# source file dir
SRC_DIR := ./source
# build dir
BUILD_DIR := ./build
# header file dir
INC_DIRS := include
INC_FLAGS := $(addprefix -I, $(INC_DIRS))
WIN_FLAGS := -lmingw32 -LC:/mingw_dev_lib/lib -IC:/mingw_dev_lib/include

# list of all source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# list of all source files, but in build dir
OBJS_TEMP := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS))
# list of all object files in build dir
OBJS := $(OBJS_TEMP:.cpp=.o )
# list of all dependencies
DEPS := $(OBJS:.o=.d)

# IF RUNNING WINDOWS, THEN INCLUDE THE WIN_FLAGS
# VARIABLE BEFORE -lSDL2main, IF NOT ON WINDOWS, REMOVE IT
$(BUILD_DIR)/$(FINAL_EXEC): $(OBJS)
	$(CC) $^ -o $@ $(WIN_FLAGS) -lSDL2main -lSDL2

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(INC_FLAGS) -MMD -MP -c $^ -o $@ 

speak:
	@echo $(OBJS)
	@echo $(SRCS)
	@echo $(DEPS)

# dont want to delete the .pngs
clean:
	rm $(BUILD_DIR)/*.o
	rm $(BUILD_DIR)/*.d
	rm $(BUILD_DIR)/$(FINAL_EXEC)