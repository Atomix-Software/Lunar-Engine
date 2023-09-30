#pragma once

#include "luna/renderer/OrthoCamera.h"
#include "luna/core/Timestep.h"

#include "luna/events/ApplicationEvent.h"
#include "luna/events/MouseEvent.h"

namespace luna
{

	class OrthoController
	{
	public:
		OrthoController(float width = 1280, float height = 720, bool rotation = false, bool debugInput = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		inline OrthoCamera& GetCamera() { return m_Camera; }
		inline const OrthoCamera& GetCamera() const { return m_Camera; }

		inline float GetZoom() { return m_Zoom; }
		inline void SetZoom(float zoom) { m_Zoom = zoom; UpdateProjection(); }
	private:
		void UpdateProjection();
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
	private:
		float m_AspectRatio;
		float m_Zoom = 1.0f;

		OrthoCamera m_Camera;

		bool m_DebugInput;
		bool m_Rotation;

		glm::vec3 m_CamPosition = { 0.0f, 0.0f, 0.0f };
		float m_CamRotation = 0.0f;
		float m_TranslateSpeed = 5.0f, m_RotationSpeed = 180.0f;
	};
}