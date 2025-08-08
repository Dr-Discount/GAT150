#include "Font.h"
#include "../Core/Logger.h"

namespace viper {
	Font::~Font() {
		if (m_ttfFont != nullptr) {
			TTF_CloseFont(m_ttfFont);
		}
	}

	bool Font::Load(const std::string& name, float fontSize) {
		m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (m_ttfFont == nullptr) {
			Logger::Info("Could not load font: ", name);
			return false;
		}

		return true;
	}
}