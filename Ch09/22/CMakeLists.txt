add_library("Ch09-22-Modules")
target_sources("Ch09-22-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			roman.ixx
)
add_executable("Ch09-22" "main.cpp")
target_link_libraries("Ch09-22" "Ch09-22-Modules")
