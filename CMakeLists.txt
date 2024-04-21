cmake_minimum_required(VERSION 3.21)

project(
	EldenParry
	VERSION 1.3.3
	LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(XSEPlugin)

find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")

target_include_directories(
	"${PROJECT_NAME}"
	PRIVATE
		${SIMPLEINI_INCLUDE_DIRS}
)

list(APPEND CMAKE_PREFIX_PATH "$ENV{CommonLibSSEPath}")

find_package(CommonLibSSE REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC CommonLibSSE::CommonLibSSE)
target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
			# disable warnings
			/wd5105
)