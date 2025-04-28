cmake_minimum_required(VERSION 3.30)
project(rocket_lander)

set(CMAKE_CXX_STANDARD 20)
set(RAYLIB "${CMAKE_CURRENT_SOURCE_DIR}/elib/raylib")
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")

include_directories(${RAYLIB} ${SRC})

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/application.cpp
        src/application.h
        src/irenderable.h
        src/renderables.cpp
        src/renderables.h
        src/iupdateable.h
        src/physicalworld.cpp
        src/physicalworld.h
        src/physicalobjects.cpp
        src/iphysicalobject.h
        src/thruster.cpp
        src/thruster.h
        src/isensor.h
        src/sensors.cpp
        src/sensors.h
        src/ipid.h
        src/pidcontrollers.cpp
        src/guidancesystem.cpp
        src/guidancesystem.h
)

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        "${RAYLIB}/libraylib.a"
        winmm
        gdi32
        opengl32
)