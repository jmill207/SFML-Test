cmake_minimum_required(VERSION 3.20)
project(SFML_RPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -------------------------------------------------------------------
# Step 1: Locate SFML
# -------------------------------------------------------------------
if(APPLE)
    # Homebrew default install paths
    list(APPEND CMAKE_PREFIX_PATH
        /opt/homebrew/opt/sfml
        /usr/local/opt/sfml
    )
endif()

find_package(SFML 3.0.2 COMPONENTS Graphics Audio Window System)

# -------------------------------------------------------------------
# Step 2: Fetch SFML if not found
# -------------------------------------------------------------------
if(NOT SFML_FOUND)
    message(WARNING "SFML 3.0.2 not found locally — fetching from GitHub...")

    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
    )
    FetchContent_MakeAvailable(SFML)
endif()

# -------------------------------------------------------------------
# Step 3: Fetch nlohmann/json
# -------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

# -------------------------------------------------------------------
# Step 4: Collect source files
# -------------------------------------------------------------------
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
list(FILTER ALL_SOURCES EXCLUDE REGEX "src/jsonTest.cpp$")

add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${HEADERS})

# -------------------------------------------------------------------
# Step 5: Include directories
# -------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE include)

# -------------------------------------------------------------------
# Step 6: Link SFML and JSON
# -------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics
    SFML::Audio
    SFML::Window
    SFML::System
    nlohmann_json::nlohmann_json
)

# macOS runtime path for SFML dylibs
if(APPLE)
    if(DEFINED SFML_DIR)
        get_target_property(SFML_LIB_DIR SFML::Graphics LOCATION)
        get_filename_component(SFML_LIB_DIR "${SFML_LIB_DIR}" DIRECTORY)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            BUILD_RPATH "${SFML_LIB_DIR}"
            INSTALL_RPATH "${SFML_LIB_DIR}"
        )
    endif()
endif()

# -------------------------------------------------------------------
# Step 7: Optional JSON test executable
# -------------------------------------------------------------------
add_executable(jsonTest src/jsonTest.cpp)
target_link_libraries(jsonTest PRIVATE nlohmann_json::nlohmann_json)

# -------------------------------------------------------------------
# Step 8: Debug info
# -------------------------------------------------------------------
message(STATUS "SFML found in: ${SFML_DIR}")
message(STATUS "CMake prefix path: ${CMAKE_PREFIX_PATH}")
