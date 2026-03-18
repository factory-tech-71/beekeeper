cmake_minimum_required(VERSION 3.20)
project(Pchelovod LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Quick QuickControls2 Location Positioning Core Gui)
find_package(MAVSDK REQUIRED)

# HailoRT — предполагается, что установлен глобально
# Если нужно явно указать:
# include_directories(/opt/hailo/include)
# link_directories(/opt/hailo/lib)

add_executable(Pchelovod
    main.cpp
    src/core/SwarmManager.cpp
    src/core/HailoInference.cpp
    src/gui/MainWindow.cpp
)

target_include_directories(Pchelovod PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
)

target_link_libraries(Pchelovod PRIVATE
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Location
    Qt6::Positioning
    MAVSDK::mavsdk
    # HailoRT — пример:
    # hailort
    # opencv_core opencv_imgproc opencv_videoio   # если используешь OpenCV для кадров
)

# Для QML-файлов (если хочешь использовать qrc)
# qt_add_resources(Pchelovod "resources"
#     PREFIX "/qml"
#     FILES src/gui/MapView.qml
# )
qt_add_resources(RESOURCES resources/resources.qrc)
target_sources(Pchelovod PRIVATE ${RESOURCES})