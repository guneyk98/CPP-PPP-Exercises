qt_add_executable("Ch11-drill" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch11-drill" PRIVATE PPP)
qt_finalize_executable("Ch11-drill")
