#include "WorldEditor.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Model.h"
#include "Raycast.h"
#include "InstancedModel.h"
#include "Utils.h"
#include <iostream>
#include <misc/cpp/imgui_stdlib.h>
#include "DataTypes.h"
#include "PropertyInfo.h"

using namespace GFXEditor;
using namespace GFXEngine;
using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;

void WorldEditor::renderProjectExplorer(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer)
{
	ImGui::Begin("Project Explorer");

	// Context menu for the project explorer
	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::MenuItem("Create Directory"))
		{
			m_showCreateDirectoryPopup = true;
		}

		if (ImGui::MenuItem("Option 2"))
		{
			// Aktion
		}

		ImGui::EndPopup();
	}

	// Entries in the current directory
	for (const auto& entry : std::filesystem::directory_iterator(m_currentExplorerPath)) {
		if (entry.is_directory())
		{
			if (ImGui::Selectable((entry.path().filename().string() + "/").c_str())) {
				m_currentExplorerPath = entry.path();
			}
		}
		else if (entry.is_regular_file()) {
			if (ImGui::Selectable(entry.path().filename().string().c_str())) {
				std::string extension = entry.path().extension().string();
				std::cout << "Selected file: " << entry.path() << std::endl;
			}
		}
	}

	if (m_showCreateDirectoryPopup) {
		ImGui::OpenPopup("CreateDirectoryPopup");
		if (ImGui::BeginPopupModal("CreateDirectoryPopup", &m_showCreateDirectoryPopup, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Create a new directory");
			static char newDirectoryName[256] = "";
			ImGui::InputText("Directory Name", newDirectoryName, sizeof(newDirectoryName));
			if (ImGui::Button("Create Directory##create_dir_modal_btn")) {
				std::filesystem::path newDirPath = m_currentExplorerPath / newDirectoryName;
				if (!std::filesystem::exists(newDirPath)) {
					try {
						std::filesystem::create_directory(newDirPath);
						std::cout << "Directory created: " << newDirPath << std::endl;
					}
					catch (const std::filesystem::filesystem_error& e) {
						std::cerr << "Error creating directory: " << e.what() << std::endl;
					}
				}
				else {
					std::cerr << "Directory already exists: " << newDirPath << std::endl;
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel##create_dir_modal_cancel_btn")) {
				m_showCreateDirectoryPopup = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	ImGui::End();
}

void WorldEditor::updateRenderTextureSize(GFXEngine::Graphics::Renderer& renderer, float width, float height, GFXEngine::Core::UIContext* ui)
{
	// Avoid resizing to zero dimensions
	if (width <= 0 || height <= 0) {
		return;
	}
	renderer.waitIdle();

	// Clamp the width and height to a minimum of 1 to prevent issues with zero-sized textures
	uint32_t w = std::max((uint32_t)width, 1u);
	uint32_t h = std::max((uint32_t)height, 1u);

	// Update the camera's aspect ratio to match the new render texture size
	m_editorCamera->setAspectRatio(static_cast<float>(w) / static_cast<float>(h));

	// Resize the render texture and update the descriptor set
	m_renderTexture->resize(renderer, { w, h }, renderer.getOffscreenRenderPass());
	ui->freeTextureDescriptorSet(renderer, m_descriptorSet);
	m_descriptorSet = ui->createTextureDescriptorSet(renderer, *m_renderTexture);
}

void WorldEditor::placeModel(GFXEngine::Graphics::Renderer& renderer, const glm::vec3& position, GFXEngine::Graphics::StaticMeshModel* model)
{
	auto entity = std::make_unique<GFXEngine::Core::Model>(model);
	entity->setName(model->getName());
	entity->setPosition(position);
	entity->setScale(glm::vec3(0.1f));
	entity->setRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	entity->init(*m_scene, renderer);
	m_scene->addEntity(std::move(entity));
}

void WorldEditor::renderBehavior(GFXEngine::Core::Behavior& behavior, GFXEngine::Graphics::Renderer& renderer)
{
	std::string name = behavior.getName();
	std::vector<GFXEngine::Core::PropertyInfo> properties = behavior.getProperties();
	if (ImGui::CollapsingHeader(UIContext::createLabelID(name, behavior.getUUID()).c_str()))
	{
		for (const auto& prop : properties)
		{
			const std::string label = UIContext::createLabelID(prop.name, behavior.getUUID());
			this->renderProperty(label, prop);
		}
		if (ImGui::Button(GFXEngine::Core::UIContext::createLabelID("Remove Behavior", behavior.getUUID()).c_str())) {
			this->markBehaviorForRemoval(&behavior);
		}
	}
}

void WorldEditor::renderProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop)
{
	// std::get_if returns a pointer to the value stored in the variant.
	// Since the variant stores a std::string*,
	// get_if returns a std::string**.
	if (auto* dataPtr = std::get_if<std::string*>(&prop.data)) {
		this->renderStringProperty(label, prop, *dataPtr);
	}
	else if (auto* dataPtr = std::get_if<int*>(&prop.data)) {
		this->renderIntProperty(label, prop, *dataPtr);
	}
	else if (auto* dataPtr = std::get_if<bool*>(&prop.data)) {
		this->renderBoolProperty(label, prop, *dataPtr);
	}
	else if (auto* dataPtr = std::get_if<float*>(&prop.data)) {
		this->renderFloatProperty(label, prop, *dataPtr);
	}
	else if (auto* dataPtr = std::get_if<glm::vec2*>(&prop.data)) {
		this->renderVector2Property(label, prop, *dataPtr);
	}
	else if (auto* dataPtr = std::get_if<glm::vec3*>(&prop.data)) {
		this->renderVector3Property(label, prop, *dataPtr);
	}
	else if (auto* dataPtr = std::get_if<glm::vec4*>(&prop.data)) {
		this->renderVector4Property(label, prop, *dataPtr);
	}
	else if (auto* dataPtr = std::get_if<glm::quat*>(&prop.data)) {
		// Quaternions can be represented as Vector4 in the UI for editing purposes
		this->renderVector4Property(label, prop, reinterpret_cast<glm::vec4*>(*dataPtr));
	}
	else if (auto* dataPtr = std::get_if<GFXEngine::EngineTypes::EntityReference*>(&prop.data)) {
		this->renderEntityProperty(label, prop, *dataPtr);
	}
	else if (auto* dataPtr = std::get_if<GFXEngine::EngineTypes::AssetReference*>(&prop.data)) {
		this->renderAssetProperty(label, prop, *dataPtr);
	}
	else {
		ImGui::Text("Unsupported property type");
	}
}

void WorldEditor::renderStringProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, std::string* value)
{
	auto data = value;
	switch (prop.hint)
	{
	case GFXEngine::Core::PropertyHint::Enum:
		if (auto* meta = std::get_if<GFXEngine::Core::EnumMetaData>(&prop.metaData))
		{
			if (ImGui::BeginCombo(label.c_str(), data->c_str())) {
				for (const auto& option : meta->options) {
					bool isSelected = (*data == option);
					if (ImGui::Selectable(option.c_str(), isSelected)) {
						*data = option;
						if (prop.onChanged) {
							prop.onChanged();
						}
					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
		}
		else {
			throw std::runtime_error("Enum property missing EnumMetaData. Do you forgot to expose it?");
		}
		break;
	case GFXEngine::Core::PropertyHint::ReadOnly:
		ImGui::InputText(label.c_str(), data, ImGuiInputTextFlags_ReadOnly);
		break;
	case GFXEngine::Core::PropertyHint::Multiline:
		if (ImGui::InputTextMultiline(label.c_str(), data)) {
			if (prop.onChanged) {
				prop.onChanged();
			}
		}
		break;
	default:
		if (ImGui::InputText(label.c_str(), data)) {
			if (prop.onChanged) {
				prop.onChanged();
			}
		}
		break;
	}
}

void WorldEditor::renderIntProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, int* value)
{
	if (ImGui::InputInt(label.c_str(), value)) {
		if (prop.onChanged) {
			prop.onChanged();
		}
	}
}

void WorldEditor::renderBoolProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, bool* value)
{
	if (ImGui::Checkbox(label.c_str(), value)) {
		if (prop.onChanged) {
			prop.onChanged();
		}
	}
}

void WorldEditor::renderFloatProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, float* value)
{
	if (ImGui::InputFloat(label.c_str(), value)) {
		if (prop.onChanged) {
			prop.onChanged();
		}
	}
}

void WorldEditor::renderVector2Property(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, glm::vec2* value)
{
	if (ImGui::InputFloat2(label.c_str(), reinterpret_cast<float*>(value))) {
		if (prop.onChanged) {
			prop.onChanged();
		}
	}
}

void WorldEditor::renderVector3Property(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, glm::vec3* value)
{
	switch (prop.hint)
	{
	case PropertyHint::Color:
		if (ImGui::ColorEdit3(label.c_str(), reinterpret_cast<float*>(value))) {
			if (prop.onChanged)
			{
				prop.onChanged();
			}
		}
		break;
	default:
		if (ImGui::InputFloat3(label.c_str(), reinterpret_cast<float*>(value))) {
			if (prop.onChanged)
			{
				prop.onChanged();
			}
		}
		break;
	}
}

void WorldEditor::renderVector4Property(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, glm::vec4* value)
{
	switch (prop.hint)
	{
	case PropertyHint::Color:
		if (ImGui::ColorEdit4(label.c_str(), reinterpret_cast<float*>(value)))
		{
			if (prop.onChanged)
			{
				prop.onChanged();
			}
		}
		break;
	default:
		if (ImGui::InputFloat4(label.c_str(), reinterpret_cast<float*>(value))) {
			if (prop.onChanged) {
				prop.onChanged();
			}
		}
		break;
	}
}

void WorldEditor::renderEntityProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, GFXEngine::EngineTypes::EntityReference* ref)
{
	std::string currentName = ref->isResolved() ? ref->getEntity().getName() : "None";

	if (ImGui::BeginCombo(label.c_str(), currentName.c_str())) {
		if (ImGui::Selectable("None", !ref->isResolved())) {
			ref->clear();
			if (prop.onChanged) {
				prop.onChanged();
			}
		}

		m_scene->forEachEntity([&](GFXEngine::Core::Entity& entity) {
			bool isSelected = (ref->isResolved() && &ref->getEntity() == &entity);
			if (ImGui::Selectable(entity.getName().c_str(), isSelected)) {
				ref->setEntity(&entity);
				if (prop.onChanged) {
					prop.onChanged();
				}
			}
			if (isSelected) {
				ImGui::SetItemDefaultFocus();
			}
			});
		// Here you would populate the combo with available entities
		ImGui::EndCombo();
	}
}

void WorldEditor::renderAssetProperty(const std::string& label, const GFXEngine::Core::PropertyInfo& prop, GFXEngine::EngineTypes::AssetReference* value)
{
	const auto asset = static_cast<GFXEngine::Asset*>(value->asset);
	if (ImGui::BeginCombo(label.c_str(), asset ? asset->getName().c_str() : "None"))
	{
		// Handle EnviromentMap assets
		if (value->isTypeOf<GFXEngine::Graphics::EnviromentMap>())
		{
			m_assetManager->forEachAssetOfType<GFXEngine::Graphics::EnviromentMap>([&](GFXEngine::Graphics::EnviromentMap* envMap) {
				if (ImGui::Selectable(envMap->getName().c_str()))
				{
					value->set(envMap);
					if (prop.onChanged) {
						prop.onChanged();
					}
				}
				});
		}
		// Handle MeshModel assets
		else if (value->isTypeOf<GFXEngine::Graphics::MeshModel>())
		{
			m_assetManager->forEachAssetOfType<GFXEngine::Graphics::MeshModel>([&](GFXEngine::Graphics::MeshModel* model) {
				if (ImGui::Selectable(UIContext::createLabelID(model->getName(), model->getUUID()).c_str()))
				{
					value->set(model);
					if (prop.onChanged) {
						prop.onChanged();
					}
				}
				});
		}
		ImGui::EndCombo();
	}
}

void WorldEditor::markBehaviorForRemoval(GFXEngine::Core::Behavior* behavior)
{
	m_behaviorsToRemove.push_back(behavior);
}

void WorldEditor::cleanupRemovedBehaviors(GFXEngine::Graphics::Renderer& renderer)
{
	if (m_behaviorsToRemove.empty()) {
		return;
	}

	renderer.waitIdle(); // Ensure the renderer is idle before modifying behaviors to avoid issues with behaviors being used while they're being removed
	for (auto* behavior : m_behaviorsToRemove) {
		m_selectedEntity->removeBehavior(behavior, [this, &renderer](GFXEngine::Core::Behavior* behavior) {
			behavior->destroy(*m_scene, renderer);
			});
	}
	m_behaviorsToRemove.clear();
}

void WorldEditor::init(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer)
{
	// Create the render texture for the scene viewport
	m_renderTexture = std::make_unique<GFXEngine::Graphics::RenderTexture>();
	m_renderTexture->create(renderer, { 1024, 1024 }, renderer.getOffscreenRenderPass());
	m_descriptorSet = context.createTextureDescriptorSet(renderer, *m_renderTexture);

	// Create the editor camera
	m_editorCamera = std::make_unique<GFXEngine::Graphics::Camera3D>(glm::vec3(0.0f, 35.0f, 0.0f), 1024.0f / 1024.0f, 0.1f, 1000.0f);
	m_editorCamera->getTransform().rotateWorld(-35.0f, 45.0f, 0.0f);
	m_editorCamera->createDescriptorSets(renderer, renderer.getUniformBufferLayout());

	// Initialize the camera buffers for all swapchain images
	for (uint32_t i = 0; i < renderer.getSwapchainImageCount(); i++)
	{
		m_editorCamera->updateCameraBuffers(renderer, i);
	}
}

void WorldEditor::update(GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime)
{
	if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && m_viewportCursorInfo.isHovering) {
		glm::vec4 viewport = glm::vec4(0.0f, 0.0f, m_sceneViewportWindowSize.x, m_sceneViewportWindowSize.y);
		auto ray = GFXEngine::Physics::Raycast::screenPointToRay(m_viewportCursorInfo.position, *m_editorCamera, viewport);

		auto candidates = m_scene->collectEntities([&](GFXEngine::Core::Entity& entity) {
			if (!entity.isVisible())
				return false;
			auto aabb = entity.getWorldAABB();
			float tMin, tMax;
			return GFXEngine::Physics::Raycast::rayIntersectsAABB(ray, aabb, tMin, tMax);
			});

		GFXEngine::Core::Entity* closestEntity = nullptr;
		float closestT = std::numeric_limits<float>::max();
		for (auto& entity : candidates) {
			if (dynamic_cast<GFXEngine::Core::InstancedModel*>(entity))
			{
				continue;
			}

			size_t meshes = entity->getMeshCount();
			for (size_t i = 0; i < meshes; i++) {
				GFXEngine::Physics::RaycastHit hitInfo;
				auto meshMaterialPair = entity->getMeshAndMaterial(i);
				const auto& [mesh, material] = meshMaterialPair.value(); // TODO: add generic mesh raycast
				if (GFXEngine::Physics::Raycast::rayIntersectsMesh(ray, entity->getTransform(), mesh, hitInfo)) {
					if (hitInfo.distance < closestT) {
						closestT = hitInfo.distance;
						closestEntity = entity;
					}
				}
			}
		}

		if (closestEntity) {
			std::cout << "Clicked on entity: " << closestEntity->getName() << std::endl;
			m_selectedEntity = closestEntity;
		}
	}
}

