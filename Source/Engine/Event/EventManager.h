#pragma once
#include "../Core/Singleton.h"
#include "Observer.h"
#include "Event.h"
#include <map>
#include <list>

#define OBSERVER_ADD(event_id)				viper::EventManager::Instance().AddObserver(#event_id, *this)
#define OBSERVER_REMOVE_SELF				viper::EventManager::Instance().RemoveObserver(*this)
#define EVENT_NOTIFY_DATA(event_id, data)	viper::EventManager::Instance().Notify({ #event_id, data })
#define EVENT_NOTIFY(event_id)				viper::EventManager::Instance().Notify({ #event_id, true })

namespace viper {
	class EventManager : public Singleton<EventManager> {
	public:
		void AddObserver(const Event::id_t id, Observer& observer);
		void RemoveObserver(Observer& observer);
		void RemoveAllObservers() { m_observers.clear(); }

		void Notify(const Event& event);
	private:
		std::map<Event::id_t, std::list<Observer*>> m_observers;

	};
}