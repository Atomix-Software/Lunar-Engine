#pragma once

#include <glm/glm.hpp>

namespace luna
{
	class OrthoCamera
	{
	public:
		OrthoCamera(float left = -1.0f, float right = 1.0f, float bot = -1.0f, float top = 1.0f);
		
		void SetProjection(float left, float right, float bot, float top);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; UpdateMatrices(); }
	
		inline float GetRotation() const { return m_Rotation; }
		inline void SetRotation(float rotation) { m_Rotation = rotation; UpdateMatrices(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_CombinedMatrix; }
	private:
		void UpdateMatrices();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_CombinedMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}