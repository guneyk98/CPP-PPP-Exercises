qt_add_executable("Ch10-07" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch10-07" PRIVATE PPP)
qt_finalize_executable("Ch10-07")
