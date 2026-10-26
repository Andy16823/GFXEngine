#pragma once
#include "Renderer.h"
#include <functional>
#include "Material.h"
#include "Mesh3D.h"
#include "Asset.h"

namespace GFXEngine {
	namespace Graphics {

		enum class MaterialType {
			Unlit,
			PBR
		};

		/// <summary>
		/// MeshModel class represents a 3D mesh model asset that can be used for rendering in a 3D scene. 
		/// It manages the loading, initialization, and destruction of the associated mesh and material resources.
		/// </summary>
		class MeshModel 
			: public Asset, public GraphicsAsset, public FileAsset {

		public:
			
			MeshModel(const std::string& name, const std::string& filePath)
				: Asset(name) { this->setFilePath(filePath); }
			
			virtual ~MeshModel() = default;
			MeshModel(const MeshModel&) = delete;
			MeshModel& operator=(const MeshModel&) = delete;
			MeshModel(MeshModel&&) = default;
			MeshModel& operator=(MeshModel&&) = default;

			virtual size_t getMeshCount() const = 0;
			virtual const Mesh3D& getMesh(size_t index) const = 0;
			virtual const Material& getMeshMaterial(size_t index) const = 0;
		};
	}
}