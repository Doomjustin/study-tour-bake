add_subdirectory(FileSystem)
add_subdirectory(Net)

add_library(ST
  STATIC
    ${PROJECT_SOURCE_DIR}/include/ST/Process.h
    ${PROJECT_SOURCE_DIR}/include/ST/APUE.h
    ${PROJECT_SOURCE_DIR}/include/ST/TypeTraits.h
    ${PROJECT_SOURCE_DIR}/include/ST/Global.h
    ${PROJECT_SOURCE_DIR}/include/ST/Exception.h
    Process.cpp
    APUE.cpp
    Global.cpp
)

target_link_libraries(ST PUBLIC FileSystem Net)