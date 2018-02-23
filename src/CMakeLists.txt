set(GLUT_INCLUDE_DIR "C:/includes")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(project2 ${SOURCES})

include_directories( 
	${OPENGL_INCLUDE_DIRS} 
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command(TARGET project2 POST_BUILD        # Adds a post-build event to project2
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/lib/libstdc++-6.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:project2>)                 # <--this is out-file path

add_custom_command(TARGET project2 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/lib $<TARGET_FILE_DIR:project2>)

target_link_libraries(project2 ${OPENGL_LIBRARIES} freeglut.a)
