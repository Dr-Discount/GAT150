#include "AudioClip.h"
#include "AudioSystem.h"

namespace viper {
    bool AudioClip::Load(const std::string& filename, AudioSystem& audioSystem) {
		FMOD_RESULT result = audioSystem.m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &m_sound);
        if (!AudioSystem::CheckFmodResult(result)) return false;
		return true;
    }

    AudioClip::~AudioClip() {
		if (m_sound) m_sound->release();
    }
}