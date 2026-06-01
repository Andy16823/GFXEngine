project(GFXEditor)

add_executable(GFXEditor "main.cpp" "WorldEditor.h" "WorldEditor.cpp" "Editor.h" "Editor.cpp")

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

add_custom_command(TARGET GFXEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/shaders
        $<TARGET_FILE_DIR:GFXEditor>/shaders
)