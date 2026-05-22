#pragma once
#include "Asset.h"
#include <nlohmann/json.hpp>
#include <string>
#include <span>

namespace GFXEngine {
	namespace Core {
		class DataResource : public GFXEngine::Asset
		{
		public:
			DataResource(const std::string& name, const std::string& path);
			virtual ~DataResource() = default;
			nlohmann::json data;

			bool hasProperty(const std::string& propertyName) const;
			bool hasProperty(std::span<const std::string> propertyPath) const;
			const nlohmann::json* findProperty(std::span<const std::string> path) const;
		};
	}
}