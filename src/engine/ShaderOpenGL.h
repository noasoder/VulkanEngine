#pragma once 

#include "Types.h"
#include "Core.h"
#include "Shader.h"

class ShaderOpenGL
{
public:
	struct Vertex
	{
		Vec3 pos;
		Vec3 color;
		Vec2 texCoord;
	};

	ShaderOpenGL(ShaderCreateDesc createDesc);
	~ShaderOpenGL();
	void LoadShaders(ShaderCreateDesc createDesc);

private:
	void CreateShader(unsigned int type, std::vector<char> binary, unsigned int program);
	
};