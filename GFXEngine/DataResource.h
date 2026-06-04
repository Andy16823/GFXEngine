#pragma once
#include "Asset.h"
#include <nlohmann/json.hpp>
#include <string>
#include <span>
#include <initializer_list>

namespace GFXEngine {
	namespace Core {
		class DataResource : public Asset, public FileAsset
		{
		private:
			bool m_loaded = false;
			std::string m_filePath;

		public:
			DataResource(const std::string& name) : Asset(name) {}
			virtual ~DataResource() = default;
			nlohmann::json data;

			void load(const std::string& filePath) override;
			bool isLoaded() const override { return m_loaded; }
			const std::string& getFilePath() const override { return m_filePath; }

			bool hasProperty(const std::string& propertyName) const;
			bool hasProperty(std::span<std::string> propertyPath) const;
			const nlohmann::json* findProperty(std::span<const std::string> path) const;
			const nlohmann::json* findProperty(std::initializer_list<std::string> path) const;
		};
	}
}