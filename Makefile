# 编译器
CXX = g++
# 标志
FLAGS = -pedantic-errors -std=c++17 -static -MMD -MP -Wall -I ./include -I ./lib/ncurses/include
# 添加 ncurses 静态库的路径
LDFLAGS = -L/home/ivan/remote_gp/lib/ncurses/lib -lncursesw -ltinfow
# DEBUG 标志
DEBUG_FLAGS = -g -O0

# 基本构建配置
SRC_DIR = ./src
BUILD_DIR = ./build
TEST_DIR = ./test
INCLUDE_DIR = ./include

# 找到所有依赖文件
DEP_FILES = $(wildcard $(BUILD_DIR)/*.d)


# 目标
TARGETS = main server
TEST_TARGETS = $(shell find $(TEST_DIR) -type f -name '*.cpp' | sed 's|$(TEST_DIR)/|$(BUILD_DIR)/|g' | sed 's|\.cpp$$||g')

.PHONY: all clean test

all: $(TARGETS)

# 海战棋游戏
GAME_OBJECTS = $(patsubst $(SRC_DIR)/battleship/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/battleship/*.cpp))
# 海战棋客户端
CLIENT_OBJECTS = $(patsubst $(SRC_DIR)/client/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/client/*.cpp))
# 海战棋服务器
SERVER_OBJECTS = $(patsubst $(SRC_DIR)/server/%.cpp, $(BUILD_DIR)/%.o,$(wildcard $(SRC_DIR)/server/*.cpp))

COMMON_OBJECTS = $(patsubst $(SRC_DIR)/common/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/common/*.cpp))

# 包含所有依赖文件
-include $(DEP_FILES)

$(BUILD_DIR)/%.o: $(SRC_DIR)/**/%.cpp
	$(CXX) $(FLAGS) -c $< -o $@


# 构建main
main: $(BUILD_DIR)/main

$(BUILD_DIR)/main: ./src/main.cpp $(GAME_OBJECTS) $(CLIENT_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) $(FLAGS) $^ $(LDFLAGS) -pthread -o $@

server: $(BUILD_DIR)/server

$(BUILD_DIR)/server: $(SERVER_OBJECTS) $(GAME_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) $(FLAGS) -I ./include $^ $(LDFLAGS) -pthread -o $@

# clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d


test: $(TEST_TARGETS)

./build/test_%: ./test/test_%.cpp $(GAME_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) $(FLAGS) -o $@ $^ $(LDFLAGS)