#include <lnapch.h>
#include "OrthoController.h"

#include "luna/events/Event.h"

#include "luna/core/Input.h"
#include "luna/core/KeyCodes.h"

namespace luna
{
	OrthoController::OrthoController(float width, float height, bool rotation) :
		m_AspectRatio(width / height), m_Camera(-m_AspectRatio * m_Zoom, m_AspectRatio* m_Zoom, -m_Zoom, m_Zoom), m_Rotation(rotation)
	{
	}

	void OrthoController::OnUpdate(Timestep ts)
	{
		LNA_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(LNA_KEY_UP))
		{
			m_CamPosition.x += -sin(glm::radians(m_CamRotation)) * m_TranslateSpeed * ts;
			m_CamPosition.y += cos(glm::radians(m_CamRotation)) * m_TranslateSpeed * ts;
		}
		else if (Input::IsKeyPressed(LNA_KEY_DOWN))
		{
			m_CamPosition.x -= -sin(glm::radians(m_CamRotation)) * m_TranslateSpeed * ts;
			m_CamPosition.y -= cos(glm::radians(m_CamRotation)) * m_TranslateSpeed * ts;
		}

		if (Input::IsKeyPressed(LNA_KEY_LEFT))
		{
			m_CamPosition.x -= cos(glm::radians(m_CamRotation)) * m_TranslateSpeed * ts;
			m_CamPosition.y -= sin(glm::radians(m_CamRotation)) * m_TranslateSpeed * ts;
		}
		else if (Input::IsKeyPressed(LNA_KEY_RIGHT))
		{
			m_CamPosition.x += cos(glm::radians(m_CamRotation)) * m_TranslateSpeed * ts;
			m_CamPosition.y += sin(glm::radians(m_CamRotation)) * m_TranslateSpeed * ts;
		}


		if (m_Rotation)
		{
			if (Input::IsKeyPressed(LNA_KEY_Q))
				m_CamRotation += m_RotationSpeed * ts;
			else if (Input::IsKeyPressed(LNA_KEY_E))
				m_CamRotation -= m_RotationSpeed * ts;

			if (m_CamRotation > 180.0f)
				m_CamRotation -= 360.0f;
			else if (m_CamRotation <= -180.0f)
				m_CamRotation += 360.0f;

			m_Camera.SetRotation(m_CamRotation);
		}

		m_Camera.SetPosition(m_CamPosition);
		m_TranslateSpeed = m_Zoom;
	}

	void OrthoController::OnEvent(Event& e)
	{
		LNA_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowResizeEvent>(LNA_BIND_EVENT_FN(OrthoController::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(LNA_BIND_EVENT_FN(OrthoController::OnMouseScrolled));
	}

	void OrthoController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		UpdateProjection();
	}

	void OrthoController::UpdateProjection()
	{
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
	}

	bool OrthoController::OnWindowResized(WindowResizeEvent& e)
	{
		LNA_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

	bool OrthoController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		LNA_PROFILE_FUNCTION();

		m_Zoom -= e.GetYOffset() * 0.25f;
		m_Zoom = std::max(m_Zoom, 0.25f);
		UpdateProjection();

		return false;
	}
}