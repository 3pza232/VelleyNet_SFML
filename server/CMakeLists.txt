cmake_minimum_required(VERSION 3.15)

project(server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# if(WIN32)
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
# endif()

set(LIBS_DIR ${CMAKE_SOURCE_DIR}/../libs)
set(SFML_ROOT ${LIBS_DIR}/SFML-2.6.2)
set(BOX2D_ROOT ${LIBS_DIR}/box2d)

# SFML
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system network REQUIRED)

# Box2D
set(BOX2D_LIBRARY "${BOX2D_ROOT}/libbox2d.a")
include_directories(
    ${BOX2D_ROOT}/include
    ${SFML_ROOT}/include
)

# Source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/head/*.h")

# Resource files (including config files)
file(GLOB_RECURSE RESOURCE_FILES
    "resources/*.png"
    "resources/*.jpg"
    "resources/*.jpeg"
    "resources/*.svg"
    "resources/*.mp3"
    "resources/*.wav"
    "resources/*.ogg"
    "resources/*.json"
    "resources/*.xml"
    "resources/*.ini"
    "resources/*.cfg"
    "resources/*.ttf"
    "resources/*.otf"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SFML_INCLUDE_DIR}
    src/head
    ${BOX2D_ROOT}/include
    ${SFML_ROOT}/include
)

target_link_libraries(${PROJECT_NAME} 
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-network 
    ${BOX2D_LIBRARY}
)

# Post-build: Copy all SFML DLLs and resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

file(GLOB SFML_DLLS "${SFML_ROOT}/bin/*.dll")
foreach(DLL ${SFML_DLLS})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${DLL}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endforeach()

# Copy entire resources folder (including config)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/resources"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
)

# Print build info
message(STATUS "Build output will be in: ${CMAKE_BINARY_DIR}/bin")
message(STATUS "SFML root: ${SFML_ROOT}")
message(STATUS "Box2D root: ${BOX2D_ROOT}")
message(STATUS "Found resource files:")
foreach(resource ${RESOURCE_FILES})
    message(STATUS "  ${resource}")
endforeach()
