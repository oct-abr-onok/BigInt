cmake_minimum_required(VERSION 3.14)
project(lab1_BigInt)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

############

enable_testing()

add_executable(
  big_int
  big_int.cpp
  big_int.hpp
)
target_link_libraries(
  big_int
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(big_int)
