qt_add_executable("Ch10-drill" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch10-drill" PRIVATE PPP)
qt_finalize_executable("Ch10-drill")
