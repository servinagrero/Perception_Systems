CXX ?= g++
CXXFLAGS += -pedantic -Wall -Wextra -g -fPIC $(OCV_F)
LDLIBS = $(LDFLAGS) $(OCV)

OCV_L = $(pkg-config --libs opencv)
OCV_F = $(pkg-config --cflags opencv)

SRC_FILES := $(wildcard *.cpp)
OBJFILES  := $(patsubst %.cpp,%.o,$(SRCFILES))

BUILD_DIR := build

%.cpp: $(OBJFILES)
    $(LINKER) $^ -o $@


%.o: %.cpp
    $(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
