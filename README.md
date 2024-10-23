# Obstacle Detection and Tracking for Warehouse Robots

## Phase-1

[![CICD Workflow status](https://github.com/Uthappa13/obstacle-tracking-aip/actions/workflows/test.yml/badge.svg)](https://github.com/Uthappa13/obstacle-tracking-aip/actions/workflows/test.yml) [![codecov](https://codecov.io/gh/Uthappa13/obstacle-tracking-aip/branch/main/graph/badge.svg)](https://codecov.io/gh/Uthappa13/obstacle-tracking-aip) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

### Installing Dependencies
To install the dependencies for this project (ONNX and OpenCV), simply run the command below on an Ubuntu system (confirmed to work on Ubuntu 22.04).
```sh
# Install OpenCV with root privileges:
  sudo apt install libopencv-dev
```

### Building the Code

Before running any component of the Obstacle Detection and Tracking module, make sure you are in the main working directory.
To build the project, execute the following commands.
```sh
# Create all the make files:
  cmake -S ./ -B build/
# Compile and build the code to the 'build' directory from scratch:
  cmake --build build/ --clean-first
# Clean the 'build' directory:
  cmake --build build/ --target clean
# Remove the 'build' directory to rebuild the project if necessary:
  rm -rf build/
```

### Generating Documentation

To generate and view the Doxygen documentation of the project, run the following commands.
```sh
# Build the documentation into the 'docs' directory using CMake:
  cmake --build build/ --target docs
# Open the documentation as a HTML file in your web browser:
  open docs/html/index.html
```

### Running the Program Executables

To try a demo of the Obstacle Detection and Tracking module on your system's webcam, execute the following commands.
``` bash
# Execute the 'app/main.cpp' file to see a demo run of HDAL on your system's webcam:
  ./build/app/perception-app /dev/video0
```

### Running Unit Tests

To manually run and verify the working of the unit tests for HDAL, execute the commands below.
``` bash
# Manually run the unit tests:
  ctest --test-dir build/
```

### Building for Test Coverage

This section shows how to configure the code to enable code coverage. Note that this information can also be viewed in the code coverage report which can be accessed by clicking the *codecov* badge at the top of this file. Otherwise, you can build the report manually and view the HTML file in a web browser by running the commands below.
```bash
# If you don't have gcovr or lcov installed, run:
  sudo apt-get install gcovr lcov
# Set the build type to Debug and WANT_COVERAGE=ON:
  cmake -D WANT_COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug -S ./ -B build/
# Do a clean compile, run unit test, and generate the coverage report:
  cmake --build build/ --clean-first --target all test_coverage
# Open a web browser to browse the test coverage report:
  open build/test_coverage/index.html
```
Running these commands generates an `index.html` page in the `build/test_coverage` sub-directory that can be viewed on a local web browser.

You can also get a code coverage report for the *shell-app* target, instead of the unit tests. To do so, repeat the previous two steps, but with the *app_coverage* target:
``` bash
# Do another clean compile, run shell-app, and generate its coverage report:
  cmake --build build/ --clean-first --target all app_coverage
# Open a web browser to browse the test coverage report:
  open build/app_coverage/index.html
```
This generates an `index.html` page in the `build/app_coverage` sub-directory that can be viewed locally in a web browser.


### Google Coding Style Verification
To check how the written code conforms to the Google C++ style guide, look at the `results/cpplint_report.txt` file to see the output on using the *Cpplint* tool on this project. You should not be able to see any issues or problems, with all the files processed successfully.

This can be self-verified as well by running the following command in the highest-level directory of the project.
```sh
# Install Cpplint(ignore if already installed):
  sudo apt install cpplint
# Self-check Google code style conformity using Cpplint:
  cpplint --filter="-legal/copyright" $( find . -name *.cpp | grep -vE -e "^./build/" )
```

On running the above command, you should see the same output in the `results/cpplint_report.txt` file.

In the proposal phase, we have designed the software plan along with the following elements of software design:  

 1. [Software Plan](https://drive.google.com/file/d/1jGiiobS3-BFS2GZKp7tRJ7s5Mr_CgpAN/view?usp=drive_link)
 2. [Product Backlog](https://docs.google.com/spreadsheets/d/1E_nRD0vp5bYWbiwfghffEHXf7bQaf3OA0RdkEj6O_uE/edit?usp=drive_link)
 3. [UML Diagrams and Quad Chart](diagram)
 4. [Video Proposal](https://drive.google.com/file/d/1RA5c2WGzY5DniITtkwL4w4C65WinjcHl/view?usp=drive_link)
