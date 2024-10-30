# Any C++ source files needed to build this target (cpp-test).
add_executable(perception-test
  # list of source cpp files:
  main.cpp
  test.cpp
  )

# Any dependent libraires needed to build this target.
target_link_libraries(perception-test PUBLIC
  # list of libraries:
  gtest
  gmock
  DetectorLib
  TrackerLib
  )

# Enable CMake’s test runner to discover the tests included in the
# binary, using the GoogleTest CMake module.
gtest_discover_tests(perception-test)