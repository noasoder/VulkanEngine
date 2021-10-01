CXX       := g++
CXX_FLAGS := -std=c++17 -static-libstdc++ -lpthread -lmsvcrt
CXX_FLAGS_EXE := -std=c++17 -static-libstdc++ -02 -lpthread -lmsvcrt

CXX_DLL	:= $(CXX) -shared

BIN     := bin
SRC     := src
INCLUDE := -IC:/VulkanSDK/1.2.182.0/Include -Ilib/glfw-3.3.4.bin.WIN64/include -Ilib/glm -Ilib/imgui -Ilib/OpenFBX -Ilib/stb -Ilib/tiny_obj_loader
LIBPATH := -LC:/VulkanSDK/1.2.182.0/Lib -Llib/glfw-3.3.4.bin.WIN64/lib-mingw-w64

LIBRARIES   := -l:libglfw3dll.a -lvulkan-1
DLL  := VulkanEngine.dll
EXECUTABLE  := VulkanEngine
OUTEXE := $(BIN)/$(EXECUTABLE)
OUTDLL := $(BIN)/$(DLL)

DIRS = $(SRC)/code $(SRC)/code/Camera $(SRC)/code/Camera/CameraControllers $(SRC)/code/Managers $(SRC)/code/Utility
vpath %.c $(DIRS)
vpath %.cpp $(DIRS)
SEARCHC = $(addsuffix /*.c ,$(DIRS))
SEARCHCPP = $(addsuffix /*.cpp ,$(DIRS))
SRCS = $(wildcard $(SEARCHC))
SRCS += $(wildcard $(SEARCHCPP))

DIRS2 = -Iinclude -Iinclude/Camera -Iinclude/Camera/CameraControllers -Iinclude/Managers -Iinclude/Utility


all: dll exe

dll: $(SRCS)
	$(CXX_DLL) $(CXX_FLAGS) -g $^ -o $(OUTDLL) $(INCLUDE) $(DIRS2) $(LIBPATH) $(LIBRARIES)

exe:
	$(CXX) $(CXX_FLAGS) -g $(SRC)/main.cpp -o $(OUTEXE) $(INCLUDE) $(DIRS2) $(LIBPATH) -Lbin/ $(LIBRARIES) -lVulkanEngine

clean:
	-rm $(BIN)/*