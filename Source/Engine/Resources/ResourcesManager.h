#pragma once
#include "Resource.h"
#include "../Core/Logger.h"
#include "../Core/Singleton.h"
#include <string>
#include <map>

namespace viper {
	class ResourceManager : public Singleton<ResourceManager> {
	public:
		void Clear() { m_resources.clear(); }

		template <typename T,  typename ... Args>
		res_t<T> Get(const std::string& name, Args&& ... args);

		template <typename T, typename ... Args>
		res_t<T> GetWithID(const std::string& id, const std::string& name, Args&& ... args);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

		std::map<std::string, res_t<Resource>> m_resources;
	};

	template <typename T, typename ... Args>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args) {
		return GetWithID<T>(name, name, std::forward<Args>(args)...);
	}

	template<typename T, typename ...Args>
	inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, Args && ...args) {
		std::string key = id;

		auto iter = m_resources.find(name);

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
		if (resource->Load(name, std::forward<Args>(args)...) == false) {
			Logger::Info("Failed to load resource: ", name);
			return res_t<T>();
		}

		m_resources[key] = resource;

		return resource;
	}

	inline ResourceManager& Resources() {return ResourceManager::Instance();}
}