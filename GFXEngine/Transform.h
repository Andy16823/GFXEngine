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
			
			Transform() = default;
			Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl);
			~Transform() = default;

			void setFromMatrix(const glm::mat4& matrix);

			void setRotationFromEuler(const glm::vec3& rot);
			void rotateWorld(float pitch, float yaw, float roll);
			void rotateLocal(float pitch, float yaw, float roll);
			void translate(const glm::vec3& delta);
			void setPosition(const glm::vec3& newPos);
			void setScale(const glm::vec3& newScale);
			void forward(float distance);
			void right(float distance);
			void up(float distance);

			glm::mat4 getModelMatrix() const;
			glm::vec3 getEulerRotation() const;
			glm::vec3 getForward() const;
			glm::vec3 getRight() const;
			glm::vec3 getUp();

			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context) override;
		};
	}
}
