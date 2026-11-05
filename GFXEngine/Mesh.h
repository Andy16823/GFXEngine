#pragma once
#include "Renderer.h"
#include "AABB.h"
#include "DataTypes.h"
#include <stdexcept>
#include <typeindex>
#include <vector>
#include "StrideSpan.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// MeshVertexPointer is a structure that holds information about the vertex data of a mesh. 
		/// It contains a pointer to the vertex data, the number of vertices, the stride (size) of each vertex, 
		/// and the type of the vertex. 
		/// It provides methods to get the total size of the vertex buffer and to retrieve a span of vertices 
		/// of a specific type, ensuring that the requested type matches the stored vertex type and stride.
		/// </summary>
		struct MeshVertexPointer {
			const void* vertexData = nullptr;
			size_t vertexCount = 0;
			size_t vertexStride = 0;
			std::type_index vertexType = typeid(void);

			size_t getVertexBufferSize() const {
				return vertexCount * vertexStride;
			}

			template<typename VertexType>
			std::span<const VertexType> getVertices() const {

				if (vertexType != typeid(VertexType)) 
				{
					throw std::runtime_error("Vertex type mismatch");
				}

				if (vertexStride != sizeof(VertexType))
				{
					throw std::runtime_error("Vertex stride mismatch");
				}

				return { static_cast<const VertexType*>(vertexData), vertexCount };
			}
		};

		/// <summary>
		/// Mesh is an abstract base class that defines the interface 
		/// for mesh objects in the graphics engine.
		/// </summary>
		class Mesh
		{
		public:
			virtual ~Mesh() = default;
			virtual void init(Renderer& renderer) = 0;
			virtual void destroy(Renderer& renderer) = 0;
			virtual Math::AABB computeAABB() const = 0;
			virtual const LibGFX::Buffer& getVertexBuffer() const = 0;
			virtual const LibGFX::Buffer& getIndexBuffer() const = 0;
			virtual size_t getIndexCount() const = 0;

			virtual GFXEngine::EngineTypes::VertexComponentView getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const = 0;
			virtual MeshVertexPointer getVertexPointer() const = 0;
			virtual std::span<const uint32_t> getIndices() const = 0;

			template<typename VertexType>
			std::span<const VertexType> getVertices() const {
				auto pointer = getVertexPointer();
				return pointer.getVertices<VertexType>();
			}

			template<typename T>
			T* as() {
				static_assert(std::is_base_of_v<Mesh, T>, "T must be a subclass of Mesh");
				return dynamic_cast<T*>(this);
			}

			template<typename T>
			const T* as() const {
				static_assert(std::is_base_of_v<Mesh, T>, "T must be a subclass of Mesh");
				return dynamic_cast<const T*>(this);
			}
		};
	}
}