#pragma once  
#include <vector>
#include "../Math/Vector2.h"
#include <array>

namespace viper {  
	class InputSystem {  
	public:
		enum MouseButton {
			Left,
			Middle,
			Right
		};

		int i = MouseButton::Right;

	public:  
		InputSystem() = default;  

		bool Initialize();  
		void Shutdown();  

		void Update();  

		bool GetKeyDown(uint8_t key) const { return m_keyboardState[key]; }
		bool GetPreviousKeyDown(uint8_t key) const { return m_previousKeyboardState[key]; }
		bool GetKeyPressed(uint8_t key) const { return m_keyboardState[key] && !m_previousKeyboardState[key]; }
		bool GetKeyReleased(uint8_t key) const { return !m_keyboardState[key] && m_previousKeyboardState[key]; }

		bool GetMouseButtonDown(MouseButton button) { return m_mouseButtonState[button]; }
		bool GetPreviousMouseButtonDown(MouseButton button) { return m_previousMouseButtonState[button]; }
		bool GetMouseButtonPressed(MouseButton button) { return m_mouseButtonState[button] && !m_previousMouseButtonState[button]; }
		bool GetMouseButtonReleased(MouseButton button) { return !m_mouseButtonState[button] && m_previousMouseButtonState[button]; }

		const vec2& GetMousePosition() const { return m_mousePosition; }
		const vec2& GetPreviousMousePosition() const { return m_previousMousePosition; }
	private:  
		std::vector<bool> m_keyboardState;  
		std::vector<bool> m_previousKeyboardState;  

		vec2 m_mousePosition{0,0};
		vec2 m_previousMousePosition{0,0};

		std::array<bool,3>m_mouseButtonState{ false, false, false };
		std::array<bool,3>m_previousMouseButtonState{ false, false, false };
	};  
}