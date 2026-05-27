# CMakeList.txt: CMake-Projekt für "GFXEngine". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_library(GFXEngine STATIC  "RuntimeContext.h" "Renderer.h" "Renderer.cpp" "OffscreenRenderPass.h" "OffscreenRenderPass.cpp" "PipelineManager.h" "PipelineManager.cpp"   "RenderShader.h" "RenderShader.cpp" "DataTypes.h" "Utils.h" "Utils.cpp" "Shapes.h" "Shapes.cpp" "Camera3D.h" "Camera3D.cpp" "Transform.h" "Transform.cpp" "Entity.h" "Entity.cpp" "Sprite.h" "Sprite.cpp" "Material.h" "SpriteMaterial.h" "SpriteMaterial.cpp" "RenderTarget.h"  "RenderTexture.h" "RenderTexture.cpp"   "Camera.h" "Behavior.h" "Mesh.h" "Mesh.cpp" "MeshModel.h" "StaticMeshModel.h" "StaticMeshModel.cpp" "UnlitMaterial.h" "UnlitMaterial.cpp" "Model.h" "Model.cpp"           "InstancedModel.h" "InstancedModel.cpp" "Game.h" "Game.cpp" "Scene.h" "Scene3D.h" "Scene3D.cpp"   "EnviromentMap.h" "EnviromentMap.cpp" "PBRMaterial.h" "PBRMaterial.cpp" "DirectionalLight.h" "DirectionalLight.cpp" "ServiceManager.h"  "Raycast.h" "Raycast.cpp" "AABB.h" "AABB.cpp"   "GraphicsPipeline.h" "DebugBhv.h" "DebugBhv.cpp" "EngineDefinitions.h" "UIContext.h" "UIContext.cpp" "GraphicsPipeline.cpp" "AssetManager.h" "AssetManager.cpp" "Asset.h" "Asset.cpp" "BehaviorRegistry.h" "BehaviorRegistry.cpp" "ISerializable.h" "SerializationContext.h" "SerializationContext.cpp" "DataResource.h" "DataResource.cpp" "PropertyInfo.h" "EntityFactory.h"  "InputManager.h" "InputManager.cpp" "UIWidget.h" "MeshBuilder.h" "MeshBuilder.cpp" "PipelineBuilder.h" "PipelineBuilder.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GFXEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
# LibGFX linken (GLFW und Vulkan kommen automatisch mit)
target_link_libraries(GFXEngine 
    PRIVATE LibGFX
    PRIVATE glm::glm
    PRIVATE stb_image
    PRIVATE assimp::assimp
    PRIVATE imgui
    PRIVATE imguizmo
    PRIVATE nlohmann_json::nlohmann_json
)

# Include-Verzeichnisse (falls nötig)
target_include_directories(GFXEngine 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# C++ Standard setzen
target_compile_features(GFXEngine 
    PUBLIC cxx_std_20
)