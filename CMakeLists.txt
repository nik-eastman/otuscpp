cmake_minimum_required(VERSION 3.14.0)
project(ip_filter VERSION 0.0.1)

# ip library
add_library(ip_lib ip_address.cpp)

# testing support
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_executable(test_ip test_ip.cpp)
target_link_libraries(test_ip
    gtest_main
    ip_lib
)

enable_testing()
add_test(NAME test_ip COMMAND test_ip)

# main application
add_executable(ip_filter ip_filter.cpp ip_address.h)
target_link_libraries(ip_filter PRIVATE
    ip_lib
)

set_target_properties(test_ip ip_filter
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)