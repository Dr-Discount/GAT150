#pragma once
#include "RendererComponent.h"

namespace viper {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

		void Update(float dt) override;
		void Draw(Renderer& renderer) override;
	};
}