void WorldEditor::beforeRender(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	m_scene->beforeRender(renderer, *m_editorCamera, imageIndex);
}

void WorldEditor::renderSceneToTexture(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Core::UIContext* ui, uint32_t imageIndex)
{
	// Avoid rendering if the viewport size is zero or negative to prevent issues with zero-sized render textures
	if (m_sceneViewportWindowSize.x <= 0 || m_sceneViewportWindowSize.y <= 0) {
		return;
	}

	// Check if the render texture size matches the current viewport size, and resize if necessary
	auto currentSize = m_renderTexture->getIntSize();
	if (currentSize.x != static_cast<uint32_t>(m_sceneViewportWindowSize.x) || currentSize.y != static_cast<uint32_t>(m_sceneViewportWindowSize.y)) {
		this->updateRenderTextureSize(renderer, m_sceneViewportWindowSize.x, m_sceneViewportWindowSize.y, ui);
	}

	// Update the editor camera's buffers for the current frame
	m_editorCamera->updateCameraBuffers(renderer, imageIndex);

	// Save the current viewport and scissor to restore them after rendering to the texture
	VkViewport viewport = renderer.getViewport();
	VkRect2D scissor = renderer.getScissor();

	// Render the scene to the offscreen render texture
	renderer.beginRenderPass(renderer.getOffscreenRenderPass(), m_renderTexture->getFramebuffer(), m_renderTexture->getViewport(), m_renderTexture->getScissor(), imageIndex);
	m_scene->render(renderer, *m_editorCamera, imageIndex);
	renderer.endRenderPass(imageIndex);

	// Restore the original viewport and scissor after rendering to the texture
	renderer.setViewport(viewport);
	renderer.setScissor(scissor);
}

