#pragma once
#include "DataTypes.h"
#include "Entity.h"
#include <vector>
#include "SpriteMaterial.h"
#include "Mesh2D.h"

// TODO: Add Serialization support for Sprite (including material and mesh references) make mesh and material an pointer and add an standard constructor.
namespace GFXEngine {
	namespace Core {

		class Sprite : public Entity
		{
		private:
			const Graphics::SpriteMaterial& m_material;
			const Graphics::Mesh2D& m_mesh;

		public:
			//************************************
			// Method:    Sprite
			// FullName:  GFXEngine::Core::Sprite::Sprite
			// Access:    public 
			// Returns:   
			// Qualifier: : m_material(material), m_mesh(mesh)
			// Parameter: const Graphics::SpriteMaterial & material
			// Parameter: const Graphics::Mesh2D & mesh
			//************************************
			Sprite(const Graphics::SpriteMaterial& material, const Graphics::Mesh2D& mesh)
				: m_material(material), m_mesh(mesh) {
				this->setPosition(glm::vec3(0.0f));
				this->setRotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
				this->setScale(glm::vec3(1.0f));
			}

			//************************************
			// Method:    ~Sprite
			// FullName:  GFXEngine::Core::Sprite::~Sprite
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~Sprite() = default;
			
		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::Sprite::init
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			virtual void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    update
			// FullName:  GFXEngine::Core::Sprite::update
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Camera & camera
			// Parameter: float deltaTime
			//************************************
			virtual void update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime) override;
			
			//************************************
			// Method:    buildRenderTasks
			// FullName:  GFXEngine::Core::Sprite::buildRenderTasks
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::RenderContext & context
			// Parameter: GFXEngine::Graphics::RenderQueue & renderQueue
			//************************************
			virtual void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Core::Sprite::destroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			virtual void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;

			//************************************
			// Method:    getMeshCount
			// FullName:  GFXEngine::Core::Sprite::getMeshCount
			// Access:    virtual public 
			// Returns:   std::size_t
			// Qualifier: const 
			//************************************
			virtual size_t getMeshCount() const override { return 1; }
			
			//************************************
			// Method:    getMeshAndMaterial
			// FullName:  GFXEngine::Core::Sprite::getMeshAndMaterial
			// Access:    virtual public 
			// Returns:   GFXEngine::Core::MeshMaterialPair
			// Qualifier: const 
			// Parameter: size_t index
			//************************************
			virtual MeshMaterialPair getMeshAndMaterial(size_t index) const override;
			
			//************************************
			// Method:    getGraphicResources
			// FullName:  GFXEngine::Core::Sprite::getGraphicResources
			// Access:    virtual public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void getGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex) const override;
			
			//************************************
			// Method:    getMeshMaterialGraphicResources
			// FullName:  GFXEngine::Core::Sprite::getMeshMaterialGraphicResources
			// Access:    virtual public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			// Parameter: size_t meshIndex
			//************************************
			virtual void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const override;
		};
	}
}
