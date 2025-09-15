add_library("Ch08-13-Modules")
target_sources("Ch08-13-Modules"
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Rational.ixx
)
add_executable("Ch08-13" "main.cpp")
target_link_libraries("Ch08-13" "Ch08-13-Modules")
