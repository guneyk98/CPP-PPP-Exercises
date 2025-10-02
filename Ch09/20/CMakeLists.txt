add_library("Ch09-20-Modules")
target_sources("Ch09-20-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			reading.ixx
)
add_executable("Ch09-20" "main.cpp")
target_link_libraries("Ch09-20" "Ch09-20-Modules")
