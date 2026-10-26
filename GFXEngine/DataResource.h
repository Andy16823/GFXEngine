#pragma once
#include "Asset.h"
#include <nlohmann/json.hpp>
#include <string>
#include <span>
#include <initializer_list>

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// DataResource class represents a data resource that can be loaded from a file and contains JSON data.
		/// </summary>
		class DataResource 
			: public Asset, public FileAsset
		{
		private:
			bool m_loaded = false;

		public:
			nlohmann::json data;

		public:
			DataResource(const std::string& name, const std::string& filePath) 
				: Asset(name) { this->setFilePath(filePath); }
			virtual ~DataResource() = default;
			
		public:
			void load() override;
			void unload() override;
			bool isLoaded() const override { return m_loaded; }

		public:
			bool hasProperty(const std::string& propertyName) const;
			bool hasProperty(std::span<std::string> propertyPath) const;
			const nlohmann::json* findProperty(std::span<const std::string> path) const;
			const nlohmann::json* findProperty(std::initializer_list<std::string> path) const;
		};
	}
}