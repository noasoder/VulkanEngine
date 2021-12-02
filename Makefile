CXX       := g++

WIN_FLAGS := -std=c++17 -static-libstdc++ -lpthread -lmsvcrt
LINUX_FLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi


CXX_DLL	:= $(CXX) -shared

BIN     := bin
SRC     := src
INCLUDE_EXT := -IC:/VulkanSDK/1.2.198.0/Include -Ilib/glfw-3.3.5.bin.WIN64/include -Ilib/glm -Ilib/imgui -Ilib/stb -Ilib/tiny_obj_loader
LIBPATH := -LC:/VulkanSDK/1.2.198.0/Lib -Llib/glfw-3.3.5.bin.WIN64/lib-mingw-w64 -Lbin/ -Lbin/lib 

LIBRARIES   := -l:libglfw3dll.a -lvulkan-1
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

DIRS_UTIL = $(SRC)/utility
vpath %.cpp $(DIRS_UTIL)
SCPP_UTIL = $(addsuffix /*.cpp ,$(DIRS_UTIL))
SRC_UTIL += $(wildcard $(SCPP_UTIL))

INCLUDE_DLL = -Isrc/engine -Isrc/engine/Camera -Isrc/engine/Camera/CameraControllers -Isrc/engine/Managers -Isrc/utility -Isrc/openfbx 
INCLUDE = -Isrc/code -Isrc/code/Networking

all: dll exe
libs: ofbx utils dll
linux: linux_utils linux_dll linux_exe

ofbx: 
	$(CXX) -std=c++17 -c src/openfbx/miniz.cpp src/openfbx/ofbx.cpp 
	ar crf bin/lib/OpenFBX.a miniz.o ofbx.o

utils: $(SRC_UTIL)
	$(CXX_DLL) $(WIN_FLAGS) -g $^ -o bin/Utility.dll $(INCLUDE_EXT) -Isrc/utility $(LIBPATH) $(LIBRARIES) 

dll: $(SRCS_DLL)
	$(CXX_DLL) $(WIN_FLAGS) -g $^ -o $(OUTDLL) $(INCLUDE_EXT) $(INCLUDE_DLL) $(LIBPATH) $(LIBRARIES) -l:OpenFBX.a -lUtility

exe: $(SRC)/main.cpp $(SRCS)
	$(CXX) $(WIN_FLAGS) -g $^ -o $(OUTEXE) $(INCLUDE_EXT) $(INCLUDE) $(LIBPATH) $(INCLUDE_DLL) $(LIBRARIES) -l:OpenFBX.a -lUtility -lVulkanEngine -lWS2_32

linux_utils: $(SRC_UTIL)
	$(CXX_DLL) $(LINUX_FLAGS) -g $^ -o bin/Utility.dll $(INCLUDE_EXT) -Isrc/utility $(LIBPATH) $(LIBRARIES) 

linux_dll: $(SRCS_DLL)
	$(CXX_DLL) $(LINUX_FLAGS) -g $^ -o $(OUTDLL) $(INCLUDE_EXT) $(INCLUDE_DLL) $(LIBPATH) $(LIBRARIES) -l:OpenFBX.a -lUtility

linux_exe: $(SRC)/main.cpp $(SRCS)
	$(CXX) $(LINUX_FLAGS) -g $^ -o $(OUTEXE) $(INCLUDE_EXT) $(INCLUDE) $(LIBPATH) $(INCLUDE_DLL) $(LIBRARIES) -l:OpenFBX.a -lUtility -lVulkanEngine -lWS2_32