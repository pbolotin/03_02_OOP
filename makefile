CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := .
OBJ_DIR  := $(BUILD)
APP_DIR  := $(BUILD)
TARGET   := snake
INCLUDE  := -Iinclude/
SRC      :=                      \
		$(wildcard *.cpp)         \

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES \
         := $(OBJECTS:.o=.d)

all: build $(APP_DIR)/$(TARGET) snake_all_header

$(OBJ_DIR)/%.o: %.cpp
		@mkdir -p $(@D)
		$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
		@mkdir -p $(@D)
		$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info

build:
		@mkdir -p $(APP_DIR)
		@mkdir -p $(OBJ_DIR)

snake_all_header:
		cat *.h > snake_all.hpp

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
		-@rm -rvf $(OBJ_DIR)/*.d
		-@rm -rvf $(APP_DIR)/*.o
		-@rm -rvf $(APP_DIR)/$(TARGET)

info:
		@echo "[*] Application dir: ${APP_DIR}     "
		@echo "[*] Object dir:      ${OBJ_DIR}     "
		@echo "[*] Sources:         ${SRC}         "
		@echo "[*] Objects:         ${OBJECTS}     "
		@echo "[*] Dependencies:    ${DEPENDENCIES}"
