#include <fstream>
#include <iostream>
#include <string>

#include "detector.hpp"
#include "tracker.hpp"


const char CLASSLIST_PATH[] = "./data/coco.names";
const char MODEL_PATH[] = "./model/yolov5s.onnx";
const float YOLO_IMG_WIDTH = 640.0;
const float YOLO_IMG_HEIGHT = 640.0;
const float CONFIDENCE_THRESHOLD = 0.45;
const float NMS_THRESHOLD = 0.45;
const float SCORE_THRESHOLD = 0.5;
const int YOLO_GRID_CELLS = 25200;


float HEIGHT = 0.762;
const float FOCAL_LENGTH = 1.898;
const float HFOV = 100.11;
const float VFOV = 56.34;
const float PIXEL_SIZE = 0.0028;
std::vector<int> RESOLUTION = {1280, 720};

int main(int argc, char* argv[]) {
  // Use command line arguments to initialise camera and height
  std::string capture_device = argv[1];
  // Initialise Detector
  std::vector<std::string> yolo_classes;
  std::ifstream read_input(CLASSLIST_PATH);
  std::string text;
  while (read_input >> text) {
    getline(read_input, text);
    yolo_classes.push_back(text);
  }
  cv::dnn::Net yolo_model = cv::dnn::readNet(MODEL_PATH);
  Detector detector(yolo_model, YOLO_IMG_WIDTH, YOLO_IMG_HEIGHT,
                    CONFIDENCE_THRESHOLD, NMS_THRESHOLD, SCORE_THRESHOLD,
                    YOLO_GRID_CELLS, yolo_classes);
  // Initialise Camera
  cv::VideoCapture cap(capture_device);
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
  if (!cap.isOpened()) {
    std::cout << "Error opening video stream or file" << std::endl;
    return -1;
  }

  Tracker* human_tracker =
      new Tracker(HEIGHT, FOCAL_LENGTH, HFOV, VFOV, RESOLUTION, PIXEL_SIZE);

  while (1) {
    cv::Mat frame;
    cap >> frame;
    // If the frame is empty, break immediately
    if (frame.empty()) break;

    DetectorOutput output = detector.detect_humans(frame);
    // Detector method comes here to populate prediction pixels
    std::vector<cv::Point> prediction_pixels = output.pixels;
    // Calling tracker method for coordinates in camera frame
    std::vector<std::vector<float>> coordinates =
        human_tracker->pixel_to_camera_frame(prediction_pixels);
    // Plot coordinates on frame
    cv::Mat final_frame = human_tracker->plot_coordinates(
        prediction_pixels, coordinates, output.boxed_img);
    // Display the frame
    cv::imshow("Frame", output.boxed_img);
    char c = static_cast<char>(cv::waitKey(25));
    if (c == 27) break;
  }
  // Close capture object
  cap.release();
  // Closes all the frames
  cv::destroyAllWindows();
  return 0;
}
