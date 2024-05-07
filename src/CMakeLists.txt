set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(header ${header_path}/circle.h)
set(src circle.cpp)
set(tasks_src "${${PROJECT_NAME}_SOURCE_DIR}/src/tasks.cpp")

add_library(${PROJECT_NAME} SHARED
  ${header}
  ${src}
  ${tasks_src})
  
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}
  pthread)

add_executable(${PROJECT_NAME}.info main.cpp)
target_include_directories(${PROJECT_NAME}.info
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}.info
  ${PROJECT_NAME})

add_executable(${PROJECT_NAME}.test test/AllTests.cpp test/tests.cpp)
target_include_directories(${PROJECT_NAME}.test
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${header_path}
)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION "${lib_dest}"
    ARCHIVE DESTINATION "${lib_dest}"
    COMPONENT library)
install(TARGETS ${PROJECT_NAME}.info
        RUNTIME DESTINATION "${tool_dest}"
    COMPONENT library)
install(FILES ${header} DESTINATION "${include_dest}")
