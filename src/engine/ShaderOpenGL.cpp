
#include "ShaderOpenGL.h"
#include "FileReader.h"

#ifdef OPENGL


ShaderOpenGL::ShaderOpenGL(ShaderCreateDesc createDesc)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)sizeof(Vec3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)sizeof(Vec3));

    LoadShaders(createDesc);
}

ShaderOpenGL::~ShaderOpenGL()
{

}

void ShaderOpenGL::LoadShaders(ShaderCreateDesc createDesc)
{
    auto vertShaderCode = File::ReadFile(createDesc.vertexShaderPath);
    auto fragShaderCode = File::ReadFile(createDesc.fragmentShaderPath);

    unsigned int program = glCreateProgram();

    CreateShader(GL_VERTEX_SHADER, vertShaderCode, program);
    CreateShader(GL_FRAGMENT_SHADER, fragShaderCode, program);

    glLinkProgram(program);
}

void ShaderOpenGL::CreateShader(unsigned int type, std::vector<char> binary, unsigned int program)
{
    unsigned int shaderID = glCreateShader(type);
    glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, binary.data(), binary.size());
    glSpecializeShader(shaderID, "main", 0, 0, 0);

    int compiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
    if (compiled)
        glAttachShader(program, shaderID);
}

#endif // OPENGL