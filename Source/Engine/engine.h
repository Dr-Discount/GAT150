#pragma once
#include "Core/Time.h"
#include <memory>

namespace viper {
	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Update();
		void Shutdown();
		void Draw();

		class Renderer& GetRenderer() { return *m_renderer; }
		class AudioSystem& GetAudioSystem() { return *m_audio; }
		class InputSystem& GetInputSystem() { return *m_input; }
		class ParticleSystem& GetPS() { return *m_particleSystem; }
		class Time& GetTime() { return m_time; }

	private:
		Time m_time;

		std::unique_ptr<class Renderer> m_renderer;
		std::unique_ptr<class AudioSystem> m_audio;
		std::unique_ptr<class InputSystem> m_input;
		std::unique_ptr<class ParticleSystem> m_particleSystem;
	};
	Engine& GetEngine();
}