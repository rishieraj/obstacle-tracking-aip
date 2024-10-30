find_package(OpenCV REQUIRED)

add_library(TrackerLib SHARED tracker.cpp)
target_include_directories(TrackerLib PUBLIC 
${OpenCV_INCLUDE_DIRS}
.)

target_link_libraries(TrackerLib
${OpenCV_LIBS}
)