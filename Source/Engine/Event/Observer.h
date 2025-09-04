#pragma once

namespace viper {
	class Observer {
	public:
		virtual ~Observer();

		virtual void OnNotify(const Event& event) = 0;
	};
}
