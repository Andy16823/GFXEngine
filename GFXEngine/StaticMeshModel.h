#pragma once
#include "Mesh3D.h"
#include "MeshModel.h"
#include <vector>
#include "PBRMaterial.h"


namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// StaticMeshModel is a concrete implementation of the MeshModel interface for rendering static 3D models loaded from files.
		/// </summary>
		class StaticMeshModel : public MeshModel {
		private:
			std::vector<std::unique_ptr<Material>> m_materials;
			std::vector<Mesh3D> m_meshes;
			bool m_initialized = false;
			bool m_loaded = false;
			std::string m_filePath;

		public:
			StaticMeshModel(const std::string& name) : MeshModel(name) {}
			
			// GraphicsAsset interface implementation
			void init(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;
			bool isInitialized() const override { return m_initialized; }

			// FileAsset interface implementation
			void load(const std::string& filePath) override;
			bool isLoaded() const override { return m_loaded; }
			const std::string& getFilePath() const override { return m_filePath; }

			const Mesh3D& getMesh(size_t index) const override { return m_meshes.at(index); }
			const Material& getMeshMaterial(size_t index) const override { return *m_materials.at(index % m_materials.size()); }
			size_t getMeshCount() const override { return m_meshes.size(); }
		};
	}
}
