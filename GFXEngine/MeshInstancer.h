#pragma once
#include "Entity.h"
#include "Buffer.h"
#include "Mesh.h"
#include "UnlitMaterial.h"
#include "DataTypes.h"

namespace GFXEngine {
	namespace Core {
		class MeshInstancer : public Entity
		{
		public:
			MeshInstancer(const Graphics::Mesh& mesh, const Graphics::UnlitMaterial& material, size_t instances)
				: m_mesh(mesh), m_material(material), m_numInstances(instances) {}
			void init(GFXEngine::Graphics::Renderer& renderer) override;
			void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;

		private:
			const Graphics::Mesh& m_mesh;
			const Graphics::UnlitMaterial& m_material;
			LibGFX::Buffer m_instanceBuffer;
			VkDescriptorSet m_instanceDescriptorSet = VK_NULL_HANDLE;
			size_t m_numInstances = 0;

			std::vector<GFXEngine::EngineTypes::InstanceData> bakeInstanceData() const;
		};
	}
}
