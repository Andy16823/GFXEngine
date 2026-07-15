#pragma once
#include "Asset.h"
#include "Mesh.h"

#include <memory>

namespace GFXEngine {
	namespace Graphics {
		class MeshAsset : public Asset, public GraphicsAsset
		{
		private:
			bool m_initialized = false;
			std::unique_ptr<Mesh> m_mesh;

		public:
			//************************************
			// Method:    MeshAsset
			// FullName:  GFXEngine::Graphics::MeshAsset::MeshAsset
			// Access:    public 
			// Returns:   
			// Qualifier: : Asset(name), m_mesh(std::move(mesh))
			// Parameter: const std::string & name
			// Parameter: std::unique_ptr<Mesh> mesh
			// Description: Constructs a MeshAsset with the given name and mesh.
			//************************************
			MeshAsset(const std::string& name, std::unique_ptr<Mesh> mesh)
				: Asset(name), m_mesh(std::move(mesh)) {}

		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::MeshAsset::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Description: Initializes the mesh asset by initializing its mesh with the provided renderer.
			//************************************
			void init(Graphics::Renderer& renderer) override;

			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::MeshAsset::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Description: Destroys the mesh asset by destroying its mesh with the provided renderer.
			//************************************
			void destroy(Graphics::Renderer& renderer) override;

			//************************************
			// Method:    isInitialized
			// FullName:  GFXEngine::Graphics::MeshAsset::isInitialized
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Description: Checks if the mesh asset has been initialized.
			//************************************
			bool isInitialized() const override { return m_initialized; }

		public:
			//************************************
			// Method:    getMesh
			// FullName:  GFXEngine::Graphics::MeshAsset::getMesh
			// Access:    public 
			// Returns:   Mesh*
			// Qualifier:
			// Description: Returns a pointer to the mesh managed by this asset.
			//************************************
			Mesh* getMesh() { return m_mesh.get(); }

		};
	}
}
