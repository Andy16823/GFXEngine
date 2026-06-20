#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "ISerializable.h"

namespace GFXEngine {
	namespace Graphics {

		class DirectionalLight : public GFXEngine::ISerializable
		{
		private:
			std::vector<LibGFX::Buffer> m_uniformBuffers;
			std::vector<VkDescriptorSet> m_descriptorSets;

		public:
			glm::vec3 direction = glm::vec3(-0.5f, -1.0f, -0.3f);
			glm::vec3 color = glm::vec3(1.0f, 0.95f, 0.9f);
			float intensity = 3;

		public:
			//************************************
			// Method:    DirectionalLight
			// FullName:  GFXEngine::Graphics::DirectionalLight::DirectionalLight
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			DirectionalLight() = default;
			
			//************************************
			// Method:    ~DirectionalLight
			// FullName:  GFXEngine::Graphics::DirectionalLight::~DirectionalLight
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			~DirectionalLight() = default;

			//************************************
			// Method:    DirectionalLight
			// FullName:  GFXEngine::Graphics::DirectionalLight::DirectionalLight
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const DirectionalLight &
			//************************************
			DirectionalLight(const DirectionalLight&) = delete;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Graphics::DirectionalLight::operator=
			// Access:    public 
			// Returns:   GFXEngine::Graphics::DirectionalLight&
			// Qualifier: = delete
			// Parameter: const DirectionalLight &
			//************************************
			DirectionalLight& operator=(const DirectionalLight&) = delete;
			
			//************************************
			// Method:    DirectionalLight
			// FullName:  GFXEngine::Graphics::DirectionalLight::DirectionalLight
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: DirectionalLight & &
			//************************************
			DirectionalLight(DirectionalLight&&) = default;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Graphics::DirectionalLight::operator=
			// Access:    public 
			// Returns:   GFXEngine::Graphics::DirectionalLight&
			// Qualifier: = default
			// Parameter: DirectionalLight & &
			//************************************
			DirectionalLight& operator=(DirectionalLight&&) = default;

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::DirectionalLight::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer);
			
			//************************************
			// Method:    update
			// FullName:  GFXEngine::Graphics::DirectionalLight::update
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
			// FullName:  GFXEngine::Graphics::DirectionalLight::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer);

			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Graphics::DirectionalLight::serialize
			// Access:    public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			nlohmann::json serialize() const override;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Graphics::DirectionalLight::deserialize
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: GFXEngine::SerializationContext & context
			// Parameter: GFXEngine::SerializationFlags flags
			//************************************
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
			
			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::DirectionalLight::getDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier: const
			// Parameter: uint32_t imageIndex
			//************************************
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const 
			{
				return m_descriptorSets[imageIndex];
			}
		};
	}
}
