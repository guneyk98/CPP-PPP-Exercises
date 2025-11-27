qt_add_executable("Ch14-02" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch14-02" PRIVATE PPP)
qt_finalize_executable("Ch14-02")
