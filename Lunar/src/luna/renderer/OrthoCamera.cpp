#include <lnapch.h>
#include "OrthoCamera.h"

#include <glm/ext.hpp>

namespace luna
{
	OrthoCamera::OrthoCamera(float left, float right, float bot, float top) :
		m_Position(0.0f), m_ProjectionMatrix(glm::ortho(left, right, bot, top)), m_ViewMatrix(1.0f)
	{
		LNA_PROFILE_FUNCTION();
		m_CombinedMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthoCamera::SetProjection(float left, float right, float bot, float top)
	{
		LNA_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, bot, top);
		m_CombinedMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthoCamera::UpdateMatrices()
	{
		LNA_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_CombinedMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}