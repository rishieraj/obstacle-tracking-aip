find_package(OpenCV REQUIRED)

add_library(DetectorLib SHARED detector.cpp)
target_include_directories(DetectorLib PUBLIC 
${OpenCV_INCLUDE_DIRS}
.)

target_link_libraries(DetectorLib
${OpenCV_LIBS}
)