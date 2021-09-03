CXX       := gcc
CXX_FLAGS := -std=c++17 -static-libgcc -static-libstdc++ -static -lpthread

BIN     := bin
SRC     := src
INCLUDE := -IC:/VulkanSDK/1.2.182.0/Include -Ilib/glfw-3.3.4.bin.WIN64/include -Ilib/glm -Ilib/imgui -Ilib/OpenFBX -Ilib/stb -Ilib/tiny_obj_loader -Iinclude -Isrc/code
LIBPATH := -LC:/VulkanSDK/1.2.182.0/Lib -Llib/glfw-3.3.4.bin.WIN64/lib-mingw-w64

LIBRARIES   := -lvulkan-1 -lglfw3
EXECUTABLE  := VulkanEngine


DIRS = src src/code src/code/Camera src/code/Camera/CameraControllers src/code/Managers src/code/Utility
vpath %.c $(DIRS)
vpath %.cpp $(DIRS)
SEARCHC = $(addsuffix /*.c ,$(DIRS))
SEARCHCPP = $(addsuffix /*.cpp ,$(DIRS))
SRCS = $(wildcard $(SEARCHC))
SRCS += $(wildcard $(SEARCHCPP))


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRCS)
	$(CXX) $(CXX_FLAGS) -g $(INCLUDE) $(LIBPATH) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*