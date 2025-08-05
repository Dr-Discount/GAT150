#include "engine.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

namespace viper {
	Engine& GetEngine() {
		static Engine engine;
		return engine;
	}

	bool Engine::Initialize() {
	    m_renderer = std::make_unique<viper::Renderer>();
		m_renderer->Initialize();
		m_renderer->CreateWindow("Viper Engine", 1280, 1024);
		
		m_input = std::make_unique<viper::InputSystem>();
		m_input->Initialize();

		m_audio = std::make_unique<viper::AudioSystem>();
		m_audio->Initialize();
		
		m_particleSystem = std::make_unique<viper::ParticleSystem>();
		m_particleSystem->Initialize();

		return true;
	}

	void Engine::Update() {
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
	}

	void Engine::Shutdown() {
		m_audio->Shutdown();
		m_input->Shutdown();
		m_renderer->Shutdown();
	}

	void Engine::Draw() {
		
	}
}