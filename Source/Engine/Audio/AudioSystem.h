#pragma once  
#include <string>  
#include <map>  
#include <fmod.hpp>  

namespace viper {  
	class AudioSystem {  
	public:  
		AudioSystem() = default;  

		bool Initialize();  
		void Shutdown();  

		void Update();  

		bool AddSound(const std::string& filename, const std::string& name = "");  
		bool PlaySound(const std::string& name, bool loop = false);  

	private:  
		bool CheckFmodResult(FMOD_RESULT result);  

		FMOD::System* m_system = nullptr;  
		std::map<std::string, FMOD::Sound*> m_sounds;  
	};  
}
