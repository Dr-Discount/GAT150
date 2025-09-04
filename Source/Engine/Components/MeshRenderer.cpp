#include "MeshRenderer.h"
#include "SpriteRenderer.h"
#include "../Renderer/mesh.h"

namespace viper {
	FACTORY_REGISTER(MeshRenderer)

	void MeshRenderer::Update(float dt) {
		//
	}
	void MeshRenderer::Draw(Renderer& renderer) {
		auto mesh = Resources().Get<Mesh>(meshName);
		if (mesh) {
			mesh->Draw(renderer, owner->transform);
		}
	}
}