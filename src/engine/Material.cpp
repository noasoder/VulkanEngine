
#include "Material.h"
#include "GraphicsPipeline.h"
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
	GraphicsPipeline::PipelineCreateDesc pipelineCreateDesc{};

	pipelineCreateDesc.vertexShaderPath = createDesc.shaderName + "_vert.spv";
	pipelineCreateDesc.fragmentShaderPath = createDesc.shaderName + "_frag.spv";

	CreateGraphicsPipeline(pipelineCreateDesc);
}

void Material::RecreatePipeline()
{
	CreatePipeline(m_createDesc);
}

void Material::DeletePipeline()
{
	CreatePipeline(m_createDesc);
}