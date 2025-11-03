qt_add_executable("Ch12-04" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch12-04" PRIVATE PPP)
qt_finalize_executable("Ch12-04")
