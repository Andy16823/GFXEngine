#pragma once
#include <vulkan/vulkan.h>
#include "Renderer.h"

namespace GFXEngine {
	namespace Graphics {
		class Material {
		public:
			//************************************
			// Method:    Material
			// FullName:  GFXEngine::Graphics::Material::Material
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			Material() = default;
			
			//************************************
			// Method:    ~Material
			// FullName:  GFXEngine::Graphics::Material::~Material
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~Material() = default;

			//************************************
			// Method:    Material
			// FullName:  GFXEngine::Graphics::Material::Material
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const Material &
			//************************************
			Material(const Material&) = delete;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Graphics::Material::operator=
			// Access:    public 
			// Returns:   GFXEngine::Graphics::Material&
			// Qualifier: = delete
			// Parameter: const Material &
			//************************************
			Material& operator=(const Material&) = delete;
			
			//************************************
			// Method:    Material
			// FullName:  GFXEngine::Graphics::Material::Material
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: Material & &
			//************************************
			Material(Material&&) = default;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Graphics::Material::operator=
			// Access:    public 
			// Returns:   GFXEngine::Graphics::Material&
			// Qualifier: = default
			// Parameter: Material & &
			//************************************
			Material& operator=(Material&&) = default;

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::Material::init
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			virtual void init(Renderer& renderer) = 0;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::Material::destroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			virtual void destroy(Renderer& renderer) = 0;
			
			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::Material::getDescriptorSet
			// Access:    virtual public 
			// Returns:   VkDescriptorSet
			// Qualifier: const
			// Parameter: uint32_t imageIndex
			//************************************
			virtual VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const = 0;
		};
	}
}