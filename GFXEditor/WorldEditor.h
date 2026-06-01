#pragma once
#include "glm/glm.hpp"
#include "UIWidget.h"
#include "Scene3D.h"
#include "Renderer.h"
#include "UIContext.h"
#include "RenderTexture.h"
#include "Camera3D.h"
#include "AssetManager.h"
#include "BehaviorRegistry.h"
#include "StaticMeshModel.h"
#include <memory>
#include <string>

namespace GFXEditor {

	struct ViewportCursorInfo {
		glm::vec2 position;
		bool isHovering;
	};

	struct CursorDragInfo {
		glm::vec2 startPosition;
		glm::vec2 currentPosition;
		bool isDragging;
	};

	class WorldEditor : public GFXEngine::Core::UIWidget
	{
	private:
		// Non-owning pointers to the scene and asset manager
		GFXEngine::Core::Scene3D* m_scene;
		GFXEngine::AssetManager* m_assetManager;
		GFXEngine::BehaviorRegistry* m_behaviorRegistry;
		GFXEngine::Core::Entity* m_selectedEntity = nullptr;

		std::filesystem::path m_projectDirectory;
		std::filesystem::path m_currentExplorerPath;
		bool m_showCreateDirectoryPopup = false;

		// Helper Vectors
		std::vector<GFXEngine::Core::Behavior*> m_behaviorsToRemove;

		// Owned resources for the editor
		std::unique_ptr<GFXEngine::Graphics::RenderTexture> m_renderTexture;
		std::unique_ptr<GFXEngine::Graphics::Camera3D> m_editorCamera;
		VkDescriptorSet m_descriptorSet;
		glm::vec2 m_sceneViewportWindowSize = glm::vec2(1024.0f, 1024.0f);
		ViewportCursorInfo m_viewportCursorInfo = { glm::vec2(0.0f), false };
		bool m_dockspaceInitialized = false;
		GFXEngine::Core::GuizmoOperation m_currentGuizmoOperation = GFXEngine::Core::GuizmoOperation::Translate;
		CursorDragInfo m_cursorDragInfo = { glm::vec2(0.0f), glm::vec2(0.0f), false };

		void renderProjectExplorer(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer);

		void updateRenderTextureSize(GFXEngine::Graphics::Renderer& renderer, float width, float height, GFXEngine::Core::UIContext* ui);
		void placeModel(GFXEngine::Graphics::Renderer& renderer, const glm::vec3& position, GFXEngine::Graphics::StaticMeshModel* model);
		void renderBehavior(GFXEngine::Core::Behavior& behavior, GFXEngine::Graphics::Renderer& renderer);
		void renderProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop);
		void renderStringProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, std::string* value);
		void renderIntProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, int* value);
		void renderBoolProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, bool* value);
		void renderFloatProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, float* value);
		void renderVector2Property(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, glm::vec2* value);
		void renderVector3Property(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, glm::vec3* value);
		void renderVector4Property(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, glm::vec4* value);
		void renderEntityProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, GFXEngine::EngineTypes::EntityReference* value);
		void renderAssetProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, GFXEngine::EngineTypes::AssetReference* value);

		void markBehaviorForRemoval(GFXEngine::Core::Behavior* behavior);
		void cleanupRemovedBehaviors(GFXEngine::Graphics::Renderer& renderer);

	public:
		WorldEditor(GFXEngine::Core::Scene3D* scene, GFXEngine::AssetManager* assetManager, GFXEngine::BehaviorRegistry* behaviorRegistry, const std::filesystem::path& projectDirectory)
			: GFXEngine::Core::UIWidget(), m_scene(scene), m_assetManager(assetManager), m_behaviorRegistry(behaviorRegistry), m_projectDirectory(projectDirectory), m_currentExplorerPath(projectDirectory) {}
		~WorldEditor() = default;

		void init(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;
		void update(GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime) override;
		void beforeRender(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
		void renderSceneToTexture(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Core::UIContext* ui, uint32_t imageIndex);
		void render(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
		void afterRender(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
		void handleInput(GLFWwindow* window, int key, int mods, int action) override;
		void handleMouseInput(GLFWwindow* window, int button, int mods, int action) override;
		void handleMouseMove(GLFWwindow* window, double xpos, double ypos) override;
		void dispose(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;
	};
}