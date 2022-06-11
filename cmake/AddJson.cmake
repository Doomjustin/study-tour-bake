include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(addFetchContentMakeAvailable.cmake)
endif()

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY    git@github.com:nlohmann/json.git # 指定git仓库地址
  GIT_TAG           v3.10.5 # 指定版本
  SOURCE_DIR        ${CMAKE_SOURCE_DIR}/third_parties/json   # 源码下载到此目录下
)

FetchContent_MakeAvailable(nlohmann_json)