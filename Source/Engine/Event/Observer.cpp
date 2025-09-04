#include "Observer.h"
#include "EventManager.h"

namespace viper {
	viper::Observer::~Observer() {
		OBSERVER_REMOVE_SELF;
	}
}