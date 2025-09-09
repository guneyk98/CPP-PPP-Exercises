add_library("Ch08-08-Modules")
target_sources("Ch08-08-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx Book.ixx Patron.ixx
)
add_executable("Ch08-08" "main.cpp")
target_link_libraries("Ch08-08" "Ch08-08-Modules")
