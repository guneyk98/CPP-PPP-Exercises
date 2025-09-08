add_library("Ch08-05-Modules")
target_sources("Ch08-05-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx Book.ixx
)
add_executable("Ch08-05" "main.cpp")
target_link_libraries("Ch08-05" "Ch08-05-Modules")
