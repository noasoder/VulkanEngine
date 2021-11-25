CXX       := g++
CXX_FLAGS := -std=c++17 -static-libstdc++ -lpthread -lmsvcrt
CXX_FLAGS_EXE := -std=c++17 -static-libgcc -static-libstdc++ -lpthread -lmsvcrt

CXX_DLL	:= $(CXX) -shared

BIN     := bin
SRC     := src
INCLUDE_EXT := -IC:/VulkanSDK/1.2.198.0/Include -Ilib/glfw-3.3.4.bin.WIN64/include -Ilib/glm -Ilib/imgui -Ilib/stb -Ilib/tiny_obj_loader
LIBPATH := -LC:/VulkanSDK/1.2.198.0/Lib -Llib/glfw-3.3.4.bin.WIN64/lib-mingw-w64 -Lbin/ -Lbin/lib 

LIBRARIES   := -l:libglfw3dll.a -lvulkan-1 -l:OpenFBX.a
DLL  := VulkanEngine.dll
EXECUTABLE  := VulkanEngine
OUTEXE := $(BIN)/$(EXECUTABLE)
OUTDLL := $(BIN)/$(DLL)

DIRS = $(SRC)/code $(SRC)/code/Networking
vpath %.c $(DIRS)
vpath %.cpp $(DIRS)
SEARCHC = $(addsuffix /*.c ,$(DIRS))
SEARCHCPP = $(addsuffix /*.cpp ,$(DIRS))
SRCS = $(wildcard $(SEARCHC))
SRCS += $(wildcard $(SEARCHCPP))

DIRS_DLL = $(SRC)/engine $(SRC)/engine/Camera $(SRC)/engine/Camera/CameraControllers $(SRC)/engine/Managers $(SRC)/engine/Utility
vpath %.c $(DIRS_DLL)
vpath %.cpp $(DIRS_DLL)
vpath %.o $(BIN)/lib
SEARCHC_DLL = $(addsuffix /*.c ,$(DIRS_DLL))
SEARCHCPP_DLL = $(addsuffix /*.cpp ,$(DIRS_DLL))
SEARCHO_DLL = $(addsuffix /*.o ,$(BIN)/lib))
SRCS_DLL = $(wildcard $(SEARCHC_DLL))
SRCS_DLL += $(wildcard $(SEARCHCPP_DLL))
SRCSO_DLL = $(wildcard $(SEARCHO_DLL))

INCLUDE_DLL = -Isrc/engine -Isrc/engine/Camera -Isrc/engine/Camera/CameraControllers -Isrc/engine/Managers -Isrc/engine/Utility -Isrc/openfbx
INCLUDE = -Isrc/code -Isrc/code/Networking


all: dll exe

ofbx: 
	$(CXX) -std=c++17 -c src/openfbx/miniz.cpp src/openfbx/ofbx.cpp 
	ar crf bin/lib/OpenFBX.a miniz.o ofbx.o

dll: $(SRCS_DLL)
	$(CXX_DLL) $(CXX_FLAGS) -g $^ -o $(OUTDLL) $(INCLUDE_EXT) $(INCLUDE_DLL) $(LIBPATH) $(LIBRARIES) 

exe: $(SRC)/main.cpp $(SRCS)
	$(CXX) $(CXX_FLAGS_EXE) -g $^ -o $(OUTEXE) $(INCLUDE_EXT) $(INCLUDE) $(LIBPATH) $(INCLUDE_DLL) $(LIBRARIES) -lVulkanEngine -lWS2_32