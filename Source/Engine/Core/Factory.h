#pragma once
#include "../Framework/Actor.h"
#include "../Framework/Object.h"
#include "Singleton.h"
#include "Logger.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname)
    #define FACTORY_REGISTER(classname) \
    class Register##classname { \
    public: \
        Register##classname() { \
            viper::Factory::Instance().Register<classname>(#classname); \
        } \
    }; \
    static Register##classname global_Register##classname;

namespace viper {

	class CreatorBase {
	public:
		virtual ~CreatorBase() = default;
		virtual std::unique_ptr<Object> Create() = 0;
	};

	template<typename T>
	requires std::derived_from<T, Object>
	class Creator : public CreatorBase {
	public:
		std::unique_ptr<Object> Create() override {
			return std::make_unique<T>();
		}
	};
	
	template<typename T>
	requires std::derived_from<T, Object>
	class PrototypeCreator : public CreatorBase {
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) : m_prototype(std::move(prototype)) {}
		std::unique_ptr<Object> Create() override {
			return m_prototype->Clone();
		}

	private:
		std::unique_ptr<T> m_prototype;
	};


	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);
		
		template<typename T>
		requires std::derived_from<T, Object>
		void PrototypeRegister(const std::string& name, std::unique_ptr<T> prototype);

		template<typename T = Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
	};

	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& name) {
		m_registry[name] = std::make_unique<Creator<T>>();
		Logger::Info("Registered factory object: {}", name);
	}

	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::PrototypeRegister(const std::string& name, std::unique_ptr<T> prototype) {
		m_registry[name] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
		Logger::Info("Registered prototype factory object: {}", name);
	}

	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& name) {
		auto it = m_registry.find(name);
		if (it != m_registry.end()) {
			auto object = it->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if (derived) {
				Logger::Info("Created factory object: {}", name);
				object.release();
				return std::unique_ptr<T>(derived);
			}
			Logger::Error("Type mismatch of factory object: {}", name);
		} else {
			Logger::Error("Could not create factory object: {}", name);
		}
		return nullptr;
	}

	template<typename T = Actor>
	requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name) {
		return Factory::Instance().Create<T>(name);
	}

	template<typename T = Actor>
	requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name, const vec2& position, float rotation, float scale) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->transform = Transform{ position, rotation, scale };
		return instance;
	}

	template<typename T = Actor>
	requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name, const Transform& transform) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->transform = transform;
		return instance;
	}
}