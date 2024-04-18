# 编译器
CXX = g++
# 标志
FLAGS = -pedantic-errors -std=c++11 -MMD -MP -Wall

# 基本构建配置
SRC_DIR = ./src
BUILD_DIR = ./build
INCLUDE_DIR = ./include

# 找到所有依赖文件
DEP_FILES = $(wildcard $(BUILD_DIR)/*.d)

# 目标
TARGETS = battleship client server

.PHONY: all clean

all: $(TARGETS)

# 海战棋游戏
GAME_OBJECTS = $(patsubst $(SRC_DIR)/battleship/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/battleship/*.cpp))
# 海战棋客户端
CLIENT_OBJECTS = $(patsubst $(SRC_DIR)/client/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/client/*.cpp))
# 海战棋服务器
SERVER_OBJECTS = $(patsubst $(SRC_DIR)/server/%.cpp, $(BUILD_DIR)/%.o,$(wildcard $(SRC_DIR)/server/*.cpp))

# 包含所有依赖文件
-include $(DEP_FILES)

$(BUILD_DIR)/%.o: $(SRC_DIR)/**/%.cpp
	$(CXX) $(FLAGS) -I $(INCLUDE_DIR) -c $< -o $@

# 构建battleship游戏
battleship: $(BUILD_DIR)/battleship
$(BUILD_DIR)/battleship: $(GAME_OBJECTS) $(filter-out $(BUILD_DIR)/client.o, $(CLIENT_OBJECTS))
	$(CXX) $(FLAGS) $^ -o $@

# 构建客户端
client: $(BUILD_DIR)/client
$(BUILD_DIR)/client: $(CLIENT_OBJECTS) $(filter-out $(BUILD_DIR)/battleship.o, $(GAME_OBJECTS))
	$(CXX) $(FLAGS) $^ -o $@
	
# 构建服务器
server: $(BUILD_DIR)/server
$(BUILD_DIR)/server: $(SERVER_OBJECTS) $(filter-out $(BUILD_DIR)/battleship.o, $(GAME_OBJECTS)) $(filter-out $(BUILD_DIR)/client.o, $(CLIENT_OBJECTS))
	$(CXX) $(FLAGS) $^ -o $@

# clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)?/*.d
