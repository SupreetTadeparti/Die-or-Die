#include "Camera.hpp"

namespace Moon
{
	Camera::Camera() : m_TranslationMatrix(1.0f), m_RotationMatrix(1.0f), m_ViewMatrix(1.0f), m_Rotation(0.0f)
	{
	}

	void Camera::Move(Vec3 translation)
	{
		m_TranslationMatrix = glm::translate(m_TranslationMatrix, -translation);
		UpdateViewMatrix();
	}

	void Camera::Move(Double x, Double y, Double z)
	{
		Move(Vec3(x, y, z));
	}

	void Camera::Rotate(Vec3 rotation)
	{
		m_Rotation.x = (float)std::max(std::min((long double)(m_Rotation.x + rotation.x), Math::PI / 2), -Math::PI / 2);
		m_Rotation.y += rotation.y;
		auto yaw = glm::angleAxis(m_Rotation.x, Vec3(1, 0, 0));
		auto pitch = glm::angleAxis(m_Rotation.y, Vec3(0, 1, 0));
		m_RotationMatrix = glm::mat4_cast(yaw * pitch);
		UpdateViewMatrix();
	}

	void Camera::Rotate(Double x, Double y, Double z)
	{
		Rotate(Vec3(x, y, z));
	}

	void Camera::UpdateViewMatrix()
	{
		m_ViewMatrix = m_RotationMatrix * m_TranslationMatrix;
	}
}