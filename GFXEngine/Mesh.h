#pragma once
#include "Renderer.h"
#include "AABB.h"
#include "DataTypes.h"
#include <stdexcept>
#include <typeindex>
#include <vector>

namespace GFXEngine {
	namespace Graphics {

		struct MeshVertexPointer {
			const void* vertexData = nullptr;
			size_t vertexSize = 0;
			size_t vertexStride = 0;
			std::type_index vertexType = typeid(void);

			template<typename VertexType>
			std::span<const VertexType> getVertices() const {
				if (vertexType != typeid(VertexType)) {
					throw std::runtime_error("Vertex type mismatch");
				}
				size_t vertexCount = vertexSize / sizeof(VertexType);
				return { static_cast<const VertexType*>(vertexData), vertexCount };
			}
		};

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

			template <typename T>
			T* as() {
				static_assert(std::is_base_of_v<Mesh, T>, "T must be a subclass of Mesh");
				if (typeid(T) != typeid(*this)) {
					throw std::runtime_error("Mesh type mismatch");
				}
				return static_cast<T*>(this);
			}
		};
	}
}