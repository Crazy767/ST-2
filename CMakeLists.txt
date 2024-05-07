cmake_minimum_required (VERSION 3.10.2)
project (ST-2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g")

set(tool_dest "bin")
set(lib_dest "lib")
set(include_dest "include/")

set(header_path "${PROJECT_SOURCE_DIR}/include")
set(header "${header_path}/circle.h")
set(src "${PROJECT_SOURCE_DIR}/src/circle.cpp")
set(tasks_src "${PROJECT_SOURCE_DIR}/src/tasks.cpp")

add_library(${PROJECT_NAME} SHARED
  ${header}
  ${src}
  ${tasks_src}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${header_path}
)

target_link_libraries(${PROJECT_NAME}
  pthread
)

add_executable(${PROJECT_NAME}.info src/main.cpp)
target_include_directories(${PROJECT_NAME}.info PUBLIC
  ${header_path}
)
target_link_libraries(${PROJECT_NAME}.info ${PROJECT_NAME})

add_executable(${PROJECT_NAME}.test test/AllTests.cpp test/tests.cpp)
target_include_directories(${PROJECT_NAME}.test PUBLIC
  ${header_path}
)

find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_NAME}.test ${PROJECT_NAME} GTest::GTest GTest::Main)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}.info ${PROJECT_NAME}.test
        LIBRARY DESTINATION ${lib_dest}
        RUNTIME DESTINATION ${tool_dest}
        ARCHIVE DESTINATION ${lib_dest}
        COMPONENT library)
install(FILES ${header} DESTINATION ${include_dest})
