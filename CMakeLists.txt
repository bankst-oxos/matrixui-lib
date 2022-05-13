cmake_minimum_required(VERSION 3.18)

project(matrixui-lib VERSION 0.0.1 DESCRIPTION "ImGui based GUI framework built around a widget concept")

# Generate compile_commands.json for clangd
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Download, build, and include imgui
include(${CMAKE_CURRENT_LIST_DIR}/cmake/imgui/CMakeLists.txt)

# library
set(COMMON_SOURCES
	src/ImGuiApp.cpp
	src/ImGuiWidget.cpp
	src/MatrixPlot.cpp
	src/widget/MatrixDebugWidget.cpp
	src/widget/OpenCVMatWidget.cpp
)

set(COMMON_INC
	inc/ImGuiApp.h
	inc/ImGuiWidget.h
	inc/MatrixPlot.h
	inc/widget/MatrixDebugWidget.h
	inc/widget/OpenCVMatWidget.h
	inc/widget/OpenGLCanvasWidget.h
)

# TODO: make an install prefix option?
set(MATRIXUI_INSTALL_LIBDIR /usr/local/lib)
set(MATRIXUI_INSTALL_INCLUDEDIR /usr/local/include)

FIND_PACKAGE(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

add_library(${PROJECT_NAME} SHARED
	${COMMON_SOURCES}
	${COMMON_INC}
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${COMMON_INC}")

target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/widget/>
	$<INSTALL_INTERFACE:${include_dest}/${PROJECT_NAME}>
)

install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${MATRIXUI_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${MATRIXUI_INSTALL_INCLUDEDIR}/matrixui-lib
)

# Optional actions such as compile features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME}
	${OpenCV_LIBS}
	imgui
	-lGL
	glfw
)