void WorldEditor::render(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;
	if (UIContext::gizmoIsOver() || UIContext::gizmoIsUsing()) {
		windowFlags |= ImGuiWindowFlags_NoMove;
	}

	// Render the GUI for the world editor
	UIContext::beginnFullscreen("World Editor", windowFlags);
	ImGuiID dockspaceID = ImGui::GetID("WorldEditorDockspace");
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

	if (!m_dockspaceInitialized)
	{
		ImGui::DockBuilderRemoveNode(dockspaceID);
		ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspaceID, ImVec2(800.0f, 600.0f));

		// DOCKING LAYOUT
		ImGuiID mainDockID = dockspaceID;
		ImGuiID topDockID, leftDockID, leftBottomDockID, centerDockID, bottomDockID;

		// TOP
		ImGui::DockBuilderSplitNode(
			mainDockID,
			ImGuiDir_Up,
			0.06f,
			&topDockID,
			&mainDockID
		);

		ImGui::DockBuilderGetNode(topDockID)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

		// LEFT
		ImGui::DockBuilderSplitNode(
			mainDockID,
			ImGuiDir_Left,
			0.4f,
			&leftDockID,
			&centerDockID
		);

		// LEFT BOTTOM
		ImGui::DockBuilderSplitNode(
			leftDockID,
			ImGuiDir_Down,
			0.5f,
			&leftBottomDockID,
			&leftDockID
		);

		// BOTTOM
		ImGui::DockBuilderSplitNode(
			centerDockID,
			ImGuiDir_Down,
			0.35f,
			&bottomDockID,
			&centerDockID
		);

		ImGui::DockBuilderDockWindow(
			"World Editor Toolbar",
			topDockID
		);

		ImGui::DockBuilderDockWindow(
			"Scene Hierarchy",
			leftBottomDockID
		);

		ImGui::DockBuilderDockWindow(
			"Selected Entity",
			leftDockID
		);

		ImGui::DockBuilderDockWindow(
			"Scene Settings",
			leftDockID
		);

		ImGui::DockBuilderDockWindow(
			"Assets",
			bottomDockID
		);

		ImGui::DockBuilderDockWindow(
			"Debug",
			bottomDockID
		);

		ImGui::DockBuilderDockWindow(
			"Scene Viewport",
			centerDockID
		);

		ImGui::DockBuilderFinish(dockspaceID);

		m_dockspaceInitialized = true;
	}
	ImGui::End();

	auto toolbarFlags = ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoScrollbar;

	ImGui::Begin("World Editor Toolbar", nullptr, toolbarFlags);
	UIContext::createButton("Translate", [&]() {
		m_currentGuizmoOperation = GFXEngine::Core::GuizmoOperation::Translate;
		});

	ImGui::SameLine();

	UIContext::createButton("Rotate", [&]() {
		m_currentGuizmoOperation = GFXEngine::Core::GuizmoOperation::Rotate;
		});

	ImGui::SameLine();

	UIContext::createButton("Scale", [&]() {
		m_currentGuizmoOperation = GFXEngine::Core::GuizmoOperation::Scale;
		});

	ImGui::End();

	ImGui::Begin("Scene Hierarchy");
	if (ImGui::CollapsingHeader("Entities"))
	{
		m_scene->forEachEntity([&](GFXEngine::Core::Entity& entity) {
			bool isSelected = (m_selectedEntity == &entity);
			if (ImGui::Selectable(entity.getName().c_str(), isSelected)) {
				m_selectedEntity = &entity;
			}
			});
	}
	ImGui::End();


	ImGui::Begin("Scene Settings");
	auto sceneProps = m_scene->getProperties();
	for (const auto& prop : sceneProps)
	{
		const std::string label = UIContext::createLabelID(prop.name, "SCENE");
		this->renderProperty(label, prop);
	}

	UIContext::createButton("Save Scene", [&]() {
		std::string path = "C:\\Users\\andy1\\Documents\\gfxscene.json";
		if (!path.empty()) {
			auto jsonData = m_scene->serialize();
			GFXEngine::Utils::saveJsonToFile(jsonData, path);
		}
		});

	ImGui::End();

	ImGui::Begin("Assets");
	if (ImGui::CollapsingHeader("Models")) {
		m_assetManager->forEachAssetOfType<GFXEngine::Graphics::StaticMeshModel>([&](GFXEngine::Graphics::StaticMeshModel* model) {
			UIContext::createButton(model->getName().c_str(), [&]() {
				this->placeModel(renderer, glm::vec3(0.0f, 0.0f, 0.0f), model);
				});
			});
	}
	ImGui::End();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Scene Viewport");
	ImGui::PopStyleVar();
	auto viewportPos = UIContext::toVec2(ImGui::GetCursorScreenPos());
	m_sceneViewportWindowSize = UIContext::toVec2(ImGui::GetContentRegionAvail());
	UIContext::createImage(m_descriptorSet, glm::vec2(m_sceneViewportWindowSize.x, m_sceneViewportWindowSize.y));
	auto mousePos = UIContext::toVec2(ImGui::GetMousePos());
	m_viewportCursorInfo.position = mousePos - viewportPos;
	m_viewportCursorInfo.isHovering =
		m_viewportCursorInfo.position.x >= 0 &&
		m_viewportCursorInfo.position.y >= 0 &&
		m_viewportCursorInfo.position.x < m_sceneViewportWindowSize.x &&
		m_viewportCursorInfo.position.y < m_sceneViewportWindowSize.y;

	if (m_selectedEntity)
	{
		glm::mat4 view = m_editorCamera->getViewMatrix();
		glm::mat4 projection = m_editorCamera->getProjectionMatrix();
		glm::mat4 model = m_selectedEntity->getModelMatrix();
		glm::vec4 rect = glm::vec4(viewportPos, m_sceneViewportWindowSize);
		if (UIContext::transformGizmo(view, projection, model, rect, m_currentGuizmoOperation)) {
			m_selectedEntity->setModelMatrix(model);
			m_selectedEntity->propertyChanged(Entity::PropertyComponentType::Transform);
		}
	}

	ImGui::End();

	ImGui::Begin("Debug");
	ImGui::InputFloat3("Camera Position", glm::value_ptr(m_editorCamera->getTransform().position));
	ImGui::InputFloat3("Relative Position", glm::value_ptr(m_viewportCursorInfo.position));
	ImGui::Checkbox("Hovering Viewport", &m_viewportCursorInfo.isHovering);
	ImGui::End();

	ImGui::Begin("Selected Entity");
	if (m_selectedEntity) {
		auto props = m_selectedEntity->getProperties();
		for (const auto& prop : props) {
			const std::string label = UIContext::createLabelID(prop.name, m_selectedEntity->getUUID());
			this->renderProperty(label, prop);
		}
		m_selectedEntity->foreachBehavior([&](GFXEngine::Core::Behavior* behavior) {
			this->renderBehavior(*behavior, renderer);
			});

		ImGui::Separator();
		if (ImGui::BeginCombo("Add Behavior", "")) {
			m_behaviorRegistry->foreachBehavior([&](const std::string& behaviorName) {
				if (ImGui::Selectable(behaviorName.c_str())) {
					auto bhv = m_selectedEntity->addBehavior(m_behaviorRegistry->createBehavior(behaviorName));
					bhv->init(*m_scene, renderer);
				}
				});
			ImGui::EndCombo();
		}
	}
	else {
		ImGui::Text("No entity selected");
	}
	ImGui::End();

	this->renderProjectExplorer(context, renderer);

	// Instances from InstancedModel
	if (auto instancedModel = dynamic_cast<GFXEngine::Core::InstancedModel*>(m_selectedEntity)) {
		ImGui::Begin("Instances");
		for (size_t i = 0; i < instancedModel->getInstanceCount(); i++) {
			if (ImGui::Selectable(("Instance_" + std::to_string(i)).c_str())) {
				std::cout << "Selected instance " << i << std::endl;
			}
		}
		ImGui::End();
	}
}

