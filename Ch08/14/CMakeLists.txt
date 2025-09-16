add_library("Ch08-14-Modules")
target_sources("Ch08-14-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Money.ixx
)
add_executable("Ch08-14" "main.cpp")
target_link_libraries("Ch08-14" "Ch08-14-Modules")
