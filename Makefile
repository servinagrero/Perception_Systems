CXX ?= g++
CXXFLAGS += -pedantic -Wall -Wextra -g -fPIC $(OCV_F)
LDLIBS += $(CXXFLAGS) $(OCV_L)

OCV_L = $(pkg-config --libs opencv)
OCV_F = $(pkg-config --cflags opencv)

SRC_FILES := $(wildcard *.cpp)
OBJ_FILES  := $(patsubst %.cpp,%,$(SRC_FILES))

BUILD_DIR := build

all: $(BUILD_DIR) $(OBJ_FILES)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJ_FILES)

.PHONY: all clean
