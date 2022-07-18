#include "Model.hpp"

namespace Moon
{
	const Vec4 Model::s_DefaultColor(255.0f / 2, 255.0f / 2, 255.0f / 2, 1.0f);

	Model::Model(const String& name, VertexArray* vao) : m_Shader(Shader::GenerateDefaultColor()), m_VertexArray(vao), m_Material(new Material(MaterialType::Color, new Color(s_DefaultColor))), m_Name(name)
	{
	}

	Model::Model(const String& name, VertexArray* vao, Material* material) : m_Shader(material->GetMaterialType() == MaterialType::Texture ? Shader::GenerateDefaultTexture() : Shader::GenerateDefaultColor()), m_VertexArray(vao), m_Material(material), m_Name(name)
	{
	}

	Model::Model(const String& name, Shader* shader, VertexArray* vao) : m_Shader(shader), m_VertexArray(vao), m_Material(new Material(MaterialType::Color, new Color(s_DefaultColor))), m_Name(name)
	{
	}

	Model::Model(const String& name, Shader* shader, VertexArray* vao, Material* material) : m_Shader(shader), m_VertexArray(vao), m_Material(material), m_Name(name)
	{
	}

	void Model::SetVertexArray(VertexArray* vao)
	{
		m_VertexArray = vao;
	}

	void Model::SetMaterial(Material* material)
	{
		m_Material = material;
	}

	void Model::SetShader(Shader* shader)
	{
		m_Shader = shader;
	}

	void Model::Render() const
	{
		m_VertexArray->Render();
	}
}