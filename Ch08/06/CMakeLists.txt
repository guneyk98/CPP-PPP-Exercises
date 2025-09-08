add_library("Ch08-06-Modules")
target_sources("Ch08-06-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx Book.ixx
)
add_executable("Ch08-06" "main.cpp")
target_link_libraries("Ch08-06" "Ch08-06-Modules")
