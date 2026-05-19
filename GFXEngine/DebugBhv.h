#pragma once
#include "Behavior.h"
#include "Buffer.h"

namespace GFXEngine {
	namespace Core {
		class DebugBhv : public Behavior
		{
		public:
			void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			void update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime) override;
			void render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;
			void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;

			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;

			std::string getName() const override { return "DebugBhv"; }
			std::vector<PropertyInfo> getProperties() override;

		private:
			LibGFX::Buffer m_debugVertexBuffer;
			LibGFX::Buffer m_debugIndexBuffer;
			uint32_t m_indexCount;
			bool m_isEnabled = true;
		};
	}
}
