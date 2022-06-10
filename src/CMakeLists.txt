add_subdirectory(FileSystem)

add_library(ST)

target_link_libraries(ST PRIVATE FileSystem)