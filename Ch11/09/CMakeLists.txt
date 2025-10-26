qt_add_executable("Ch11-09" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch11-09" PRIVATE PPP)
qt_finalize_executable("Ch11-09")
