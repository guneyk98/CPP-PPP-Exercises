qt_add_executable("Ch11-06" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch11-06" PRIVATE PPP)
qt_finalize_executable("Ch11-06")
