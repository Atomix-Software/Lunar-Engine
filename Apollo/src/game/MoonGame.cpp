#include "MoonGame.h"
#include <random>

#include <luna/audio/VorbisOgg.hpp>

#include "ecs/Systems.h"

namespace game
{
	std::random_device rd;
	std::mt19937 rng(rd());

	ALCdevice* Device;
	ALCcontext* Context;

	using namespace luna;

	Shared<TextureAtlas2D> Stars[4];
	Shared<audio::OggStreamData> TestSound;

	MoonGame::MoonGame() :
		Layer("MoonGame"), m_CamControl(640.f, 640.f) {}

	void MoonGame::OnAttach()
	{
		Device = alcOpenDevice(nullptr);
		if (Device) {
			if (!alcCall(alcCreateContext, Context, Device, Device, nullptr))
			{
				LNA_ERROR("Failed to load Audio Context!");
				Application::Get().Close();
			}

			ALCboolean pass;
			alcCall(alcMakeContextCurrent, pass, Device, Context);
			if (!pass)
			{
				LNA_ERROR("Failed to make Audio Context Current!");
				Application::Get().Close();
			}

			alcCall(alcGetContextsDevice, Device, Device, Context);
		}

		TestSound = CreateShared<audio::OggStreamData>();
		if (!audio::create_stream_from_file("assets/audio/gameover.ogg", *TestSound.get()))
		{
			LNA_ERROR("Failed to load gameover.ogg");
			Application::Get().Close();
		}
		audio::start_ogg(*TestSound.get());


		m_Textures["stars"] = Texture2D::Create("assets/textures/stars.png");
		m_Textures["ship_rocks"] = Texture2D::Create("assets/textures/ship_rocks.png");

		m_Engine.AddSystem(new ecs::GameplaySystem(m_Textures, 0));
		m_Engine.AddSystem(new ecs::RenderSystem(m_CamControl, 1));
		m_Engine.AddSystem(new ecs::PlayerSystem(2));
		m_Engine.AddSystem(new ecs::MotionSystem(3));
		m_Engine.AddSystem(new ecs::CollisionSystem(4));
		m_Engine.Start();

		Stars[0] = TextureAtlas2D::CreateFromCoords(m_Textures["stars"], { 0, 0 }, { 16, 16 });
		Stars[1] = TextureAtlas2D::CreateFromCoords(m_Textures["stars"], { 1, 0 }, { 16, 16 });
		Stars[2] = TextureAtlas2D::CreateFromCoords(m_Textures["stars"], { 2, 0 }, { 16, 16 });
		Stars[3] = TextureAtlas2D::CreateFromCoords(m_Textures["stars"], { 3, 0 }, { 16, 16 });

		std::uniform_int_distribution<int> starGn(0, 3);
		for (int i = 0; i < 75; i++)
		{
			auto starLevel = starGn(rng);
			auto entity = m_Engine.CreateEntity("Star");
			m_Engine.AddComponent<component::Renderable>(entity, Stars[starLevel], 0.075f, 0.075f);
			m_Engine.AddComponent<component::Transform>(entity, glm::vec3(game::randf(-1.25, 1.25), randf(-1.25, 1.25), randf(-1.0f, -0.9f)), glm::vec3(0.0f, 0.0f, randf(0.0f, 360.0f)), glm::vec3(1.0f));
		}

		auto gameplay = m_Engine.CreateEntity("GamePlay");
		m_Engine.AddComponent<component::Gameplay>(gameplay);
	}

	void MoonGame::OnDetach()
	{
		m_Textures.clear();

		alcCall(alcGetCurrentContext, Context, Device);
		alcCall(alcGetContextsDevice, Device, Device, Context);

		ALCboolean success;
		alcCall(alcMakeContextCurrent, success, Device, nullptr);
		if(!success)
			LNA_ERROR("Failed to invalidate context!");

		if(!alcCall(alcDestroyContext, Device, Context))
			LNA_ERROR("Failed to destroy context!");

		if (!alCall(alcCloseDevice, Device))
			LNA_ERROR("Failed to close Audio Device!");
	}

	void MoonGame::OnUpdate(Timestep ts)
	{
		m_CamControl.OnUpdate(ts);

		audio::update_ogg(*TestSound.get());

		if (Input::IsKeyPressed(LNA_KEY_ESCAPE))
		{
			m_Engine.Stop();
			Application::Get().Close();
			return;
		}


		m_Engine.OnUpdate(ts);
	}

	void MoonGame::OnEvent(Event& event)
	{
		m_CamControl.OnEvent(event);
	}

}