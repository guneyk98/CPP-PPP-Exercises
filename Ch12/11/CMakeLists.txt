qt_add_executable("Ch12-11" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch12-11" PRIVATE PPP)
qt_finalize_executable("Ch12-11")
