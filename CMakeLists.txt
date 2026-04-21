cmake_minimum_required(VERSION 3.20)
project(AlgorithmVisualizer VERSION 1.0 LANGUAGES CXX)

# =========================
# C++ CONFIG
# =========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =========================
# QT CONFIG
# =========================
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# ── Include paths ─────────────────────────────────────────
include_directories(include)

# =========================
# ENGINE (PURE C++ — no Qt)
# =========================
add_library(engine STATIC
    src/engine/BubbleSortEngine.cpp
)

target_include_directories(engine PUBLIC include)
set_target_properties(engine PROPERTIES AUTOMOC OFF)

# =========================
# QT APPLICATION
# =========================
qt_add_executable(AlgorithmVisualizer
    src/main.cpp
    src/ui/MainWindow.cpp
    src/ui/SortingWidget.cpp
    src/utils/Logger.cpp
    include/ui/MainWindow.h       # ← required for AUTOMOC
    include/ui/SortingWidget.h    # ← required for AUTOMOC
)

target_include_directories(AlgorithmVisualizer PRIVATE include)

target_link_libraries(AlgorithmVisualizer
    PRIVATE Qt6::Widgets engine
)

# =========================
# WINDOWS: copy Qt DLLs next to .exe
# =========================
if(WIN32)
    add_custom_command(TARGET AlgorithmVisualizer POST_BUILD
        COMMAND "${Qt6_DIR}/../../../bin/windeployqt.exe"
                --debug
                "$<TARGET_FILE:AlgorithmVisualizer>"
        COMMENT "Deploying Qt DLLs..."
    )
endif()