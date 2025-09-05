add_library(chrono)
target_sources(chrono
	PUBLIC
		FILE_SET CXX_MODULES FILES
			Chrono.ixx
)
add_executable("Ch08-drill" "main.cpp")
target_link_libraries("Ch08-drill" chrono)
