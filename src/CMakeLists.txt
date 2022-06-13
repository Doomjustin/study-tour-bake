add_subdirectory(FileSystem)
add_subdirectory(System)

add_library(ST
  STATIC
    ${PROJECT_SOURCE_DIR}/include/ST/Process.h
    ${PROJECT_SOURCE_DIR}/include/ST/APUE.h
    Process.cpp
    APUE.cpp
)

target_link_libraries(ST PRIVATE FileSystem System)