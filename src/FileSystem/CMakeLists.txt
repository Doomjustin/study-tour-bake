add_library(FileSystem
  OBJECT
    ${CMAKE_SOURCE_DIR}/include/ST/FileSystem.h
    File.cpp
)

target_link_libraries(FileSystem PRIVATE fmt::fmt spdlog::spdlog)