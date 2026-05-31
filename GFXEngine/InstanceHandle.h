#pragma once
#include "Entity.h"

namespace GFXEngine {
	namespace Core {

		class InstancedModel;

		class InstanceHandle : public Entity
		{
		private:
			InstancedModel* m_parentModel = nullptr;
			size_t m_instanceIndex = -1;

		public:
			InstanceHandle(InstancedModel* parentModel, size_t instanceIndex) 
				: m_parentModel(parentModel), m_instanceIndex(instanceIndex) {}
			virtual ~InstanceHandle() = default;
			InstanceHandle(const InstanceHandle&) = delete;
			InstanceHandle& operator=(const InstanceHandle&) = delete;
			InstanceHandle(InstanceHandle&&) = default;
			InstanceHandle& operator=(InstanceHandle&&) = default;

		public:
			void propertyChanged(PropertyComponentType component) override;

			// Geerbt über Entity
			size_t getMeshCount() const override;
			MeshMaterialPair getMeshAndMaterial(size_t index) const override;
		};
	}
}
