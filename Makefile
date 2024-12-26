CXX := g++
CXXFLAGS := -Wall -Iinclude -ISDL2/include -Igoogletest/googletest/include
LIBS := -LSDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# Add paths for Google Test libraries
GTEST_LIBS := -Lgoogletest/build/lib -lgtest -lgtest_main -pthread

SRC_DIR := src
INCLUDE_DIR := include
ENGINE_SRC := $(SRC_DIR)/Engine
ENGINE_INCLUDE := $(INCLUDE_DIR)/Engine
UNIT_TEST_DIR := $(SRC_DIR)/unit_tests

SOURCES := $(wildcard $(SRC_DIR)/*.cpp $(ENGINE_SRC)/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
TARGET := engine

# Unit test sources and target
UNIT_TEST_SOURCES := $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp $(ENGINE_SRC)/*.cpp $(UNIT_TEST_DIR)/*.cpp))
UNIT_TEST_OBJECTS := $(UNIT_TEST_SOURCES:.cpp=.o)
UNIT_TEST_TARGET := unit_tests

.PHONY: all clean run build_run test

all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

build_run: all run

clean:
	rm -f $(OBJECTS) $(TARGET) $(UNIT_TEST_OBJECTS) $(UNIT_TEST_TARGET)

# Rule to build and run unit tests
test: $(UNIT_TEST_TARGET)
	./$(UNIT_TEST_TARGET)

$(UNIT_TEST_TARGET): $(UNIT_TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS) $(GTEST_LIBS)
