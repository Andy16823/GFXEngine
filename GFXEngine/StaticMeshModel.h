#pragma once
#include "Mesh3D.h"
#include "MeshModel.h"
#include <vector>
#include "PBRMaterial.h"


namespace GFXEngine {
	namespace Graphics {

		class StaticMeshModel : public MeshModel {
		private:
			std::vector<std::unique_ptr<Material>> m_materials;
			std::vector<Mesh3D> m_meshes;
			bool m_initialized = false;
			bool m_loaded = false;

		public:
			//************************************
			// Method:    StaticMeshModel
			// FullName:  GFXEngine::Graphics::StaticMeshModel::StaticMeshModel
			// Access:    public 
			// Returns:   
			// Qualifier: : MeshModel(name, filePath)
			// Parameter: const std::string & name
			// Parameter: const std::string & filePath
			//************************************
			StaticMeshModel(const std::string& name, const std::string& filePath) : MeshModel(name, filePath) {}
			
		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::StaticMeshModel::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::StaticMeshModel::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer) override;
			
			//************************************
			// Method:    isInitialized
			// FullName:  GFXEngine::Graphics::StaticMeshModel::isInitialized
			// Access:    public 
			// Returns:   bool
			// Qualifier: const 
			//************************************
			bool isInitialized() const override { return m_initialized; }

			//************************************
			// Method:    load
			// FullName:  GFXEngine::Graphics::StaticMeshModel::load
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void load() override;
			
			//************************************
			// Method:    unload
			// FullName:  GFXEngine::Graphics::StaticMeshModel::unload
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void unload() override;
			
			//************************************
			// Method:    isLoaded
			// FullName:  GFXEngine::Graphics::StaticMeshModel::isLoaded
			// Access:    public 
			// Returns:   bool
			// Qualifier: const 
			//************************************
			bool isLoaded() const override { return m_loaded; }

			//************************************
			// Method:    getMesh
			// FullName:  GFXEngine::Graphics::StaticMeshModel::getMesh
			// Access:    public 
			// Returns:   const GFXEngine::Graphics::Mesh3D&
			// Qualifier: const 
			// Parameter: size_t index
			//************************************
			const Mesh3D& getMesh(size_t index) const override { return m_meshes.at(index); }
			
			//************************************
			// Method:    getMeshMaterial
			// FullName:  GFXEngine::Graphics::StaticMeshModel::getMeshMaterial
			// Access:    public 
			// Returns:   const GFXEngine::Graphics::Material&
			// Qualifier: const 
			// Parameter: size_t index
			//************************************
			const Material& getMeshMaterial(size_t index) const override { return *m_materials.at(index % m_materials.size()); }
			
			//************************************
			// Method:    getMeshCount
			// FullName:  GFXEngine::Graphics::StaticMeshModel::getMeshCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const 
			//************************************
			size_t getMeshCount() const override { return m_meshes.size(); }
		};
	}
}