#pragma once
#include "DataTypes.h"
#include "Entity.h"
#include "Imaging.h"
#include "Buffer.h"
#include <vector>
#include "Pipeline.h"

namespace GFXEngine {
	namespace Core {
		class Sprite : public Entity
		{
		private:
			std::string m_texturePath;
			LibGFX::Image m_texture;
			VkDescriptorSet m_textureDescriptorSet;

			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;
			std::vector<EngineTypes::Vertex3D> m_vertices;
			std::vector<uint32_t> m_indices;

			LibGFX::Pipeline* m_pipeline = nullptr;
		public:
			Sprite(const std::string& texturePath) : m_texturePath(texturePath) {
				this->transform.position = glm::vec3(0.0f);
				this->transform.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
				this->transform.scale = glm::vec3(1.0f);
			}
			virtual ~Sprite() = default;
			
			virtual void init(GFXEngine::Graphics::Renderer& renderer) override;
			virtual void update(float deltaTime) override;
			virtual void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera3D& camera, uint32_t imageIndex) override;
			virtual void destroy(GFXEngine::Graphics::Renderer& renderer) override;

			void createDescriptorSet(GFXEngine::Graphics::Renderer& renderer, LibGFX::Pipeline* pipline, VkDescriptorSetLayout descriptorSetLayout);
		};
	}
}
