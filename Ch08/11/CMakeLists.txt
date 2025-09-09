add_library("Ch08-11-Modules")
target_sources("Ch08-11-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx
)
add_executable("Ch08-11" "main.cpp")
target_link_libraries("Ch08-11" "Ch08-11-Modules")
