#pragma once
#include "Entity.h"
#include "DataTypes.h"
#include "InstancedModel.h"

namespace GFXEngine {
	namespace Core {

		class InstanceHandle : public Entity
		{
		private:
			EngineTypes::EntityReference m_parentModel;
			size_t m_instanceIndex = -1;

		public:
			InstanceHandle() = default;
			InstanceHandle(InstancedModel* parentModel, size_t instanceIndex) 
				: m_parentModel({parentModel->getUUID(), parentModel}), m_instanceIndex(instanceIndex) {}

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
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, SerializationContext& context, SerializationFlags flags = SerializationFlags::None) override;
			void resolveReferences(SerializationContext& context) override;
		};
	}
}
