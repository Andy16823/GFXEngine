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
#include "FileNameWidget.h"
#include "TextInputDialog.h"
#include <memory>
#include <string>
#include "BackgroundTask.h"
#include "EditorPlugin.h"

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
		GFXEngine::Core::Scene3D* m_scene;
		GFXEngine::AssetManager* m_assetManager;
		GFXEngine::BehaviorRegistry* m_behaviorRegistry;
		GFXEngine::Core::Entity* m_selectedEntity = nullptr;

	private:
		bool m_dockspaceInitialized = false;
		ImGuiID m_topDockID;
		ImGuiID m_leftDockID;
		ImGuiID m_leftBottomDockID;
		ImGuiID m_centerDockID;
		ImGuiID m_bottomDockID;
		
	private:
		std::unique_ptr<GFXEngine::Graphics::RenderTexture> m_renderTexture;
		std::unique_ptr<GFXEngine::Graphics::Camera3D> m_editorCamera;
		std::unique_ptr<TextInputDialog> m_createFileDialog;
		std::vector<GFXEngine::Core::Behavior*> m_behaviorsToRemove;
		GFXEngine::BackgroundTaskManager m_backgroundTaskManager;
		std::vector<std::unique_ptr<EditorPlugin>> m_plugins;
		glm::vec2 m_sceneViewportWindowSize = glm::vec2(1024.0f, 1024.0f);
		ViewportCursorInfo m_viewportCursorInfo = { glm::vec2(0.0f), false };
		GFXEngine::Core::GuizmoOperation m_currentGuizmoOperation = GFXEngine::Core::GuizmoOperation::Translate;
		CursorDragInfo m_cursorDragInfo = { glm::vec2(0.0f), glm::vec2(0.0f), false };
		std::filesystem::path m_projectDirectory;
		std::filesystem::path m_currentExplorerPath;
		VkDescriptorSet m_descriptorSet;
	
	private:
		//************************************
		// Method:    updateRenderTextureSize
		// FullName:  GFXEditor::WorldEditor::updateRenderTextureSize
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: float width
		// Parameter: float height
		// Parameter: GFXEngine::Core::UIContext * ui
		//************************************
		void updateRenderTextureSize(GFXEngine::Graphics::Renderer& renderer, float width, float height, GFXEngine::Core::UIContext* ui);
		
		//************************************
		// Method:    placeModel
		// FullName:  GFXEditor::WorldEditor::placeModel
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const glm::vec3 & position
		// Parameter: GFXEngine::Graphics::StaticMeshModel * model
		//************************************
		void placeModel(GFXEngine::Graphics::Renderer& renderer, const glm::vec3& position, GFXEngine::Graphics::StaticMeshModel* model);
		
		//************************************
		// Method:    renderBehavior
		// FullName:  GFXEditor::WorldEditor::renderBehavior
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::Behavior & behavior
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		//************************************
		void renderBehavior(GFXEngine::Core::Behavior& behavior, GFXEngine::Graphics::Renderer& renderer);
		
		//************************************
		// Method:    markBehaviorForRemoval
		// FullName:  GFXEditor::WorldEditor::markBehaviorForRemoval
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::Behavior * behavior
		//************************************
		void markBehaviorForRemoval(GFXEngine::Core::Behavior* behavior);
		
		//************************************
		// Method:    cleanupRemovedBehaviors
		// FullName:  GFXEditor::WorldEditor::cleanupRemovedBehaviors
		// Access:    private 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		//************************************
		void cleanupRemovedBehaviors(GFXEngine::Graphics::Renderer& renderer);

	public:
		//************************************
		// Method:    WorldEditor
		// FullName:  GFXEditor::WorldEditor::WorldEditor
		// Access:    public 
		// Returns:   
		// Qualifier: : GFXEngine::Core::UIWidget(), m_scene(scene), m_assetManager(assetManager), m_behaviorRegistry(behaviorRegistry), m_projectDirectory(projectDirectory), m_currentExplorerPath(projectDirectory)
		// Parameter: GFXEngine::Core::Scene3D * scene
		// Parameter: GFXEngine::AssetManager * assetManager
		// Parameter: GFXEngine::BehaviorRegistry * behaviorRegistry
		// Parameter: const std::filesystem::path & projectDirectory
		//************************************
		WorldEditor(GFXEngine::Core::Scene3D* scene, GFXEngine::AssetManager* assetManager, GFXEngine::BehaviorRegistry* behaviorRegistry, const std::filesystem::path& projectDirectory)
			: GFXEngine::Core::UIWidget(), m_scene(scene), m_assetManager(assetManager), m_behaviorRegistry(behaviorRegistry), m_projectDirectory(projectDirectory), m_currentExplorerPath(projectDirectory) {}
		
		//************************************
		// Method:    ~WorldEditor
		// FullName:  GFXEditor::WorldEditor::~WorldEditor
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		~WorldEditor() = default;

	public:
		//************************************
		// Method:    getScene
		// FullName:  GFXEditor::WorldEditor::getScene
		// Access:    public 
		// Returns:   GFXEngine::Core::Scene3D*
		// Qualifier: const
		//************************************
		GFXEngine::Core::Scene3D* getScene() const { return m_scene; }
		
		//************************************
		// Method:    getAssetManager
		// FullName:  GFXEditor::WorldEditor::getAssetManager
		// Access:    public 
		// Returns:   GFXEngine::AssetManager*
		// Qualifier: const
		//************************************
		GFXEngine::AssetManager* getAssetManager() const { return m_assetManager; }
		
		//************************************
		// Method:    getBehaviorRegistry
		// FullName:  GFXEditor::WorldEditor::getBehaviorRegistry
		// Access:    public 
		// Returns:   GFXEngine::BehaviorRegistry*
		// Qualifier: const
		//************************************
		GFXEngine::BehaviorRegistry* getBehaviorRegistry() const { return m_behaviorRegistry; }
		
		//************************************
		// Method:    getSelectedEntity
		// FullName:  GFXEditor::WorldEditor::getSelectedEntity
		// Access:    public 
		// Returns:   GFXEngine::Core::Entity*
		// Qualifier: const
		//************************************
		GFXEngine::Core::Entity* getSelectedEntity() const { return m_selectedEntity; }
		
		//************************************
		// Method:    getProjectDirectory
		// FullName:  GFXEditor::WorldEditor::getProjectDirectory
		// Access:    public 
		// Returns:   std::filesystem::path
		// Qualifier: const
		//************************************
		std::filesystem::path getProjectDirectory() const { return m_projectDirectory; }
		
		//************************************
		// Method:    getBackgroundTaskManager
		// FullName:  GFXEditor::WorldEditor::getBackgroundTaskManager
		// Access:    public 
		// Returns:   GFXEngine::BackgroundTaskManager&
		// Qualifier:
		//************************************
		GFXEngine::BackgroundTaskManager& getBackgroundTaskManager() { return m_backgroundTaskManager; }
		
		//************************************
		// Method:    getEditorCamera
		// FullName:  GFXEditor::WorldEditor::getEditorCamera
		// Access:    public 
		// Returns:   GFXEngine::Graphics::Camera3D*
		// Qualifier: const
		//************************************
		GFXEngine::Graphics::Camera3D* getEditorCamera() const { return m_editorCamera.get(); }
		
		//************************************
		// Method:    getRenderTexture
		// FullName:  GFXEditor::WorldEditor::getRenderTexture
		// Access:    public 
		// Returns:   GFXEngine::Graphics::RenderTexture*
		// Qualifier: const
		//************************************
		GFXEngine::Graphics::RenderTexture* getRenderTexture() const { return m_renderTexture.get(); }
		
		//************************************
		// Method:    getCurrentGuizmoOperation
		// FullName:  GFXEditor::WorldEditor::getCurrentGuizmoOperation
		// Access:    public 
		// Returns:   GFXEngine::Core::GuizmoOperation
		// Qualifier: const
		//************************************
		GFXEngine::Core::GuizmoOperation getCurrentGuizmoOperation() const { return m_currentGuizmoOperation; }
		
		//************************************
		// Method:    getCursorDragInfo
		// FullName:  GFXEditor::WorldEditor::getCursorDragInfo
		// Access:    public 
		// Returns:   GFXEditor::CursorDragInfo
		// Qualifier: const
		//************************************
		CursorDragInfo getCursorDragInfo() const { return m_cursorDragInfo; }
		
		//************************************
		// Method:    getCreateFileDialog
		// FullName:  GFXEditor::WorldEditor::getCreateFileDialog
		// Access:    public 
		// Returns:   GFXEditor::TextInputDialog*
		// Qualifier: const
		//************************************
		TextInputDialog* getCreateFileDialog() const { return m_createFileDialog.get(); }
		
		//************************************
		// Method:    getTopDockID
		// FullName:  GFXEditor::WorldEditor::getTopDockID
		// Access:    public 
		// Returns:   ImGuiID
		// Qualifier: const
		//************************************
		ImGuiID getTopDockID() const { return m_topDockID; }
		
		//************************************
		// Method:    getLeftDockID
		// FullName:  GFXEditor::WorldEditor::getLeftDockID
		// Access:    public 
		// Returns:   ImGuiID
		// Qualifier: const
		//************************************
		ImGuiID getLeftDockID() const { return m_leftDockID; }
		
		//************************************
		// Method:    getLeftBottomDockID
		// FullName:  GFXEditor::WorldEditor::getLeftBottomDockID
		// Access:    public 
		// Returns:   ImGuiID
		// Qualifier: const
		//************************************
		ImGuiID getLeftBottomDockID() const { return m_leftBottomDockID; }
		
		//************************************
		// Method:    getCenterDockID
		// FullName:  GFXEditor::WorldEditor::getCenterDockID
		// Access:    public 
		// Returns:   ImGuiID
		// Qualifier: const
		//************************************
		ImGuiID getCenterDockID() const { return m_centerDockID; }
		
		//************************************
		// Method:    getBottomDockID
		// FullName:  GFXEditor::WorldEditor::getBottomDockID
		// Access:    public 
		// Returns:   ImGuiID
		// Qualifier: const
		//************************************
		ImGuiID getBottomDockID() const { return m_bottomDockID; }
		
		//************************************
		// Method:    setSelectedEntity
		// FullName:  GFXEditor::WorldEditor::setSelectedEntity
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::Entity * entity
		//************************************
		void setSelectedEntity(GFXEngine::Core::Entity* entity) { m_selectedEntity = entity; }
		
		//************************************
		// Method:    setCurrentGuizmoOperation
		// FullName:  GFXEditor::WorldEditor::setCurrentGuizmoOperation
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::GuizmoOperation operation
		//************************************
		void setCurrentGuizmoOperation(GFXEngine::Core::GuizmoOperation operation) { m_currentGuizmoOperation = operation; }

	public:
		//************************************
		// Method:    addPlugin
		// FullName:  GFXEditor::WorldEditor::addPlugin
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: std::unique_ptr<EditorPlugin> plugin
		//************************************
		void addPlugin(std::unique_ptr<EditorPlugin> plugin) {
			plugin->onRegister(*this);
			m_plugins.push_back(std::move(plugin));
		}

	public:
		//************************************
		// Method:    init
		// FullName:  GFXEditor::WorldEditor::init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		//************************************
		void init(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;
		
		//************************************
		// Method:    update
		// FullName:  GFXEditor::WorldEditor::update
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::InputManager & input
		// Parameter: float deltaTime
		//************************************
		void update(GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime) override;
		
		//************************************
		// Method:    beforeRender
		// FullName:  GFXEditor::WorldEditor::beforeRender
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: uint32_t imageIndex
		//************************************
		void beforeRender(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
		
		//************************************
		// Method:    renderSceneToTexture
		// FullName:  GFXEditor::WorldEditor::renderSceneToTexture
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: GFXEngine::Core::UIContext * ui
		// Parameter: uint32_t imageIndex
		//************************************
		void renderSceneToTexture(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Core::UIContext* ui, uint32_t imageIndex);
		
		//************************************
		// Method:    render
		// FullName:  GFXEditor::WorldEditor::render
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: uint32_t imageIndex
		//************************************
		void render(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
		
		//************************************
		// Method:    afterRender
		// FullName:  GFXEditor::WorldEditor::afterRender
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: uint32_t imageIndex
		//************************************
		void afterRender(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
		
		//************************************
		// Method:    handleInput
		// FullName:  GFXEditor::WorldEditor::handleInput
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GLFWwindow * window
		// Parameter: int key
		// Parameter: int mods
		// Parameter: int action
		//************************************
		void handleInput(GLFWwindow* window, int key, int mods, int action) override;
		
		//************************************
		// Method:    handleMouseInput
		// FullName:  GFXEditor::WorldEditor::handleMouseInput
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GLFWwindow * window
		// Parameter: int button
		// Parameter: int mods
		// Parameter: int action
		//************************************
		void handleMouseInput(GLFWwindow* window, int button, int mods, int action) override;
		
		//************************************
		// Method:    handleMouseMove
		// FullName:  GFXEditor::WorldEditor::handleMouseMove
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GLFWwindow * window
		// Parameter: double xpos
		// Parameter: double ypos
		//************************************
		void handleMouseMove(GLFWwindow* window, double xpos, double ypos) override;
		
		//************************************
		// Method:    dispose
		// FullName:  GFXEditor::WorldEditor::dispose
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		//************************************
		void dispose(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;

	public:
		//************************************
		// Method:    renderProperty
		// FullName:  GFXEditor::WorldEditor::renderProperty
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		//************************************
		void renderProperty(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop);
		
		//************************************
		// Method:    renderStringProperty
		// FullName:  GFXEditor::WorldEditor::renderStringProperty
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		// Parameter: std::string * value
		//************************************
		void renderStringProperty(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop, std::string* value);
		
		//************************************
		// Method:    renderIntProperty
		// FullName:  GFXEditor::WorldEditor::renderIntProperty
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		// Parameter: int * value
		//************************************
		void renderIntProperty(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop, int* value);
		
		//************************************
		// Method:    renderBoolProperty
		// FullName:  GFXEditor::WorldEditor::renderBoolProperty
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		// Parameter: bool * value
		//************************************
		void renderBoolProperty(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop, bool* value);
		
		//************************************
		// Method:    renderFloatProperty
		// FullName:  GFXEditor::WorldEditor::renderFloatProperty
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		// Parameter: float * value
		//************************************
		void renderFloatProperty(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop, float* value);
		
		//************************************
		// Method:    renderVector2Property
		// FullName:  GFXEditor::WorldEditor::renderVector2Property
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		// Parameter: glm::vec2 * value
		//************************************
		void renderVector2Property(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop, glm::vec2* value);
		
		//************************************
		// Method:    renderVector3Property
		// FullName:  GFXEditor::WorldEditor::renderVector3Property
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		// Parameter: glm::vec3 * value
		//************************************
		void renderVector3Property(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop, glm::vec3* value);
		
		//************************************
		// Method:    renderVector4Property
		// FullName:  GFXEditor::WorldEditor::renderVector4Property
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		// Parameter: glm::vec4 * value
		//************************************
		void renderVector4Property(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop, glm::vec4* value);
		
		//************************************
		// Method:    renderEntityProperty
		// FullName:  GFXEditor::WorldEditor::renderEntityProperty
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		// Parameter: GFXEngine::EngineTypes::EntityReference * value
		//************************************
		void renderEntityProperty(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop, GFXEngine::EngineTypes::EntityReference* value);
		//************************************
		// Method:    renderAssetProperty
		// FullName:  GFXEditor::WorldEditor::renderAssetProperty
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Core::PropertyInfo & prop
		// Parameter: GFXEngine::EngineTypes::AssetReference * value
		//************************************
		void renderAssetProperty(const std::string& label, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Core::PropertyInfo& prop, GFXEngine::EngineTypes::AssetReference* value);
	};
}