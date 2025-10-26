qt_add_executable("Ch11-11" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch11-11" PRIVATE PPP)
qt_finalize_executable("Ch11-11")
