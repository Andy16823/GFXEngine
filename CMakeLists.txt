# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 3.10)

# Aktivieren Sie Hot Reload für MSVC-Compiler, sofern unterstützt.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GFXEngine")

include(FetchContent)

# LibGFX von GitHub laden
FetchContent_Declare(
    LibGFX
    GIT_REPOSITORY https://github.com/Andy16823/LibGFX.git
    GIT_TAG master
)

FetchContent_Declare(
    GLM
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master
)

# stb (stb_image) als Header-only Bibliothek hinzufügen
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
# Nur die Quellen herunterladen/auspacken (kein add_subdirectory, da kein CMake-Projekt vorhanden)
FetchContent_Populate(stb)
# Erstelle ein INTERFACE-Target, damit andere Targets es mit target_link_libraries verwenden können
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_SOURCE_DIR})

# LibGFX und GLM verfügbar machen
FetchContent_MakeAvailable(LibGFX GLM)

# Schließen Sie Unterprojekte ein.
add_subdirectory ("GFXEngine")
