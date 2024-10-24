# Obstacle Detection and Tracking for Warehouse Robots

## Phase-1

[![CICD Workflow status](https://github.com/rishieraj/obstacle-tracking-aip/actions/workflows/test.yml/badge.svg)](https://github.com/rishieraj/obstacle-tracking-aip/actions/workflows/test.yml) [![codecov](https://codecov.io/gh/rishieraj/obstacle-tracking-aip/branch/main/graph/badge.svg)](https://codecov.io/gh/rishieraj/obstacle-tracking-aip) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

### Project Summary
We are designing a human obstacle detection and tracking system for Acme’s warehouse robot, aimed at improving safety and efficiency in material handling operations. This system is vital in environments where human workers coexist with robots, ensuring that the robot can detect and track multiple humans within its operational range and adjust its path accordingly.

The system will use a monocular video camera to detect and track human presence, outputting positional information directly in the robot’s reference frame. This will allow the robot to navigate effectively and safely while avoiding potential collisions with workers. An object detection and tracking system is critical for modern robots as they often need to operate in crowded environments. A robust perception system helps the robots to plan a path avoiding obstacles. This
particular module is built in a self-contained manner such that it can be integrated directly into any robot system as a package and run as part of the whole system. The software module designed by us will be used in the Acme warehouse robot for safe navigation on the shop-floor for which it requires detection and tracking of human obstacles.

### Personnel Info
The authors of this Perception project are Rishie Raj and Uthappa Madettira, both graduate students in Robotics at the University of Maryland, College Park.

### AIP Workflow
This project was developed using the Agile Development Process (AIP) along with pair programming (with a driver and navigator), with a focus on test-driven development (TDD). The product backlog details have been linked below for Iteration-1. The link to the sprint meeting discussions for this sprint have also been linked below.

 - [Product Backlog](https://docs.google.com/spreadsheets/d/1qtcS4uq2FjSLTZ0jtuV0sKn7PudzRwPuLhG2PHGJw3E/edit?usp=drive_link)
 - [Sprint Meeting Plan and Review](https://docs.google.com/document/d/1mYu_vcO9rMNK6TtyyJi_NpTCQDjfDIR6bn9rOT_iLjo/edit?usp=sharing)

The latest (Phase 1) developed UML class and activity diagrams can be found in the `UML/revised` directory. The earlier devised UML diagrams as a part of Phase 0 are available in the `UML/initial` directory. 

A short video providing a brief overview of the project and the details explaining the AIP process used is embedded below. A direct link to the same can also be found [here](https://drive.google.com/file/d/1eOC-K-yg1N1fbtuiCu27ZhuwCuoyBkLL/view?usp=drive_link).

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
