add_subdirectory(core)

target_sources(${EXECUTABLE}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
