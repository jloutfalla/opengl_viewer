# https://gl.developpez.com/tutoriel/outil/makefile/
# https://makefiletutorial.com/#implicit-rules
LIBS=-lGL -lX11 -lpthread -lXrandr -ldl -lglfw -lGLEW -lGLU
SRC_DIR :=./src
BUILD_DIR :=./build
TARGET_EXEC := program
CPP_FILES := $(shell find $(SRC_DIR) -name '*.cpp')

BUILD_CPP_FILES := $(CPP_FILES:%=$(BUILD_DIR)/%.o)
INCLUDES=./include
STD=-std=c++17


$(BUILD_DIR)/$(TARGET_EXEC): $(BUILD_CPP_FILES)
	echo $(CPP_FILES)
	$(CXX) $(STD) $(BUILD_CPP_FILES) $(CPPFLAGS) $(CXXFLAGS) $(LIBS) -I$(INCLUDES)  -o $@ 

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(STD) $(CPPFLAGS) $(CXXFLAGS) -I$(INCLUDES) -c $< -o $@ 

build: $(BUILD_DIR)/$(TARGET_EXEC)

run: $(BUILD_DIR)/$(TARGET_EXEC)
	./$^

clean: 
	rm -rf $(BUILD_DIR)

