#pragma once
#include <vulkan/vulkan.h>
#include "Renderer.h"
#include "ISerializable.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Material is an abstract base class that represents a material in the graphics engine. 
		/// A material defines how a surface interacts with light and can include properties 
		/// such as color, texture, and shading parameters. Materials are used to render 
		/// objects in the scene with specific visual characteristics.
		/// </summary>
		class Material 
			: public ISerializable {

		public:
			Material() = default;
			virtual ~Material() = default;
			Material(const Material&) = delete;
			Material& operator=(const Material&) = delete;
			Material(Material&&) = default;
			Material& operator=(Material&&) = default;

		public:
			virtual void init(Renderer& renderer) = 0;
			virtual void destroy(Renderer& renderer) = 0;
			virtual VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const = 0;
			virtual void updateMaterial(Renderer& renderer) = 0;

		public:
			virtual nlohmann::json serialize() const override;
			virtual void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;

		public:
			template<typename T>
			bool isType() const {
				return dynamic_cast<const T*>(this) != nullptr;
			}

			template<typename T>
			T* as() {
				return dynamic_cast<T*>(this);
			}

			template<typename T>
			T* staticAs() {
				return static_cast<T*>(this);
			}
		};
	}
}