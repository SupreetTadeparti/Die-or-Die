#include "Entity.hpp"

namespace Moon
{
	Entity::Entity(Model* model, Vec3 translation, Vec3 rotation, Vec3 scale) : m_Model(model), m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
	{
		m_Material = m_Model->GetMaterial();
		UpdateModelMatrix();
	}

	void Entity::SetMaterial(Material* material)
	{
		m_Material = material;
	}

	void Entity::Translate(Vec3 translation)
	{
		m_Translation += translation;
		UpdateModelMatrix();
	}

	void Entity::Rotate(Vec3 rotation)
	{
		m_Rotation += rotation;
		UpdateModelMatrix();
	}

	void Entity::Scale(Vec3 scale)
	{
		m_Scale += scale;
		UpdateModelMatrix();
	}

	void Entity::UpdateModelMatrix()
	{
		m_ModelMatrix =
			glm::translate(Mat4(1.0f), m_Translation) *
			glm::rotate(Mat4(1.0f), m_Rotation[0], Vec3(1, 0, 0)) *
			glm::rotate(Mat4(1.0f), m_Rotation[1], Vec3(0, 1, 0)) *
			glm::rotate(Mat4(1.0f), m_Rotation[2], Vec3(0, 0, 1)) *
			glm::scale(Mat4(1.0f), m_Scale);
	}
}