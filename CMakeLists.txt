cmake_minimum_required(VERSION 3.20)
project(SFML_RPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH
        /opt/homebrew/opt/sfml
        /usr/local/opt/sfml
    )
endif()

find_package(SFML 3.0.2 COMPONENTS Graphics Audio Window System)

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

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

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

if(APPLE)
    set(SFML_ROOT "/opt/homebrew/opt/sfml")
    if(NOT EXISTS ${SFML_ROOT})
        set(SFML_ROOT "/usr/local/opt/sfml")
    endif()
    set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
    set(SFML_LIB_DIR "${SFML_ROOT}/lib")

    target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

    target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_LIB_DIR})

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        sfml-graphics
        sfml-audio
        sfml-window
        sfml-system
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_RPATH "${SFML_LIB_DIR}"
        INSTALL_RPATH "${SFML_LIB_DIR}"
    )
else()
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        sfml-graphics
        sfml-audio
        sfml-window
        sfml-system
    )
endif()

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD

message(STATUS "SFML found in: ${SFML_DIR}")
message(STATUS "SFML include: ${SFML_INCLUDE_DIR}")
message(STATUS "CMake prefix path: ${CMAKE_PREFIX_PATH}")