void WorldEditor::afterRender(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	this->cleanupRemovedBehaviors(renderer);
}

void WorldEditor::handleInput(GLFWwindow* window, int key, int mods, int action)
{
	// Dont process input if ImGui wants to capture it (e.g. when typing in a text field or using a combo box)
	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureKeyboard) {
		return;
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_W)
		{
			m_editorCamera->getTransform().forward(1.0f);
		}
		else if (key == GLFW_KEY_S)
		{
			m_editorCamera->getTransform().forward(-1.0f);
		}
		else if (key == GLFW_KEY_A)
		{
			m_editorCamera->getTransform().right(-1.0f);
		}
		else if (key == GLFW_KEY_D)
		{
			m_editorCamera->getTransform().right(1.0f);
		}
		else if (key == GLFW_KEY_Q)
		{
			m_editorCamera->getTransform().rotateWorld(0.0f, -1.0f, 0.0f);
		}
		else if (key == GLFW_KEY_E)
		{
			m_editorCamera->getTransform().rotateWorld(0.0f, 1.0f, 0.0f);
		}
	}
}

void WorldEditor::dispose(GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer)
{
	m_renderTexture->destroy(renderer);
	m_editorCamera->destroyDescriptorSets(renderer);
}

void WorldEditor::handleMouseInput(GLFWwindow* window, int button, int mods, int action)
{
	if (ImGui::GetIO().WantCaptureKeyboard) {
		return;
	}

	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_RIGHT) 
		{
			m_cursorDragInfo.isDragging = true;
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			m_cursorDragInfo.startPosition = glm::vec2(xpos, ypos);
			m_cursorDragInfo.currentPosition = glm::vec2(xpos, ypos);
		}
	}

	if (action == GLFW_RELEASE) {
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			m_cursorDragInfo.isDragging = false;
		}
	}
}

void WorldEditor::handleMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	if (m_cursorDragInfo.isDragging) 
	{
		auto delta = glm::vec2(xpos, ypos) - m_cursorDragInfo.currentPosition;
		float sensitivity = 0.1f;
		float m_yaw = -delta.x * sensitivity;
		float m_pitch = -delta.y * sensitivity;

		glm::quat rotation = m_editorCamera->getTransform().rotation;
		glm::quat yaw = glm::angleAxis(glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat pitch = glm::angleAxis(glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));

		m_editorCamera->getTransform().rotation = glm::normalize(yaw * pitch * rotation);
		m_cursorDragInfo.currentPosition = glm::vec2(xpos, ypos);
	}
}
