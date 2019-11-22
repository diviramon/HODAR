#pragma once
#ifndef YOLO_H
#define YOLO_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <thread>
#include <future>
#include <atomic>
#include <mutex>         // std::mutex, std::unique_lock
#include <cmath>

// It makes sense only for video-Camera (not for video-File)
// To use - uncomment the following line. Optical-flow is supported only by OpenCV 3.x - 4.x
#include "yolo_v2_class.hpp"    // imported functions from DLL
#include <opencv2/opencv.hpp>            // C++
#include <opencv2/core/version.hpp>
#include <opencv2/videoio/videoio.hpp>

std::vector<bbox_t> get_3d_coordinates(std::vector<bbox_t> bbox_vect, cv::Mat xyzrgba);

void draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vec, std::vector<std::string> obj_names,
    int current_det_fps = -1, int current_cap_fps = -1);

void show_console_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names, int frame_id = -1);

std::vector<std::string> objects_names_from_file(std::string const filename);

template<typename T>
class send_one_replaceable_object_t {
    const bool sync;
    std::atomic<T *> a_ptr;
public:
    void send(T const& _obj);
    T receive();
    bool is_object_present();
    send_one_replaceable_object_t(bool _sync);
};

int scan(std::string Filename);

int detect(std::string Filename, float const Thresh);

int scan(std::string Filename, float const Thresh);

#endif