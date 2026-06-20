#pragma once
#include "Renderer.h"
#include "Functional"
#include "Material.h"
#include "Mesh3D.h"
#include "Asset.h"

namespace GFXEngine {
	namespace Graphics {

		enum class MaterialType {
			Unlit,
			PBR
		};

		class MeshModel : public Asset, public GraphicsAsset, public FileAsset {
		public:

			//************************************
			// Method:    MeshModel
			// FullName:  GFXEngine::Graphics::MeshModel::MeshModel
			// Access:    public 
			// Returns:   
			// Qualifier: : Asset(name), FileAsset(filePath)
			// Parameter: const std::string & name
			// Parameter: const std::string & filePath
			//************************************
			MeshModel(const std::string& name, const std::string& filePath)
				: Asset(name), FileAsset(filePath) {}
			
			//************************************
			// Method:    MeshModel
			// FullName:  GFXEngine::Graphics::MeshModel::MeshModel
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~MeshModel() = default;

			//************************************
			// Method:    MeshModel
			// FullName:  GFXEngine::Graphics::MeshModel::MeshModel
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const MeshModel &
			//************************************
			MeshModel(const MeshModel&) = delete;
			
			//************************************
			// Method:    MeshModel
			// FullName:  GFXEngine::Graphics::MeshModel::MeshModel
			// Access:    public 
			// Returns:   GFXEngine::Graphics::MeshModel&
			// Qualifier: = delete
			// Parameter: const MeshModel &
			//************************************
			MeshModel& operator=(const MeshModel&) = delete;
			
			//************************************
			// Method:    MeshModel
			// FullName:  GFXEngine::Graphics::MeshModel::MeshModel
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: MeshModel & &
			//************************************
			MeshModel(MeshModel&&) = default;
			
			//************************************
			// Method:    MeshModel
			// FullName:  GFXEngine::Graphics::MeshModel::MeshModel
			// Access:    
			// Returns:   MeshModel&
			// Qualifier: = default
			// Parameter: MeshModel & &
			//************************************
			MeshModel& operator=(MeshModel&&) = default;

			//************************************
			// Method:    getMeshCount
			// FullName:  GFXEngine::Graphics::MeshModel::getMeshCount
			// Access:    virtual public 
			// Returns:   std::size_t
			// Qualifier: const
			//************************************
			virtual size_t getMeshCount() const = 0;
			
			//************************************
			// Method:    getMesh
			// FullName:  GFXEngine::Graphics::MeshModel::getMesh
			// Access:    virtual public 
			// Returns:   const GFXEngine::Graphics::Mesh3D&
			// Qualifier: const
			// Parameter: size_t index
			//************************************
			virtual const Mesh3D& getMesh(size_t index) const = 0;
			
			//************************************
			// Method:    getMeshMaterial
			// FullName:  GFXEngine::Graphics::MeshModel::getMeshMaterial
			// Access:    virtual public 
			// Returns:   const GFXEngine::Graphics::Material&
			// Qualifier: const
			// Parameter: size_t index
			//************************************
			virtual const Material& getMeshMaterial(size_t index) const = 0;
		};
	}
}