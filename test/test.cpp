#include <gtest/gtest.h>
#include <fstream>
#include "gmock/gmock.h"
#include "detector.hpp"
#include "tracker.hpp"


TEST(dummy_test, pass_test) { EXPECT_EQ(1, 1); }

const char CLASSLIST_PATH[] = "../../data/coco.names";
const char MODEL_PATH[] = "../../model/yolov5s.onnx";
const float YOLO_IMG_WIDTH = 640.0;
const float YOLO_IMG_HEIGHT = 640.0;
const float CONFIDENCE_THRESHOLD = 0.45;
const float NMS_THRESHOLD = 0.45;
const float SCORE_THRESHOLD = 0.5;
const int YOLO_GRID_CELLS = 25200;
const float HEIGHT = 0.762;
const float FOCAL_LENGTH = 1.898;
const float HFOV = 100.11;
const float VFOV = 56.34;
const float PIXEL_SIZE = 0.0028;
std::vector<int> RESOLUTION = {1280, 720};

/**
 * @brief 
 * 
 */
class DetectorTests : public testing::Test {
 public:
 protected:
  void SetUp() override {
    std::vector<std::string> yolo_classes;
    std::ifstream read_input(CLASSLIST_PATH);
    std::string text;
    while (read_input >> text) {
      getline(read_input, text);
      yolo_classes.push_back(text);
    }
    cv::dnn::Net yolo_model = cv::dnn::readNet(MODEL_PATH);
    testDetector = new Detector(yolo_model, YOLO_IMG_WIDTH, YOLO_IMG_HEIGHT,
                                CONFIDENCE_THRESHOLD, NMS_THRESHOLD,
                                SCORE_THRESHOLD, YOLO_GRID_CELLS, yolo_classes);
    std::cout << "Calling Fixture SetUp\n";
  };

  void TearDown() override {
    delete testDetector;
    std::cout << "Calling Fixture TearDown\n";
  };
  Detector *testDetector;
};

/**
 * @brief 
 *
 */
class TrackerTests : public testing::Test {
 public:
 protected:
  void SetUp() override {
    testTracker =
        new Tracker(HEIGHT, FOCAL_LENGTH, HFOV, VFOV, RESOLUTION, PIXEL_SIZE);
    std::cout << "Calling Fixture SetUp\n";
  };

  void TearDown() override {
    delete testTracker;
    std::cout << "Calling Fixture TearDown\n";
  };
  Tracker *testTracker;
};

/**
 * @brief 
 *
 */
TEST_F(TrackerTests, test_pixel_to_camera_frame) {
  std::vector<cv::Point> prediction_pixels = {cv::Point(0, 540),
                                              cv::Point(640, 540)};
  std::vector<std::vector<float>> test_coordinates =
      testTracker->pixel_to_camera_frame(prediction_pixels);
  ASSERT_THAT(test_coordinates[0],
              testing::ElementsAre(-2.70933342, 0.762, 2.86959529));
  ASSERT_THAT(test_coordinates[1], testing::ElementsAre(0, 0.762, 2.86959529));
}
/**
 * @brief 
 */

TEST_F(TrackerTests, test_plot_coordinates) {
  cv::Mat input_frame = cv::imread("../../test_data/tracker_input.png");
  std::vector<cv::Point> prediction_pixels = {cv::Point(0, 540),
                                              cv::Point(640, 540)};
  std::vector<std::vector<float>> test_coordinates =
      testTracker->pixel_to_camera_frame(prediction_pixels);
  cv::Mat final_frame = testTracker->plot_coordinates(
      prediction_pixels, test_coordinates, input_frame);
  cv::Mat expected_frame = cv::imread("../../test_data/tracker_gt.png");
  cv::Mat gray1, gray2;
  cv::cvtColor(final_frame, gray1, cv::COLOR_BGR2GRAY);
  cv::cvtColor(expected_frame, gray2, cv::COLOR_BGR2GRAY);
  cv::Mat diff;
  cv::imwrite("../test2.png", final_frame);
  cv::compare(gray1, gray2, diff, cv::CMP_EQ);
  int nz = cv::countNonZero(diff);
  ASSERT_GT(nz, 900000);
}

TEST_F(DetectorTests, test_detect_humans) {
  cv::Mat input_frame = cv::imread("../../test_data/detector_input.jpg");
  DetectorOutput output = testDetector->detect_humans(input_frame);
  cv::Mat expected_frame = cv::imread("../../test_data/detector_gt.png");
  cv::Mat gray1, gray2;
  cv::cvtColor(output.boxed_img, gray1, cv::COLOR_BGR2GRAY);
  cv::cvtColor(expected_frame, gray2, cv::COLOR_BGR2GRAY);
  cv::Mat diff;
  cv::imwrite("../test1.png", output.boxed_img);
  cv::compare(gray1, gray2, diff, cv::CMP_EQ);
  int nz = cv::countNonZero(diff);
  ASSERT_GT(nz, 120000);
}
