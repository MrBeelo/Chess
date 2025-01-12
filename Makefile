# Variables
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = bin
ASSETS_DIR = assets
HEADERS_DIR = $(SRC_DIR)/headers
LIBRARIES_DIR = $(SRC_DIR)/libraries
LIBRARY = $(LIBRARIES_DIR)/libraylib.a
PROGRAM_NAME = Chess
EXECUTABLE = $(BUILD_DIR)/$(PROGRAM_NAME)
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(HEADERS_DIR)
LDFLAGS = -L$(LIBRARIES_DIR) -lraylib

# Find all .cpp files in the src directory
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Targets
all: $(EXECUTABLE) copy-assets

# Compile the program
$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJ_FILES) $(LIBRARY) -o $@ $(LDFLAGS)

# Compile each .cpp file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(HEADERS_DIR)/*.h)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Copy assets folder to the build directory
copy-assets:
	@mkdir -p $(BUILD_DIR)
	@cp -r $(ASSETS_DIR) $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

# Phony targets
.PHONY: all clean copy-assets
