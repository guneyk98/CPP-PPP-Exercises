qt_add_executable("Ch10-04" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch10-04" PRIVATE PPP)
qt_finalize_executable("Ch10-04")
