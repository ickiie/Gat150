#include "EventSystem.h"
#include "Object/Object.h"

void nc::EventSystem::Startup() {

}

void nc::EventSystem::Shutdown() {

}

void nc::EventSystem::Update(float dt) {

}

void nc::EventSystem::Subscribe(const std::string& name, function_t function, Object* receiver) {

	Observer observer;
	observer.function = function;
	observer.receiver = receiver;

	observers[name].push_back(observer);
}

void nc::EventSystem::Unsubscribe(const std::string& name, Object* receiver)
{
     auto& eventObservers = observers[name];
     for (auto iter = eventObservers.begin(); iter != eventObservers.end();)
     {
         if (iter->receiver == receiver)
         {
            iter = eventObservers.erase(iter);
         }
         else
         {
            iter++;
         }
     }
}

void nc::EventSystem::Notify(const Event& event) {

	auto& eventObservers = observers[event.name];
	for (auto& observer : eventObservers) {

		if (event.receiver == nullptr || event.receiver == observer.receiver)
		observer.function(event);
	}
}
