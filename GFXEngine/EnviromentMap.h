#pragma once
#include "Entity.h"
#include "Imaging.h"
#include "Asset.h"
#include "PositionMesh.h"
#include "EnviromentMaterial.h"

#include <cassert>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// EnviromentMap asset type
		/// </summary>
		class EnviromentMap : public GFXEngine::Asset
		{
		private:
			std::unique_ptr<PositionMesh> m_mesh;
			std::unique_ptr<EnviromentMaterial> m_envMaterial;

		public:
			EnviromentMap(const std::string& name, const nlohmann::json& data);
			EnviromentMap(const std::string& name, const std::vector<std::string>& faceFilepaths);

			void init(GFXEngine::Graphics::Renderer& renderer);
			void destroy(GFXEngine::Graphics::Renderer& renderer);

			const EnviromentMaterial& getMaterial() const { 
				assert(m_envMaterial);
				return *m_envMaterial; 
			}

			const PositionMesh& getMesh() const { 
				assert(m_mesh);
				return *m_mesh; 
			}
		};
	}
}