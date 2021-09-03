CXX       := g++
CXX_FLAGS := -std=c++17 -static-libgcc -static-libstdc++ -static -lpthread -g

BIN     := bin
SRC     := src
INCLUDE := include -IC:/VulkanSDK/1.2.182.0/Include -Ilib/glfw-3.3.4.bin.WIN64/include -Ilib/glm -Ilib/imgui -Ilib/OpenFBX -Ilib/stb -Ilib/dtiny_obj_loader
LIBPATH := -IC:/VulkanSDK/1.2.182.0/Lib -Ilib/glfw-3.3.4.bin.WIN64/lib-vc2019

LIBRARIES   := -lvulkan-1.lib -lglfw3.lib
EXECUTABLE  := VulkanEngine


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $(LIBPATH) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*