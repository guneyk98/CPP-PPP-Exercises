add_library("Ch08-10-Modules")
target_sources("Ch08-10-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx
)
add_executable("Ch08-10" "main.cpp")
target_link_libraries("Ch08-10" "Ch08-10-Modules")
