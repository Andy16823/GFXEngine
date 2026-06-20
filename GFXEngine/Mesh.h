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

		struct MeshVertexPointer {
			const void* vertexData = nullptr;
			size_t vertexCount = 0;
			size_t vertexStride = 0;
			std::type_index vertexType = typeid(void);

			//************************************
			// Method:    getVertexBufferSize
			// FullName:  GFXEngine::Graphics::MeshVertexPointer::getVertexBufferSize
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const
			//************************************
			size_t getVertexBufferSize() const {
				return vertexCount * vertexStride;
			}

			//************************************
			// Method:    getVertices
			// FullName:  GFXEngine::Graphics::MeshVertexPointer::getVertices
			// Access:    public 
			// Returns:   
			// Qualifier: const
			//************************************
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

		class Mesh
		{
		public:
			//************************************
			// Method:    ~Mesh
			// FullName:  GFXEngine::Graphics::Mesh::~Mesh
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~Mesh() = default;

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::Mesh::init
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			virtual void init(Renderer& renderer) = 0;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::Mesh::destroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			virtual void destroy(Renderer& renderer) = 0;
			
			//************************************
			// Method:    computeAABB
			// FullName:  GFXEngine::Graphics::Mesh::computeAABB
			// Access:    virtual public 
			// Returns:   GFXEngine::Math::AABB
			// Qualifier: const
			//************************************
			virtual Math::AABB computeAABB() const = 0;

			//************************************
			// Method:    getVertexBuffer
			// FullName:  GFXEngine::Graphics::Mesh::getVertexBuffer
			// Access:    virtual public 
			// Returns:   const LibGFX::Buffer&
			// Qualifier: const
			//************************************
			virtual const LibGFX::Buffer& getVertexBuffer() const = 0;
			
			//************************************
			// Method:    getIndexBuffer
			// FullName:  GFXEngine::Graphics::Mesh::getIndexBuffer
			// Access:    virtual public 
			// Returns:   const LibGFX::Buffer&
			// Qualifier: const
			//************************************
			virtual const LibGFX::Buffer& getIndexBuffer() const = 0;
			
			//************************************
			// Method:    getIndexCount
			// FullName:  GFXEngine::Graphics::Mesh::getIndexCount
			// Access:    virtual public 
			// Returns:   std::size_t
			// Qualifier: const
			//************************************
			virtual size_t getIndexCount() const = 0;

			//************************************
			// Method:    getVertexComponent
			// FullName:  GFXEngine::Graphics::Mesh::getVertexComponent
			// Access:    virtual public 
			// Returns:   GFXEngine::EngineTypes::VertexComponentView
			// Qualifier: const
			// Parameter: GFXEngine::EngineTypes::VertexComponent component
			//************************************
			virtual GFXEngine::EngineTypes::VertexComponentView getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const = 0;
			
			//************************************
			// Method:    getVertexPointer
			// FullName:  GFXEngine::Graphics::Mesh::getVertexPointer
			// Access:    virtual public 
			// Returns:   GFXEngine::Graphics::MeshVertexPointer
			// Qualifier: const
			//************************************
			virtual MeshVertexPointer getVertexPointer() const = 0;
			
			//************************************
			// Method:    getIndices
			// FullName:  GFXEngine::Graphics::Mesh::getIndices
			// Access:    virtual public 
			// Returns:   std::span<const uint32_t>
			// Qualifier: const
			//************************************
			virtual std::span<const uint32_t> getIndices() const = 0;

			//************************************
			// Method:    getVertices
			// FullName:  GFXEngine::Graphics::Mesh::getVertices
			// Access:    public 
			// Returns:   
			// Qualifier: const
			//************************************
			template<typename VertexType>
			std::span<const VertexType> getVertices() const {
				auto pointer = getVertexPointer();
				return pointer.getVertices<VertexType>();
			}

			//************************************
			// Method:    as
			// FullName:  GFXEngine::Graphics::Mesh::as
			// Access:    public 
			// Returns:   T*
			// Qualifier:
			//************************************
			template<typename T>
			T* as() {
				static_assert(std::is_base_of_v<Mesh, T>, "T must be a subclass of Mesh");
				return dynamic_cast<T*>(this);
			}

			//************************************
			// Method:    as
			// FullName:  GFXEngine::Graphics::Mesh::as
			// Access:    public 
			// Returns:   const T*
			// Qualifier: const
			//************************************
			template<typename T>
			const T* as() const {
				static_assert(std::is_base_of_v<Mesh, T>, "T must be a subclass of Mesh");
				return dynamic_cast<const T*>(this);
			}
		};
	}
}