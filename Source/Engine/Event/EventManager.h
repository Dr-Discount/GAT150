#pragma once
#include "../Core/Singleton.h"
#include "Observer.h"
#include "Event.h"
#include <map>
#include <list>

namespace viper {
	class EventManager : public Singleton<EventManager> {
	public:
		void AddObserver(const Event::id_t id, Observer& observer);
		void RemoveObserver(Observer& observer);

		void Notify(const Event::id_t id, Event::data_t data);
	private:
		std::map<Event::id_t, std::list<Observer*>> m_observers;

	};
}