#include "AudioSystem.h"  
#include <iostream>  
#include <fmod_errors.h>
#include "../Core/StringHelper.h"

namespace viper {  
	bool AudioSystem::CheckFmodResult(FMOD_RESULT result) {  
		if (result != FMOD_OK) {  
			std::cerr << FMOD_ErrorString(result) << std::endl;  
			return false;  
		}  
		return true;  
	}  

	bool AudioSystem::Initialize() {  
		FMOD_RESULT result = FMOD::System_Create(&m_system);  
		if (!CheckFmodResult(result)) {  
			return false;  
		}  

		void* extradriverdata = nullptr;  
		m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);  

		return true;  
	}  

	void AudioSystem::Shutdown() {  
		CheckFmodResult(m_system->release());  
	}  

	void AudioSystem::Update() {  
		CheckFmodResult(m_system->update());  
	}  

	bool AudioSystem::AddSound(const std::string& filename, const std::string& name) {  
		std::string key = name.empty() ? filename : name;  
		key = toLower(key);

		if (m_sounds.find(key) != m_sounds.end()) {  
			std::cerr << "AudioSystem : name already exists: " << key << std::endl;  
			return false;  
		}  

		FMOD::Sound* sound = nullptr;  
		FMOD_RESULT result = m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);  

		if (!CheckFmodResult(result)) return false;  
		m_sounds[key] = sound;  

		return true;  
	}  

	bool AudioSystem::PlaySound(const std::string& name, bool loop) {  
		std::string key = name;
		key = toLower(key);

		if (m_sounds.find(key) == m_sounds.end()) {  
			std::cerr << "AudioSystem : sound not found: " << key << std::endl;  
			return false;  
		}  

		FMOD_RESULT result = m_system->playSound(m_sounds[key], 0, false, nullptr);  
		if (!CheckFmodResult(result)) return false;  

		return true;  
	}  
}