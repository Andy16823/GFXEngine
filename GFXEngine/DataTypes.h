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

		enum class ReferenceState 
		{
			Uninitialized,
			Unresolved,
			Resolved
		};

		/// <summary>
		/// EntityReference is a structure that holds either a UUID string reference to an entity or a direct pointer to the entity. 
		/// This allows for flexible referencing of entities, where the reference can be resolved to an actual pointer at runtime, 
		/// especially during deserialization when entities may not yet be fully constructed.
		/// </summary>
		struct EntityReference
		{
		protected:
			std::string uuid = "";
			Core::Entity* entity = nullptr;
			ReferenceState state = ReferenceState::Uninitialized;

		public:
			EntityReference() = default;
			EntityReference(const std::string& uuidStr) : uuid(uuidStr), entity(nullptr), state(ReferenceState::Unresolved) {}
			EntityReference(Core::Entity* entityPtr) : uuid(""), entity(entityPtr), state(ReferenceState::Resolved) {}

			operator bool() const {
				return entity != nullptr;
			}

			Core::Entity& get() const
			{
				return *entity;
			}

			Core::Entity* getPtr() const
			{
				return entity;
			}

			void set(Core::Entity* entityPtr)
			{
				// Set the entity pointer and clear the UUID since we now have a direct reference
				entity = entityPtr;
				uuid.clear();
				if (entityPtr) 
				{
					state = ReferenceState::Resolved;
				}
				else {
					state = ReferenceState::Uninitialized;
				}
			}

			void clear()
			{
				uuid.clear();
				entity = nullptr;
				state = ReferenceState::Uninitialized;
			}

			void setUUID(const std::string& uuidStr)
			{
				// Set the UUID string and clear the entity pointer since we are now referencing by UUID
				uuid = uuidStr;
				entity = nullptr;
				state = ReferenceState::Unresolved;
			}

			template<typename T>
			T& getAs() const
			{
				assert(entity);
				T* casted = dynamic_cast<T*>(entity);
				assert(casted && "EntityReference: Failed to cast entity to requested type");
				return *casted;
			}

			template<typename T>
			T* getPtrAs() const
			{
				assert(entity);
				T* casted = dynamic_cast<T*>(entity);
				assert(casted && "EntityReference: Failed to cast entity to requested type");
				return casted;
			}

			const std::string& getUUID() const
			{
				return uuid;
			}

			bool isResolved() const
			{
				return state == ReferenceState::Resolved;
			}

			bool hasUUID() const
			{
				return state == ReferenceState::Unresolved;
			}

			bool hasAny() const
			{
				return state != ReferenceState::Uninitialized;
			}

			ReferenceState getState() const
			{
				return state;
			}
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