#include "Renderer.h"
#include "Mesh.h"
#include "../Core/File.h"
#include "../Core/Logger.h"
#include <sstream>

namespace viper {
	bool Mesh::Load(const std::string& file) {
		std::string buffer = "";
		if (!ReadTextFile(file, buffer)) {
			Logger::Error("Could not load mesh file: {}", file);
			return false;
		}

		std::stringstream stream(buffer);

		stream >> m_color;

		vec2 point;
		while (stream >> point) {
			m_points.push_back(point);
		}

		if (!stream.eof()) {
			Logger::Error("Error reading mesh file: {}", file);
			return false;
		}

		return true;
	}
	void Mesh::Draw(class Renderer& renderer, const vec2& position, float rotation, float scale) {
		if (m_points.empty()) return;

		renderer.SetColor(m_color.r, m_color.g, m_color.b);

		for (int i = 0; i < m_points.size() - 1; ++i) {
			const vec2& p1 = m_points[i].Rotate(math::degToRad(rotation)) * scale + position;
			const vec2& p2 = m_points[i + 1].Rotate(math::degToRad(rotation)) * scale + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Mesh::Draw(class Renderer& renderer, const Transform& transform) {
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
	void Mesh::CalculateRadius() {
		m_radius = 0;
		for (auto& point : m_points) {
			float length = point.Length();
			if (length > m_radius) {
				m_radius = length;
			}
		}
	}
}