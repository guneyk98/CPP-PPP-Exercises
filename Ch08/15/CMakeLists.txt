add_library("Ch08-15-Modules")
target_sources("Ch08-15-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Money.ixx
)
add_executable("Ch08-15" "main.cpp")
target_link_libraries("Ch08-15" "Ch08-15-Modules")
