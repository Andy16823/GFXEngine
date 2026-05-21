#pragma once
#include "Entity.h"
#include "MeshModel.h"
#include "Buffer.h"
#include <vector>
#include "DataTypes.h"
#include "AABB.h"

namespace GFXEngine {
	namespace Core {

		class InstancedModel : public Entity
		{
		private:
			std::vector<EngineTypes::InstanceData> m_instanceData;
			EngineTypes::AssetReference m_meshModelRef;
			bool m_isDirty = true;

			VkDescriptorSet m_instanceDataDescriptorSet = VK_NULL_HANDLE;
			LibGFX::Buffer m_instanceDataBuffer;
			void* m_mappedInstanceData = nullptr;

		public:
			InstancedModel() = default;
			InstancedModel(Graphics::MeshModel* meshModel, size_t instanceCount);

			void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			void render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;
			void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			void updateInstance(const EngineTypes::InstanceData& instanceData, size_t index);
			void updateInstanceRange(const std::span<const EngineTypes::InstanceData>& instanceData, size_t startIndex);

			std::vector<PropertyInfo> getProperties() override;
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;

			size_t getMeshCount() const override;
			std::pair<const Graphics::Mesh&, const Graphics::Material&> getMeshAndMaterial(size_t index) const override;

			size_t getInstanceCount() const { return m_instanceData.size(); }
			GFXEngine::Math::AABB computeInstanceAABB(size_t instanceIndex) const;
			bool isInstanceVisible(size_t instanceIndex) const;
			void hideInstance(size_t instanceIndex);
			void showInstance(size_t instanceIndex);
			void setInstanceModelMatrix(size_t instanceIndex, const glm::mat4& modelMatrix);
			size_t findNextFreeInstance() const;
			glm::mat4 getInstanceModelMatrix(size_t instanceIndex) const;
		};
	}
}
