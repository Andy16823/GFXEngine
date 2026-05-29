#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <typeindex>
#include <variant>
#include "StrideSpan.h"

namespace GFXEngine {

	namespace Core {
		class Entity;
	}

	namespace EngineTypes {

		/// <summary>
		/// FramebufferVertex is a simple vertex structure used for rendering a full-screen quad, containing position and texture coordinates.
		/// </summary>
		struct FramebufferVertex
		{
			glm::vec3 pos;
			glm::vec2 texCoord;
		};

		/// <summary>
		/// Simple vertex structure for 3D rendering, containing position, color, texture coordinates, and normal vector.
		/// </summary>
		struct Vertex3D
		{
		public:
			glm::vec3 pos;
			glm::vec3 color;
			glm::vec2 texCoord;
			glm::vec3 normal;
			glm::vec4 tangent;
		};

		/// <summary>
		/// Simple vertex structure for 2D rendering, containing position, color, and texture coordinates.
		/// </summary>
		struct Vertex2D
		{
			glm::vec3 pos;
			glm::vec3 color;
			glm::vec2 texCoord;
		};

		/// <summary>
		/// Vertex structure for skinned meshes, containing position, color, texture coordinates, normal vector, bone IDs, and weights for skinning.
		/// </summary>
		struct SkinningVertex
		{
			glm::vec3 pos;
			glm::vec3 color;
			glm::vec2 texCoord;
			glm::vec3 normal;
			glm::vec4 tangent;
			glm::ivec4 boneIDs;
			glm::vec4 weights;
		};

		/// <summary>
		/// Vertex structure for simple position-only vertices, useful for rendering skyboxes or other geometry where only position is needed.
		/// </summary>
		struct PositionVertex
		{
			glm::vec3 pos;
		};

		/// <summary>
		/// Vertex component class
		/// </summary>
		enum class VertexComponent {
			Position,
			Color,
			TexCoord,
			Normal,
			Tangent,
			BoneIDs,
			BoneWeights
		};

		/// <summary>
		/// Vertex Compontent View
		/// </summary>
		struct VertexComponentView {
			const void* data;
			size_t count;
			size_t stride;
			std::type_index type;

			template<typename T>
			GFXEngine::StrideSpan<T> as() const
			{
				if (type != typeid(T)) 
				{
					throw std::runtime_error("Vertex component type mismatch");
				}
				return GFXEngine::StrideSpan<T>(data, count, stride);
			}

			bool isEmpty() const {
				return data == nullptr || count == 0;
			}

			static VertexComponentView empty() {
				return { nullptr, 0, 0, typeid(void) };
			}
		};

		/// <summary>
		/// Uniform buffer object for camera data, containing view and projection matrices, as well as the camera position for lighting calculations.
		/// </summary>
		struct CameraBufferObject
		{
			glm::mat4 view;
			glm::mat4 proj;
			glm::vec4 cameraPos;
		};
#
		/// <summary>
		/// Instance data structure for instanced rendering, containing a model matrix for transforming each instance and an extras vector for any additional per-instance data.
		/// </summary>
		struct InstanceData
		{
			glm::mat4 model;
			glm::vec4 extras;
		};	

		/// <summary>
		/// Light data structure for a directional light, containing the direction of the light and its color (with an optional intensity in the w component).
		/// </summary>
		struct DirectionalLightData
		{
			glm::vec4 direction; // w component can be used for padding
			glm::vec4 color;     // w component can be used for intensity
		};

		/// <summary>
		/// EntityReference is a simple structure that holds a non-owning pointer to an Entity.
		/// </summary>
		struct EntityReference
		{
			GFXEngine::Core::Entity* entity;
		};

		/// <summary>
		/// AssetReference is a simple structure that holds a non-owning pointer to an Asset, allowing entities to reference assets without owning them directly.
		/// </summary>
		struct AssetReference
		{
			std::type_index assetType = typeid(void);
			void* asset = nullptr;

			operator bool() const {
				return asset != nullptr;
			} 

			template<typename T>
			void set(T* assetPtr) {
				static_assert(std::derived_from<T, class GFXEngine::Asset>, "AssetReference can only hold pointers to Asset-derived types");
				assetType = typeid(T);
				asset = assetPtr;
			}

			template <typename T>
			T* get() const {
				if (assetType == typeid(T)) {
					return static_cast<T*>(asset);
				}
				return nullptr;
			}

			template <typename T>
			bool isTypeOf() const {
				return assetType == typeid(T);
			}

			void clear() {
				assetType = typeid(void);
				asset = nullptr;
			}
		};
	}
}