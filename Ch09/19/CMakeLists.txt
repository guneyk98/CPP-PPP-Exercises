add_library("Ch09-19-Modules")
target_sources("Ch09-19-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			reading.ixx
)
add_executable("Ch09-19-1" "store_temps.cpp")
add_executable("Ch09-19-2" "temp_stats.cpp")
target_link_libraries("Ch09-19-1" "Ch09-19-Modules")
target_link_libraries("Ch09-19-2" "Ch09-19-Modules")
