#pragma once
#include "Renderer.h"
#include "glm/glm.hpp"
#include "ISerializable.h"
#include "Camera.h"

namespace GFXEngine {
	namespace Graphics {
		class Fog : public ISerializable
		{
		private:
			std::vector<LibGFX::Buffer> m_uniformBuffers;
			std::vector<VkDescriptorSet> m_descriptorSets;

		public:
			float density = 0.3f;
			float minDistance = 25.0f;
			float maxDistance = 5000.0f;
			glm::vec4 color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::Fog::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer);

			//************************************
			// Method:    update
			// FullName:  GFXEngine::Graphics::Fog::update
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: const Camera & camera
			// Parameter: uint32_t imageIndex
			//************************************
			void update(Renderer& renderer, const Camera& camera, uint32_t imageIndex);

			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::Fog::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer);

			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::Fog::getDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier: const
			// Parameter: uint32_t imageIndex
			//************************************
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const { return m_descriptorSets[imageIndex]; }

			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Graphics::Fog::serialize
			// Access:    public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			nlohmann::json serialize() const override;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Graphics::Fog::deserialize
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: SerializationContext & context
			// Parameter: SerializationFlags flags
			//************************************
			void deserialize(const nlohmann::json& data, SerializationContext& context, SerializationFlags flags = SerializationFlags::None) override;
		};
	}
}
