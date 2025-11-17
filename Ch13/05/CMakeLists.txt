qt_add_executable("Ch13-05" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch13-05" PRIVATE PPP)
qt_finalize_executable("Ch13-05")
