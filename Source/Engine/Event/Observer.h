#pragma once

namespace viper {
	class Observer {
		virtual ~Observer() = default;

		virtual void OnNotify(const Event& event) = 0;
	};
}
