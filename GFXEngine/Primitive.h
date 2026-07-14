#pragma once
#include "Entity.h"
#include "Mesh3D.h"
#include "SolidMaterial.h"

namespace GFXEngine
{
	namespace Core {
		class Primitive : public Entity
		{
		private:
			Graphics::Mesh3D* m_mesh = nullptr;
			Graphics::SolidMaterial* m_material = nullptr;

		public:
			Primitive(Graphics::Mesh3D* mesh, Graphics::SolidMaterial* material)
				: m_mesh(mesh), m_material(material) {}

		public:
			// Geerbt über Entity
			void buildRenderTasks(Graphics::RenderContext& context, Graphics::RenderQueue& renderQueue) override;
			void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const override;
			size_t getMeshCount() const override;
			MeshMaterialPair getMeshAndMaterial(size_t index) const override;
		};
	}
}