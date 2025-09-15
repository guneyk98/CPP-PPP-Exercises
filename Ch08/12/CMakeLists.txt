add_library("Ch08-12-Modules")
target_sources("Ch08-12-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx
)
add_executable("Ch08-12" "main.cpp")
target_link_libraries("Ch08-12" "Ch08-12-Modules")
