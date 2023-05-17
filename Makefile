# https://gl.developpez.com/tutoriel/outil/makefile/
# https://makefiletutorial.com/#implicit-rules
# https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index
# https://stackoverflow.com/questions/2649334/difference-between-static-and-shared-libraries
exec := ray_marching.cpp # or main.cpp
LIB_NAME := lib.a

LIB_DIR := ./lib
SRC_DIR := ./src
BUILD_DIR :=./build

CPP_FILES := $(shell find $(LIB_DIR) -name '*.cpp')
BUILD_CPP_FILES := $(CPP_FILES:%=$(BUILD_DIR)/%.o)

LIBS=-lGL -lX11 -lpthread -lXrandr -ldl -lglfw -lGLEW -lGLU
INCLUDES=./include
STD=-std=c++17

build_lib: $(BUILD_DIR)/$(LIB_NAME)

run: $(BUILD_DIR)/$(exec).out
	./$^

clean: 
	rm -rf $(BUILD_DIR)

$(BUILD_DIR)/$(LIB_NAME): $(BUILD_CPP_FILES)
	# $(CXX) $(STD) $(CPPFLAGS) $(CXXFLAGS) $(LIBS) -I$(INCLUDES) -o $(BUILD_DIR)/lib$(LIB_NAME) $^
	ar rcs $@ $^ 

$(BUILD_DIR)/$(exec).out: $(BUILD_DIR)/$(LIB_NAME) 
	$(CXX) $(STD) $(SRC_DIR)/$(exec) -L$(BUILD_DIR) -l:$(LIB_NAME) -I$(INCLUDES) $(CPPFLAGS) $(CXXFLAGS) $(LIBS) -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(STD) $(CPPFLAGS) $(CXXFLAGS) -I$(INCLUDES) -c $< -o $@ 

