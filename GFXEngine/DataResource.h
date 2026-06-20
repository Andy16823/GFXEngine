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

		public:
			nlohmann::json data;

		public:
			//************************************
			// Method:    DataResource
			// FullName:  GFXEngine::Core::DataResource::DataResource
			// Access:    public 
			// Returns:   
			// Qualifier: : Asset(name), FileAsset(filePath)
			// Parameter: const std::string & name
			// Parameter: const std::string & filePath
			//************************************
			DataResource(const std::string& name, const std::string& filePath) : Asset(name), FileAsset(filePath) {}
			
			//************************************
			// Method:    DataResource
			// FullName:  GFXEngine::Core::DataResource::DataResource
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~DataResource() = default;
			
			//************************************
			// Method:    DataResource
			// FullName:  GFXEngine::Core::DataResource::DataResource
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void load() override;
			
			//************************************
			// Method:    DataResource
			// FullName:  GFXEngine::Core::DataResource::DataResource
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void unload() override;
			
			//************************************
			// Method:    DataResource
			// FullName:  GFXEngine::Core::DataResource::DataResource
			// Access:    public 
			// Returns:   bool
			// Qualifier: const 
			//************************************
			bool isLoaded() const override { return m_loaded; }

			//************************************
			// Method:    hasProperty
			// FullName:  GFXEngine::Core::DataResource::hasProperty
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: const std::string & propertyName
			//************************************
			bool hasProperty(const std::string& propertyName) const;
			
			//************************************
			// Method:    hasProperty
			// FullName:  GFXEngine::Core::DataResource::hasProperty
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: std::span<std::string> propertyPath
			//************************************
			bool hasProperty(std::span<std::string> propertyPath) const;
			
			//************************************
			// Method:    findProperty
			// FullName:  GFXEngine::Core::DataResource::findProperty
			// Access:    public 
			// Returns:   const nlohmann::json*
			// Qualifier: const
			// Parameter: std::span<const std::string> path
			//************************************
			const nlohmann::json* findProperty(std::span<const std::string> path) const;
			
			//************************************
			// Method:    findProperty
			// FullName:  GFXEngine::Core::DataResource::findProperty
			// Access:    public 
			// Returns:   const nlohmann::json*
			// Qualifier: const
			// Parameter: std::initializer_list<std::string> path
			//************************************
			const nlohmann::json* findProperty(std::initializer_list<std::string> path) const;
		};
	}
}