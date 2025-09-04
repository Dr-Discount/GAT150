#include "../EnginePCH.h"
#include "SpriteRenderer.h"
#include "../Renderer/Renderer.h"

namespace viper {
    FACTORY_REGISTER(SpriteRenderer)

	void SpriteRenderer::Update(float dt) {
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer) {
		renderer.DrawTexture(Resources().Get<Texture>(textureName, renderer).get(), owner->transform.position.x, owner->transform.position.y, owner->transform.rotation, owner->transform.scale);
	}
	void SpriteRenderer::Read(const json::value_t& value) {
		Object::Read(value);
		JSON_READ_NAME(value, "textureName", textureName);
	}
}
