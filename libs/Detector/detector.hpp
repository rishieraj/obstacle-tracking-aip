/**
 * @file detector.hpp
 * @author Rishie Raj (rraj27@umd.edu), Uthappa Madettira (uthu@umd.edu)
 * @brief Header file for detector class
 * @version 0.1
 * @date 2024-10-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#pragma once

/**
 * @brief Custom structure for handling the output of the detector module
 * 
 */
struct DetectorOutput {
  std::vector<cv::Point> pixels;
  cv::Mat boxed_img;
};

/**
 * @brief Class declaration of detector module
 * 
 */
class Detector {
 private:
  cv::dnn::Net yolo_model;
  cv::Size yolo_img_size;
  cv::Size original_img_size;
  const float confidence_threshold;
  const float nms_threshold;
  const float score_threshold;
  const int yolo_grid_cells;
  cv::Mat img;
  cv::Mat boxed_img;
  const std::vector<std::string> yolo_classes;
  /**
   * @brief Declaration of method to preprocess image before input to the detector
   * 
   * @return cv::Mat 
   */
  cv::Mat preprocess_img();

  /**
   * @brief Declaration of method to update the pixels of the bounding boxes
   * 
   * @param boxes 
   * @param confidence_values 
   * @param box_pixels 
   */
  void get_bounding_boxes(std::vector<cv::Rect> boxes,
                          std::vector<float> confidence_values,
                          std::vector<cv::Point>& box_pixels);

  /**
   * @brief Declaration of method to update the output object with bounding boxes and target pixels
   * 
   * @param yolo_outputs 
   * @return DetectorOutput 
   */
  DetectorOutput postprocess_img(std::vector<cv::Mat> yolo_outputs);

 public:
  /**
   * @brief Construct a new Detector object
   * 
   * @param yolo_model 
   * @param yolo_img_width 
   * @param yolo_img_height 
   * @param confidence_threshold 
   * @param nms_threshold 
   * @param score_threshold 
   * @param yolo_grid_cells 
   * @param yolo_classes 
   */
  Detector(cv::dnn::Net yolo_model, int yolo_img_width, int yolo_img_height,
           float confidence_threshold, float nms_threshold,
           float score_threshold, int yolo_grid_cells,
           std::vector<std::string>& yolo_classes);
  
  /**
   * @brief Declaration of method for human detection using YOLOv5 model
   * 
   * @param video_frame 
   * @return DetectorOutput 
   */
  DetectorOutput detect_humans(cv::Mat video_frame);
  ~Detector();
};
