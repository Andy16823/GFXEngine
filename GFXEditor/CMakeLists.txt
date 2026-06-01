project(GFXEditor)

add_library(GFXEditor STATIC "WorldEditor.h" "WorldEditor.cpp" "FileNameWidget.h" "FileNameWidget.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GFXEditor PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(GFXEditor PRIVATE
    GFXEngine
    LibGFX
    glm::glm
    imgui
    nlohmann_json::nlohmann_json
)