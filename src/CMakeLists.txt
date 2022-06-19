add_subdirectory(FileSystem)
add_subdirectory(Net)

add_library(ST
  STATIC
    ${PROJECT_SOURCE_DIR}/include/ST/Process.h
    ${PROJECT_SOURCE_DIR}/include/ST/Exercise.h
    ${PROJECT_SOURCE_DIR}/include/ST/TypeTraits.h
    ${PROJECT_SOURCE_DIR}/include/ST/Global.h
    ${PROJECT_SOURCE_DIR}/include/ST/Cast.h
    ${PROJECT_SOURCE_DIR}/include/ST/Singleton.h
    ${PROJECT_SOURCE_DIR}/include/ST/Exception.h
    ${PROJECT_SOURCE_DIR}/include/ST/Signal.h
    Process.cpp
    Exercise.cpp
    Global.cpp
    Signal.cpp
)

target_link_libraries(ST PUBLIC FileSystem Net)