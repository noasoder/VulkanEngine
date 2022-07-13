
#include "Material.h"
#include "Shader.h"
#include "Managers/MaterialManager.h"

Material::Material(MaterialCreateDesc& createDesc)
{
	m_createDesc = createDesc;
	CreatePipeline(createDesc);
}

Material::~Material()
{

}

void Material::CreatePipeline(MaterialCreateDesc& createDesc)
{
	ShaderCreateDesc ShaderCreateDesc{};

	ShaderCreateDesc.vertexShaderPath = createDesc.shaderName + "_vert.spv";
	ShaderCreateDesc.fragmentShaderPath = createDesc.shaderName + "_frag.spv";

#ifdef VULKAN
	CreateShader(ShaderCreateDesc);
#endif
}

void Material::RecreatePipeline()
{
	CreatePipeline(m_createDesc);
}

void Material::DeletePipeline()
{
	CreatePipeline(m_createDesc);
}