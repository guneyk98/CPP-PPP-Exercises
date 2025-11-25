qt_add_executable("Ch14-drill" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch14-drill" PRIVATE PPP)
qt_finalize_executable("Ch14-drill")
