# CMakeList.txt: CMake-Projekt für "GFXEngine". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_library(GFXEngine STATIC "GFXEngine.cpp" "GFXEngine.h" "Renderer.h" "Renderer.cpp" "OffscreenRenderPass.h" "OffscreenRenderPass.cpp" "PipelineManager.h" "PipelineManager.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GFXEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
# LibGFX linken (GLFW und Vulkan kommen automatisch mit)
target_link_libraries(GFXEngine 
    PRIVATE LibGFX
    PRIVATE glm::glm
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