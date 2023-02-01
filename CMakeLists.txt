cmake_minimum_required(VERSION 3.14)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VESRION})

#fetch exact version of googletest sources
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
FetchContent_MakeAvailable(googletest)

# version lib 
configure_file(version.h.in version.h)
add_library(version_lib lib.cpp)

add_executable(helloworld_cli main.cpp)
target_include_directories(version_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    version_lib
)

# testing support
add_executable(test_version test_version.cpp)
target_link_libraries(test_version
    gtest_main
    version_lib
)
enable_testing()
add_test(NAME test_version COMMAND test_version)

set_target_properties(helloworld_cli version_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# pack to deb-package support 
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

