cmake_minimum_required(VERSION 3.16)

project(shield)

# =========================================================
# C++ standard
# =========================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================================================
# Find Geant4
# =========================================================
find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

# =========================================================
# Include directories
# =========================================================
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# =========================================================
# Source files (.cc ONLY)
# =========================================================
file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cc
)

# =========================================================
# Executable
# =========================================================
add_executable(cam
    muon.cc
    ${SOURCES}
)

target_link_libraries(cam
    ${Geant4_LIBRARIES}
)

# =========================================================
# Copy macro files
# =========================================================
file(GLOB MACRO_FILES ${PROJECT_SOURCE_DIR}/macros/*.mac)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

message(STATUS "Geant4 version: ${Geant4_VERSION}")
message(STATUS "Project shielding configured successfully")
