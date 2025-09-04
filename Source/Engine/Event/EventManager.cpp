#include "EventManager.h"

namespace viper {
	void EventManager::AddObserver(const Event::id_t id, Observer& observer) {
		m_observers[id].push_back(&observer);
	}

	void EventManager::RemoveObserver(Observer& observer) {
		Observer* obs = &observer;
		for (auto& eventType : m_observers) {
			auto observers = eventType.second;
			std::erase_if(observers, [obs](auto observer) {
				return (observer == obs);
			});
		}
	}

	void EventManager::Notify(const Event::id_t id, Event::data_t data) {
		
	}
}