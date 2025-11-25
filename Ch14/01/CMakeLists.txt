qt_add_executable("Ch14-01" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch14-01" PRIVATE PPP)
qt_finalize_executable("Ch14-01")
