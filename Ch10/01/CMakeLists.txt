qt_add_executable("Ch10-01" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch10-01" PRIVATE PPP)
qt_finalize_executable("Ch10-01")
