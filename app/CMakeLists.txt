# Any C++ source files needed to build this target (shell-app).
add_executable(perception-app
  # list of source cpp files:
  main.cpp
  )

find_package(OpenCV REQUIRED)

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(perception-app PUBLIC
  # list inclue directories:
  ${OpenCV_INCLUDE_DIRS}
  .)

# Any dependent libraires needed to build this target.
target_link_libraries(perception-app PUBLIC
  # list of libraries
  DetectorLib
  ${OpenCV_LIBS}
  )
  