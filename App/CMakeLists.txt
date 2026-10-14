add_executable(PolyApp main.cpp)
target_link_libraries(PolyApp PRIVATE PolyUtils)

# DLL має лежати поруч з exe (для SHARED)
add_custom_command(TARGET PolyApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:PolyUtils> $<TARGET_FILE_DIR:PolyApp>)