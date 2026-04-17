cmake_minimum_required(VERSION 3.20)
project(Uraken)

set(CMAKE_CXX_STANDARD 17)

# --- SFML (dinâmico) ---
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/libs/SFML")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")

# --- Box2D ---
set(BOX2D_ROOT "${CMAKE_SOURCE_DIR}/libs/box2d")
set(BOX2D_INCLUDE_DIR "${BOX2D_ROOT}/include")
set(BOX2D_LIBRARY "${BOX2D_ROOT}/build/src/libbox2d.a")

if(NOT EXISTS ${BOX2D_LIBRARY})
    message(FATAL_ERROR "Box2D library not found at ${BOX2D_LIBRARY}")
endif()

message(STATUS "Box2D Library: ${BOX2D_LIBRARY}")
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()

# --- Executável ---
add_executable(Uraken
        src/main.cpp
        src/application.cpp
        src/gamestate.cpp
        src/menustate.cpp
        src/statemachine.cpp
        src/splashscreenstate.cpp
        src/player.cpp
)

# --- Includes ---
target_include_directories(Uraken PRIVATE
        ${BOX2D_INCLUDE_DIR}
        ${SFML_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/src
)

# --- Definições ---
target_compile_definitions(Uraken PRIVATE
        B2_USE_FIXED_ALLOCATOR=1
)

# --- Link com versões dinâmicas ---
target_link_libraries(Uraken
        ${BOX2D_LIBRARY}
        ${SFML_LIBRARY_DIR}/libsfml-graphics.a
        ${SFML_LIBRARY_DIR}/libsfml-window.a
        ${SFML_LIBRARY_DIR}/libsfml-system.a
        ${SFML_LIBRARY_DIR}/libsfml-audio.a
        -lws2_32
        -lopengl32
        -lwinmm
        -lgdi32
)

# --- Copiar DLLs ---
file(GLOB SFML_DLLS "${SFML_ROOT}/bin/*.dll")
if(SFML_DLLS)
    add_custom_command(TARGET Uraken POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SFML_DLLS} $<TARGET_FILE_DIR:Uraken>
    )
endif()

message(STATUS "Configuration complete!")