qt_add_executable("Ch13-04" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch13-04" PRIVATE PPP)
qt_finalize_executable("Ch13-04")
