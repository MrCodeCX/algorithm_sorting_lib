cmake_minimum_required(VERSION 3.16)

project(algorithm_sorting_lib
	VERSION 1.0.0
	LANGUAGES CXX
)

add_library(algorithm_sorting INTERFACE)

target_compile_features(algorithm_sorting INTERFACE cxx_std_17)
target_include_directories(algorithm_sorting
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

include(CTest)
if (BUILD_TESTING)
	add_executable(algorithm_sorting_tests tests/test.cpp)
	target_link_libraries(algorithm_sorting_tests PRIVATE algorithm_sorting)
	add_test(NAME algorithm_sorting_tests COMMAND algorithm_sorting_tests)
endif ()
