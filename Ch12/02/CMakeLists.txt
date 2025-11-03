qt_add_executable("Ch12-02" MANUAL_FINALIZATION "main.cpp")
target_link_libraries("Ch12-02" PRIVATE PPP)
qt_finalize_executable("Ch12-02")
