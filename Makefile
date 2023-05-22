# https://gl.developpez.com/tutoriel/outil/makefile/
# https://makefiletutorial.com/#implicit-rules
# https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index
# https://stackoverflow.com/questions/2649334/difference-between-static-and-shared-libraries
exec      = texture # name of the executable selected when doing 'run'

SRC_DIR   = src
BUILD_DIR = build

LIB_DIR   = lib/viewer_core
LIB_NAME  = lib.a

LIB_SRC = $(shell find $(LIB_DIR) -name '*.cpp')
LIB_OBJ = $(LIB_SRC:%=$(BUILD_DIR)/%.o)
DEPS    = $(LIB_OBJ:%.o=%.d)

SRC   = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ   = $(SRC:%=$(BUILD_DIR)/$(SRC_DIR)/%.o)
DEPS += $(OBJ:%.o=%.d)
BINS  = $(foreach file, $(SRC), $(BUILD_DIR)/$(shell basename $(file) .cpp).out)

CXXFLAGS += -std=c++17 -Iinclude
CXXFLAGS += `pkg-config --cflags glew`
CXXFLAGS += `pkg-config --cflags glfw3`
CXXFLAGS += `pkg-config --cflags xrandr`

LDFLAGS  += `pkg-config --libs glew`
LDFLAGS  += `pkg-config --libs glfw3`
LDFLAGS  += `pkg-config --libs xrandr`
LDFLAGS  += -lpthread

.PHONY: all
all: $(BINS)

.PHONY: bin
bin: $(BUILD_DIR)/$(exec).out

.PHONY: run
run: bin
	$(BUILD_DIR)/$(exec).out

.PHONY: clean
clean: 
	rm -rf $(BUILD_DIR)

# build archive, need object files
$(BUILD_DIR)/$(LIB_NAME): $(LIB_OBJ)
	ar rcs $@ $^ 

$(BUILD_DIR)/%.out: $(BUILD_DIR)/$(SRC_DIR)/%.cpp.o $(BUILD_DIR)/$(LIB_NAME)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(BUILD_DIR)/$(LIB_NAME)

-include $(DEPS)

# build object files
$(BUILD_DIR)/%.cpp.o: %.cpp
	-@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
