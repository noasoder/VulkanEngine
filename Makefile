CXX       := g++
CXX_FLAGS := -std=c++17 -static-libstdc++ -lpthread -lmsvcrt
CXX_FLAGS_EXE := -std=c++17 -static-libstdc++ -02 -lpthread -lmsvcrt

CXX_DLL	:= $(CXX) -shared

BIN     := bin
SRC     := src
INCLUDE_EXT := -IC:/VulkanSDK/1.2.182.0/Include -Ilib/glfw-3.3.4.bin.WIN64/include -Ilib/glm -Ilib/imgui -Ilib/OpenFBX -Ilib/stb -Ilib/tiny_obj_loader
LIBPATH := -LC:/VulkanSDK/1.2.182.0/Lib -Llib/glfw-3.3.4.bin.WIN64/lib-mingw-w64

LIBRARIES   := -l:libglfw3dll.a -lvulkan-1
DLL  := VulkanEngine.dll
EXECUTABLE  := VulkanEngine
OUTEXE := $(BIN)/$(EXECUTABLE)
OUTDLL := $(BIN)/$(DLL)

DIRS = $(SRC)/code
vpath %.c $(DIRS)
vpath %.cpp $(DIRS)
SEARCHC = $(addsuffix /*.c ,$(DIRS))
SEARCHCPP = $(addsuffix /*.cpp ,$(DIRS))
SRCS = $(wildcard $(SEARCHC))
SRCS += $(wildcard $(SEARCHCPP))

DIRS_DLL = $(SRC)/engine $(SRC)/engine/Camera $(SRC)/engine/Camera/CameraControllers $(SRC)/engine/Managers $(SRC)/engine/Utility
vpath %.c $(DIRS_DLL)
vpath %.cpp $(DIRS_DLL)
SEARCHC_DLL = $(addsuffix /*.c ,$(DIRS_DLL))
SEARCHCPP_DLL = $(addsuffix /*.cpp ,$(DIRS_DLL))
SRCS_DLL = $(wildcard $(SEARCHC_DLL))
SRCS_DLL += $(wildcard $(SEARCHCPP_DLL))

INCLUDE = -Iinclude -Iinclude/Camera -Iinclude/Camera/CameraControllers -Iinclude/Managers -Iinclude/Utility


all: dll exe

dll: $(SRCS_DLL)
	$(CXX_DLL) $(CXX_FLAGS) -g $^ -o $(OUTDLL) $(INCLUDE_EXT) $(INCLUDE) $(LIBPATH) $(LIBRARIES)

exe: $(SRC)/main.cpp $(SRCS)
	$(CXX) $(CXX_FLAGS) -g $^ -o $(OUTEXE) $(INCLUDE_EXT) $(INCLUDE) $(LIBPATH) -Lbin/ $(LIBRARIES) -lVulkanEngine

clean:
	-rm $(BIN)/*