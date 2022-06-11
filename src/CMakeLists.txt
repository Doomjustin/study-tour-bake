add_subdirectory(FileSystem)
add_subdirectory(System)

add_library(ST
  STATIC
    ${CMAKE_SOURCE_DIR}/include/ST/Process.h
    Process.cpp
)

target_link_libraries(ST PRIVATE FileSystem System)