add_library("Ch08-07-Modules")
target_sources("Ch08-07-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx Book.ixx
)
add_executable("Ch08-07" "main.cpp")
target_link_libraries("Ch08-07" "Ch08-07-Modules")
