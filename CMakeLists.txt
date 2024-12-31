cmake_minimum_required(VERSION 3.20)
project(DynamicDNS
  VERSION 1.0.0
  DESCRIPTION "Dynamic DNS Updater"
  LANGUAGES CXX
)

set(CORE_LIB ${PROJECT_NAME}_core_lib)
set(EXECUTABLE ${PROJECT_NAME}_exec)
set(TESTS_EXECUTABLE ${PROJECT_NAME}_tests_exec)

include(FetchContent)

FetchContent_Declare(cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG dec9422db3af470641f8b0d90e4b451c4daebf64
)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG 9cca280a4d0ccf0c08f47a99aa71d1b0e52f8d03
)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG b514bdc898e2951020cbdca1304b75f5950d1f59
)

FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Werror)
enable_testing()

add_library(${CORE_LIB})
add_executable(${EXECUTABLE})

target_include_directories(${CORE_LIB}
  PUBLIC
    ${CMAKE_SOURCE_DIR}
)

add_subdirectory(src)

target_link_libraries(${CORE_LIB}
  PRIVATE
    cpr::cpr
  PUBLIC
    nlohmann_json::nlohmann_json
)

target_link_libraries(${EXECUTABLE}
  PRIVATE
    ${CORE_LIB}
)

add_executable(${TESTS_EXECUTABLE})

target_include_directories(${TESTS_EXECUTABLE}
  PUBLIC
    ${CMAKE_SOURCE_DIR}
)

add_subdirectory(tests)

target_link_libraries(${TESTS_EXECUTABLE}
  PRIVATE
    ${CORE_LIB}
    GTest::gtest
    GTest::gtest_main
    nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(${TESTS_EXECUTABLE})
