/**
 * @file tracker.hpp
 * @author Rishie Raj (rraj27@umd.edu), Uthappa Madettira (uthu@umd.edu)
 * @brief Header file for tracker class
 * @version 0.1
 * @date 2024-10-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <opencv2/opencv.hpp>
#include <vector>

#pragma once

/**
 * @brief Class declaration for the tracker module
 * 
 */

class Tracker {
 private:
  float _height;
  float _focal_length;
  float _hfov;
  float _vfov;
  float _pixel_size;
  const std::vector<int> _resolution;
  float degrees_to_radians(float);
  float radians_to_degrees(float radians);

 public:
  std::vector<std::vector<float>> pixel_to_camera_frame(
      std::vector<cv::Point> prediction_pixels);
  cv::Mat plot_coordinates(std::vector<cv::Point> prediction_pixels,
                           std::vector<std::vector<float>> coordinates,
                           cv::Mat frame);
  Tracker(float height, float focal_length, float hfov, float vfov,
          std::vector<int>& resolution, float pixel_size);
  ~Tracker();
};