# GFXEngine

Small Vulkan based game engine written in C++.

This project started as a learning project for Vulkan and slowly evolved into a custom engine used for a space simulation game.
The focus of the engine is not to compete with large engines like Unreal or Unity, but to provide a flexible and understandable codebase tailored to the needs of the project.

## Current Features

* Vulkan renderer
* Swapchain recreation
* Instanced rendering
* Offscreen rendering
* Scene serialization
* Asset management
* Assimp model loading
* Simple PBR renderer
* ImGui + ImGuizmo integration
* Behavior system with reflection-like properties
* Ingame world editor
* Raycasting for scene interaction

## Third Party Libraries

This project uses the following open source libraries:

* GLM (MIT License)
* Dear ImGui (MIT License)
* ImGuizmo (MIT License)
* nlohmann/json (MIT License)
* Assimp (BSD-3-Clause)
* stb_image (Public Domain / MIT)
* GLFW (zlib/libpng License

See the corresponding license files in the `ThirdPartyLicenses` directory.

This project uses Vulkan® graphics API by Khronos Group.
