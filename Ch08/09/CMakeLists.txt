add_library("Ch08-09-Modules")
target_sources("Ch08-09-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx Book.ixx Patron.ixx Library.ixx
)
add_executable("Ch08-09" "main.cpp")
target_link_libraries("Ch08-09" "Ch08-09-Modules")
