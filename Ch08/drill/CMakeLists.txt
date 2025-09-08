add_library("Ch08-drill-Modules")
target_sources("Ch08-drill-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx
)
add_executable("Ch08-drill" "main.cpp")
target_link_libraries("Ch08-drill" "Ch08-drill-Modules")
