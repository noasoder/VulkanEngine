COMPILER		:= g++
LANG_VERSION	:= -std=c++17
CXX_EXE	:= $(COMPILER) $(LANG_VERSION)
CXX_DLL	:= $(COMPILER) -shared $(LANG_VERSION)

WIN_FLAGS := -static-libstdc++ -lpthread -lmsvcrt
LINUX_FLAGS = -lglfw -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

BIN     := bin
SRC     := src

DLL_NAME  := Engine
EXECUTABLE  := Application
OUTEXE := $(BIN)/$(EXECUTABLE)
OUTDLL := $(BIN)/$(DLL_NAME).dll

INCLUDE_EXT := -Ilib/vulkan/include -Ilib/glfw/include -Ilib/glew/include -Ilib/glm -Ilib/imgui -Ilib/imgui/backends -Ilib/tiny_obj_loader

LIBPATHS := -Llib/vulkan/Lib -Llib/glfw/build/src -Llib/glew/lib -Llib/opengl -Lbin/ -Lbin/lib

BASE_LIB   := -l:libglew32.dll.a -l:libglfw3dll.a -lvulkan-1 -lopengl32
DLL_LIB := $(BASE_LIB) -l:OpenFBX.a -lUtility
EXE_LIB := $(DLL_LIB) -l$(DLL_NAME) -lWS2_32


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
vpath %.hpp $(DIRS_DLL)
SEARCHC_DLL = $(addsuffix /*.c ,$(DIRS_DLL))
SEARCHCPP_DLL = $(addsuffix /*.cpp ,$(DIRS_DLL))
SEARCHHPP_DLL = $(addsuffix /*.hpp ,$(DIRS_DLL))
SRCS_DLL = $(wildcard $(SEARCHC_DLL))
SRCS_DLL += $(wildcard $(SEARCHCPP_DLL))
SRCS_DLL += $(wildcard $(SEARCHHPP_DLL))

DIRS_UTIL = $(SRC)/utility
vpath %.cpp $(DIRS_UTIL)
vpath %.hpp $(DIRS_UTIL)
SCPP_UTIL = $(addsuffix /*.cpp ,$(DIRS_UTIL))
SHPP_UTIL = $(addsuffix /*.hpp ,$(DIRS_UTIL))
SRC_UTIL = $(wildcard $(SCPP_UTIL))
SRC_UTIL += $(wildcard $(SHPP_UTIL))

INCLUDE_DLL = -Isrc/engine -Isrc/engine/Camera -Isrc/engine/Camera/CameraControllers -Isrc/engine/Managers -Isrc/utility -Isrc/openfbx -Isrc/stb
INCLUDE_EXE =  $(INCLUDE_DLL) -Isrc/code -Isrc/code/Networking

all: dll exe
libs: ofbx utils dll
linux: linux_utils linux_dll linux_exe

ofbx: 
	$(CXX_EXE) -c src/openfbx/miniz.cpp src/openfbx/ofbx.cpp 
	ar crf bin/lib/OpenFBX.a miniz.o ofbx.o

utils: 
	$(CXX_DLL) $(WIN_FLAGS) -g $(SRC_UTIL) -o bin/Utility.dll $(INCLUDE_EXT) -Isrc/utility $(LIBPATHS) $(BASE_LIB) 

dll: 
	$(CXX_DLL) $(WIN_FLAGS) -g $(SRCS_DLL) -o $(OUTDLL) $(INCLUDE_EXT) $(INCLUDE_DLL) $(LIBPATHS) $(DLL_LIB)

exe: $(SRC)/main.cpp $(SRCS)
	$(CXX_EXE) $(WIN_FLAGS) -g $^ -o $(OUTEXE) $(INCLUDE_EXT) $(INCLUDE_EXE) $(LIBPATHS) $(EXE_LIB)

linux_utils: 
	$(CXX_DLL) $(LINUX_FLAGS) -fPIC -g $(SRC_UTIL) -o bin/Utility.so $(INCLUDE_EXT) -Isrc/utility $(LIBPATHS)

linux_dll: $(SRCS_DLL)
	$(CXX_DLL) $(LINUX_FLAGS) -fPIC -g $(SRCS_DLL) -o bin/Engine.so $(INCLUDE_EXT) $(INCLUDE_DLL) $(LIBPATHS) -l:OpenFBX.a -l:Utility.so

linux_exe: $(SRC)/main.cpp $(SRCS) $(SRCS_DLL)
	$(CXX_EXE) $(LINUX_FLAGS) -g $^ -o $(OUTEXE) $(INCLUDE_EXT) $(INCLUDE_EXE) $(LIBPATHS) -l:OpenFBX.a -l:Utility.so

DIRS_EDITOR = editor
vpath %.cpp $(DIRS_EDITOR)
SCPP_EDITOR = $(addsuffix /*.cpp ,$(DIRS_EDITOR))
SRC_EDITOR = $(wildcard $(SCPP_EDITOR))

shader_editor: 
	$(CXX_EXE) $(WIN_FLAGS) -g $(SRC_EDITOR) -o bin/ShaderEditor $(INCLUDE_EXT) -Isrc/utility $(LIBPATHS) -l:libglew32.dll.a -l:libglfw3dll.a -lopengl32 -lUtility -lImGui

DIRS_IMGUI = lib/imgui
vpath %.cpp $(DIRS_IMGUI)
SCPP_IMGUI = $(addsuffix /*.cpp ,$(DIRS_IMGUI))
SRC_IMGUI = $(wildcard $(SCPP_IMGUI))

imgui: $(SRC_IMGUI) lib/imgui/backends/imgui_impl_opengl3.cpp lib/imgui/backends/imgui_impl_glfw.cpp
	$(CXX_DLL) $(WIN_FLAGS) -g $^ -o bin/ImGui.dll -Ilib/imgui -Ilib/imgui/backends -Ilib/glfw/include -Llib/glfw/build/src -l:libglfw3dll.a -lopengl32 