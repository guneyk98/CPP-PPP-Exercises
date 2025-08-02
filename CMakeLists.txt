cmake_minimum_required (VERSION 3.30 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if("${CMAKE_GENERATOR}" STREQUAL "Visual Studio 17 2022")
	set(CMAKE_CXX_SCAN_FOR_MODULES ON)
else()
	if(CMAKE_VERSION VERSION_GREATER_EQUAL "4.0.3")
		set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
	elseif(CMAKE_VERSION VERSION_GREATER_EQUAL "4.0.0")
		set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
	elseif(CMAKE_VERSION VERSION_GREATER_EQUAL "3.31.8")
		set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
	else()
		set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
	endif()

	set(CMAKE_CXX_MODULE_STD ON)
endif()

project ("CPP-PPP-Exercises" LANGUAGES CXX)

#for intellisense to work with Visual studio (only with Ninja generator)
if(EXISTS "${CMAKE_BINARY_DIR}/CMakeFiles/__cmake_cxx23.dir/std.ifc")
	add_compile_options(/reference "${CMAKE_BINARY_DIR}/CMakeFiles/__cmake_cxx23.dir/std.ifc")
endif()

add_subdirectory ("Ch02")
