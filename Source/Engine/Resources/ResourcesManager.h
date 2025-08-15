#pragma once
#include "Resource.h"
#include "../Core/Logger.h"
#include <string>
#include <map>

namespace viper {
	class ResourceManager {
	public:
		template <typename T,  typename ... TArgs>
		res_t<T> Get(const std::string& name, TArgs&& ... args);

		static ResourceManager& Instance() {
			static ResourceManager instance;
			return instance;
		}

	private:
		ResourceManager() = default;

		std::map<std::string, res_t<Resource>> m_resources;
	};

	template <typename T, typename ... TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& name, TArgs&& ... args) {
		std::string key = name;

		auto iter = m_resources.find(key);

		if (iter != m_resources.end()) {
			auto base = iter->second;
			auto resource = std::dynamic_pointer_cast<T>(base);
			if (resource == nullptr) {
				Logger::Info("Resource type mismatch: ", key);
				return res_t<T>();
			}
			return resource;
		}

		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(key, std::forward<TArgs>(args)...) == false) {
			Logger::Info("Failed to load resource: ", key);
			return res_t<T>();
		}

		m_resources[key] = resource;

		return resource; 

	}
		ResourceManager& Resources() {return ResourceManager::Instance();}
}