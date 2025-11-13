cmake_minimum_required(VERSION 3.20)
project(SFML_RPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -------------------------------------------------------------------
# Step 1. Try to locate SFML via system or package manager
# -------------------------------------------------------------------

if(APPLE)
    # Try Homebrew default install paths (Apple Silicon & Intel)
    list(APPEND CMAKE_PREFIX_PATH
        /opt/homebrew/opt/sfml
        /usr/local/opt/sfml
    )
endif()

find_package(SFML 3.0.2 COMPONENTS Graphics Audio Window System)

# -------------------------------------------------------------------
# Step 2. If not found, fetch SFML from GitHub automatically
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
# Step 3. Collect source files
# -------------------------------------------------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# -------------------------------------------------------------------
# Step 4. Include directories
# -------------------------------------------------------------------
target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

# Add explicit include paths for Homebrew SFML (macOS only)
if(APPLE)
    set(SFML_ROOT "/opt/homebrew/opt/sfml")
    if(NOT EXISTS ${SFML_ROOT})
        set(SFML_ROOT "/usr/local/opt/sfml")
    endif()
    set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
    set(SFML_LIB_DIR "${SFML_ROOT}/lib")

    target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})
    link_directories(${SFML_LIB_DIR})
endif()

# -------------------------------------------------------------------
# Step 5. Link SFML
# -------------------------------------------------------------------
if(APPLE)
    set(SFML_ROOT "/opt/homebrew/opt/sfml")
    if(NOT EXISTS ${SFML_ROOT})
        set(SFML_ROOT "/usr/local/opt/sfml")
    endif()
    set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
    set(SFML_LIB_DIR "${SFML_ROOT}/lib")

    target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

    # Explicitly link libraries by full path
    target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_LIB_DIR})

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        sfml-graphics
        sfml-audio
        sfml-window
        sfml-system
    )

    # Tell macOS where to find the dylibs at runtime
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_RPATH "${SFML_LIB_DIR}"
        INSTALL_RPATH "${SFML_LIB_DIR}"
    )
else()
    # Other platforms (Windows/Linux)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        sfml-graphics
        sfml-audio
        sfml-window
        sfml-system
    )
endif()

# -------------------------------------------------------------------
# Step 6. Copy assets (temporarily disabled)
# -------------------------------------------------------------------
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
#     COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DI


# -------------------------------------------------------------------
# Step 7. Debug info
# -------------------------------------------------------------------
message(STATUS "SFML found in: ${SFML_DIR}")
message(STATUS "SFML include: ${SFML_INCLUDE_DIR}")
message(STATUS "CMake prefix path: ${CMAKE_PREFIX_PATH}")
