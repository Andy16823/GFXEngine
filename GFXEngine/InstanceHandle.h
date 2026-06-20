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
			//************************************
			// Method:    InstanceHandle
			// FullName:  GFXEngine::Core::InstanceHandle::InstanceHandle
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			InstanceHandle() = default;
			
			//************************************
			// Method:    InstanceHandle
			// FullName:  GFXEngine::Core::InstanceHandle::InstanceHandle
			// Access:    public 
			// Returns:   
			// Qualifier: : Entity(name), m_parentModel(parentModel), m_instanceIndex(instanceIndex)
			// Parameter: const std::string & name
			// Parameter: InstancedModel * parentModel
			// Parameter: size_t instanceIndex
			//************************************
			InstanceHandle(const std::string& name, InstancedModel* parentModel, size_t instanceIndex) 
				: Entity(name), m_parentModel(parentModel), m_instanceIndex(instanceIndex) {}

			//************************************
			// Method:    ~InstanceHandle
			// FullName:  GFXEngine::Core::InstanceHandle::~InstanceHandle
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~InstanceHandle() = default;
			
			//************************************
			// Method:    InstanceHandle
			// FullName:  GFXEngine::Core::InstanceHandle::InstanceHandle
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const InstanceHandle &
			//************************************
			InstanceHandle(const InstanceHandle&) = delete;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Core::InstanceHandle::operator=
			// Access:    public 
			// Returns:   GFXEngine::Core::InstanceHandle&
			// Qualifier: = delete
			// Parameter: const InstanceHandle &
			//************************************
			InstanceHandle& operator=(const InstanceHandle&) = delete;
			
			//************************************
			// Method:    InstanceHandle
			// FullName:  GFXEngine::Core::InstanceHandle::InstanceHandle
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: InstanceHandle & &
			//************************************
			InstanceHandle(InstanceHandle&&) = default;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Core::InstanceHandle::operator=
			// Access:    public 
			// Returns:   GFXEngine::Core::InstanceHandle&
			// Qualifier: = default
			// Parameter: InstanceHandle & &
			//************************************
			InstanceHandle& operator=(InstanceHandle&&) = default;

		public:
			//************************************
			// Method:    propertyChanged
			// FullName:  GFXEngine::Core::InstanceHandle::propertyChanged
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: PropertyComponentType component
			//************************************
			void propertyChanged(PropertyComponentType component) override;

			//************************************
			// Method:    getMeshCount
			// FullName:  GFXEngine::Core::InstanceHandle::getMeshCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const 
			//************************************
			size_t getMeshCount() const override;
			
			//************************************
			// Method:    getMeshAndMaterial
			// FullName:  GFXEngine::Core::InstanceHandle::getMeshAndMaterial
			// Access:    public 
			// Returns:   GFXEngine::Core::MeshMaterialPair
			// Qualifier: const 
			// Parameter: size_t index
			//************************************
			MeshMaterialPair getMeshAndMaterial(size_t index) const override;
			
			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Core::InstanceHandle::serialize
			// Access:    public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			nlohmann::json serialize() const override;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Core::InstanceHandle::deserialize
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: SerializationContext & context
			// Parameter: SerializationFlags flags
			//************************************
			void deserialize(const nlohmann::json& data, SerializationContext& context, SerializationFlags flags = SerializationFlags::None) override;
			
			//************************************
			// Method:    resolveReferences
			// FullName:  GFXEngine::Core::InstanceHandle::resolveReferences
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: SerializationContext & context
			//************************************
			void resolveReferences(SerializationContext& context) override;
		};
	}
}
