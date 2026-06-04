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

		/// <summary>
		/// Abstract base class representing a 3D model composed of one or more meshes and materials.
		/// </summary>
		class MeshModel : public Asset, public GraphicsAsset, public FileAsset {
		public:
			MeshModel(const std::string& name)
				: Asset(name) {}
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