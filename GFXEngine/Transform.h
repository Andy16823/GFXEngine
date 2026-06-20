#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "ISerializable.h"


namespace GFXEngine {
	namespace Math {
		class Transform : public GFXEngine::ISerializable {
		public:
			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scale;
			
		public:
			//************************************
			// Method:    Transform
			// FullName:  GFXEngine::Math::Transform::Transform
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			Transform() = default;
			
			//************************************
			// Method:    Transform
			// FullName:  GFXEngine::Math::Transform::Transform
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const glm::vec3 & pos
			// Parameter: const glm::vec3 & rot
			// Parameter: const glm::vec3 & scl
			//************************************
			Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl);
			
			//************************************
			// Method:    ~Transform
			// FullName:  GFXEngine::Math::Transform::~Transform
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			~Transform() = default;

		public:
			//************************************
			// Method:    setFromMatrix
			// FullName:  GFXEngine::Math::Transform::setFromMatrix
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::mat4 & matrix
			//************************************
			void setFromMatrix(const glm::mat4& matrix);
			
			//************************************
			// Method:    setRotationFromEuler
			// FullName:  GFXEngine::Math::Transform::setRotationFromEuler
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & rot
			//************************************
			void setRotationFromEuler(const glm::vec3& rot);
			
			//************************************
			// Method:    rotateWorld
			// FullName:  GFXEngine::Math::Transform::rotateWorld
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: float pitch
			// Parameter: float yaw
			// Parameter: float roll
			//************************************
			void rotateWorld(float pitch, float yaw, float roll);
			
			//************************************
			// Method:    rotateLocal
			// FullName:  GFXEngine::Math::Transform::rotateLocal
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: float pitch
			// Parameter: float yaw
			// Parameter: float roll
			//************************************
			void rotateLocal(float pitch, float yaw, float roll);
			
			//************************************
			// Method:    translate
			// FullName:  GFXEngine::Math::Transform::translate
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & delta
			//************************************
			void translate(const glm::vec3& delta);
			
			//************************************
			// Method:    setPosition
			// FullName:  GFXEngine::Math::Transform::setPosition
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & newPos
			//************************************
			void setPosition(const glm::vec3& newPos);
			
			//************************************
			// Method:    setScale
			// FullName:  GFXEngine::Math::Transform::setScale
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & newScale
			//************************************
			void setScale(const glm::vec3& newScale);
			
			//************************************
			// Method:    forward
			// FullName:  GFXEngine::Math::Transform::forward
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: float distance
			//************************************
			void forward(float distance);
			
			//************************************
			// Method:    right
			// FullName:  GFXEngine::Math::Transform::right
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: float distance
			//************************************
			void right(float distance);
			
			//************************************
			// Method:    up
			// FullName:  GFXEngine::Math::Transform::up
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: float distance
			//************************************
			void up(float distance);

		public:
			//************************************
			// Method:    getModelMatrix
			// FullName:  GFXEngine::Math::Transform::getModelMatrix
			// Access:    public 
			// Returns:   glm::mat4
			// Qualifier: const
			//************************************
			glm::mat4 getModelMatrix() const;
			
			//************************************
			// Method:    getEulerRotation
			// FullName:  GFXEngine::Math::Transform::getEulerRotation
			// Access:    public 
			// Returns:   glm::vec3
			// Qualifier: const
			//************************************
			glm::vec3 getEulerRotation() const;
			
			//************************************
			// Method:    getForward
			// FullName:  GFXEngine::Math::Transform::getForward
			// Access:    public 
			// Returns:   glm::vec3
			// Qualifier: const
			//************************************
			glm::vec3 getForward() const;
			
			//************************************
			// Method:    getRight
			// FullName:  GFXEngine::Math::Transform::getRight
			// Access:    public 
			// Returns:   glm::vec3
			// Qualifier: const
			//************************************
			glm::vec3 getRight() const;
			
			//************************************
			// Method:    getUp
			// FullName:  GFXEngine::Math::Transform::getUp
			// Access:    public 
			// Returns:   glm::vec3
			// Qualifier:
			//************************************
			glm::vec3 getUp();

		public:
			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Math::Transform::serialize
			// Access:    public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			nlohmann::json serialize() const override;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Math::Transform::deserialize
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: GFXEngine::SerializationContext & context
			// Parameter: GFXEngine::SerializationFlags flags
			//************************************
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
		};
	}
}
