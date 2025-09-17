add_library("Ch08-16-Modules")
target_sources("Ch08-16-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Money.ixx
)
add_executable("Ch08-16" "main.cpp")
target_link_libraries("Ch08-16" "Ch08-16-Modules")
