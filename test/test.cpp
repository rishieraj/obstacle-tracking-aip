#include <gtest/gtest.h>

#include <fstream>

#include "detector.hpp"

TEST(dummy_test, pass_test) { EXPECT_EQ(1, 1); }

const char CLASSLIST_PATH[] = "../../data/coco.names";
const char MODEL_PATH[] = "../../model/yolov5s.onnx";
const float YOLO_IMG_WIDTH = 640.0;
const float YOLO_IMG_HEIGHT = 640.0;
const float CONFIDENCE_THRESHOLD = 0.45;
const float NMS_THRESHOLD = 0.45;
const float SCORE_THRESHOLD = 0.5;
const int YOLO_GRID_CELLS = 25200;

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