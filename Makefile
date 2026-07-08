CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Iinclude
AR = ar

BUILD_DIR = build
LIB = $(BUILD_DIR)/libsorting.a
DEMO = $(BUILD_DIR)/demo

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
HDR = $(wildcard include/*.h)

all: $(LIB) $(DEMO)

# Libreria estatica
$(LIB): $(OBJ)
	$(AR) rcs $@ $(OBJ)

$(BUILD_DIR)/%.o: src/%.cpp $(HDR)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Demo enlazado contra la libreria
$(DEMO): examples/main.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< -L$(BUILD_DIR) -lsorting -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
