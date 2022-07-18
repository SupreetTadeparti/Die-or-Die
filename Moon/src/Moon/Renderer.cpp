#include "Renderer.hpp"

namespace Moon
{
	Map<String, Model*> Renderer::s_ModelNameModelMap;
	Map<String, List<Entity*>> Renderer::s_ModelNameEntityMap;
	Vec3 Renderer::s_BackgroundColor(0.7f);

	void Renderer::AddEntity(Entity* entity)
	{
		s_ModelNameModelMap[entity->GetModel()->GetName()] = entity->GetModel();
		s_ModelNameEntityMap[entity->GetModel()->GetName()].push_back(entity);
	}

	void Renderer::RemoveEntity(Entity* entity)
	{
		List<Entity*> entities = s_ModelNameEntityMap[entity->GetModel()->GetName()];
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
		s_ModelNameEntityMap[entity->GetModel()->GetName()] = entities;
	}

	void Renderer::AddText(Text* text)
	{
		for (Entity* entity : text->GetCharacters())
		{
			AddEntity(entity);
		}
	}

	void Renderer::Prepare()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(s_BackgroundColor.r, s_BackgroundColor.g, s_BackgroundColor.b, 1.0f);
	}

	void Renderer::Render()
	{
		for (const auto& pair : s_ModelNameEntityMap)
		{
			Model* model = s_ModelNameModelMap[pair.first];
			model->GetVertexArray()->Bind();
			model->GetVertexArray()->GetIndexBuffer()->Bind();
			model->GetShader()->Bind();
			for (const auto& entity : pair.second)
			{
				MaterialType materialType = entity->GetMaterial()->GetMaterialType();
				if (materialType == MaterialType::Color)
				{
					model->GetShader()->SetUniformVec4("u_Color", entity->GetMaterial()->GetColor()->GetColor());
				}
				else if (materialType == MaterialType::Texture)
				{
					model->GetShader()->SetUniformInt("u_Texture", 0);
					entity->GetMaterial()->GetTexture()->Bind(0);
				}
				model->GetShader()->SetUniformMat4("u_Model", entity->GetModelMatrix());
				model->Render();
			}
			model->GetShader()->Unbind();
			model->GetVertexArray()->GetIndexBuffer()->Unbind();
			model->GetVertexArray()->Unbind();
		}
	}
}