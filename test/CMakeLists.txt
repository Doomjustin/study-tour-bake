add_executable(test-third-parties test_third_parties.cpp)
target_link_libraries(test-third-parties PRIVATE spdlog::spdlog fmt::fmt Boost::regex)

add_executable(test-catch2 test_catch2.cpp)
target_link_libraries(test-catch2 PRIVATE Catch2::Catch2WithMain)

add_executable(test-filesystem test_filesystem.cpp)
target_link_libraries(test-filesystem PRIVATE ST spdlog::spdlog)

# list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
# include(CTest)
# include(Catch)
# catch_discover_tests(test-catch2)