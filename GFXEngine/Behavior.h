#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "ISerializable.h"
#include <variant>
#include "PropertyInfo.h"
#include "Utils.h"

namespace GFXEngine {
	namespace Core {
		class Scene;

		class Behavior 
			: public GFXEngine::ISerializable {
		
		protected:
			class Entity* m_entity = nullptr;
			std::string m_uuid;

		public:

			//************************************
			// Method:    Behavior
			// FullName:  GFXEngine::Core::Behavior::Behavior
			// Access:    public 
			// Returns:   
			// Qualifier: : m_uuid(Utils::generateUUID())
			//************************************
			Behavior() : m_uuid(Utils::generateUUID()) {}
			
			//************************************
			// Method:    ~Behavior
			// FullName:  GFXEngine::Core::Behavior::~Behavior
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~Behavior() = default;
			
			//************************************
			// Method:    Behavior
			// FullName:  GFXEngine::Core::Behavior::Behavior
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const Behavior &
			//************************************
			Behavior(const Behavior&) = delete;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Core::Behavior::operator=
			// Access:    public 
			// Returns:   GFXEngine::Core::Behavior&
			// Qualifier: = delete
			// Parameter: const Behavior &
			//************************************
			Behavior& operator=(const Behavior&) = delete;

			//************************************
			// Method:    Behavior
			// FullName:  GFXEngine::Core::Behavior::Behavior
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: Behavior & &
			//************************************
			Behavior(Behavior&&) = delete;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Core::Behavior::operator=
			// Access:    public 
			// Returns:   GFXEngine::Core::Behavior&
			// Qualifier: = delete
			// Parameter: Behavior & &
			//************************************
			Behavior& operator=(Behavior&&) = delete;

			//************************************
			// Method:    setEntity
			// FullName:  GFXEngine::Core::Behavior::setEntity
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: class Entity * entity
			//************************************
			void setEntity(class Entity* entity) { m_entity = entity; }
			
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::Behavior::init
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: Graphics::Renderer & renderer
			//************************************
			virtual void init(Scene& scene, Graphics::Renderer& renderer) = 0;
			
			//************************************
			// Method:    update
			// FullName:  GFXEngine::Core::Behavior::update
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: Graphics::Camera & camera
			// Parameter: float deltaTime
			//************************************
			virtual void update(Scene& scene, Graphics::Camera& camera, float deltaTime) = 0;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Core::Behavior::destroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: Graphics::Renderer & renderer
			//************************************
			virtual void destroy(Scene& scene, Graphics::Renderer& renderer) = 0;

			//************************************
			// Method:    getName
			// FullName:  GFXEngine::Core::Behavior::getName
			// Access:    virtual public 
			// Returns:   std::string
			// Qualifier: const
			//************************************
			virtual std::string getName() const = 0;
			
			//************************************
			// Method:    getProperties
			// FullName:  GFXEngine::Core::Behavior::getProperties
			// Access:    virtual public 
			// Returns:   std::vector<GFXEngine::Core::PropertyInfo>
			// Qualifier:
			//************************************
			virtual std::vector<PropertyInfo> getProperties() = 0;

			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Core::Behavior::serialize
			// Access:    virtual public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			virtual nlohmann::json serialize() const override {
				nlohmann::json data;
				data["uuid"] = m_uuid;
				return data;
			}

			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Core::Behavior::deserialize
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: GFXEngine::SerializationContext & context
			// Parameter: GFXEngine::SerializationFlags flags
			//************************************
			virtual void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override {
				if (hasFlag(flags, GFXEngine::SerializationFlags::RegenerateUUID)) {
					m_uuid = Utils::generateUUID();
				}
				else {
					if (!data.is_null()) {
						m_uuid = data.value("uuid", Utils::generateUUID());
					}
				}
			}

			//************************************
			// Method:    getEntity
			// FullName:  GFXEngine::Core::Behavior::getEntity
			// Access:    public 
			// Returns:   GFXEngine::Core::Entity*
			// Qualifier: const
			//************************************
			Entity* getEntity() const { return m_entity; }

			//************************************
			// Method:    getUUID
			// FullName:  GFXEngine::Core::Behavior::getUUID
			// Access:    public 
			// Returns:   const std::string&
			// Qualifier: const
			//************************************
			const std::string& getUUID() const { return m_uuid; }
		};
	}
}