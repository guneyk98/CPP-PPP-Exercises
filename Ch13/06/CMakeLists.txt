qt_add_executable("Ch13-06" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch13-06" PRIVATE PPP)
qt_finalize_executable("Ch13-06")
