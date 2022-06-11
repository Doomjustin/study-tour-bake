add_library(System
  OBJECT
    ${CMAKE_SOURCE_DIR}/include/ST/System.h
    UserInfo.cpp
    GroupInfo.cpp
    SystemInfo.cpp
    Environment.cpp
)