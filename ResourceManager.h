//
// Created by stephan on 26.04.19.
//

#ifndef SHADOWDRAWGUI_RESOURCEMANAGER_H
#define SHADOWDRAWGUI_RESOURCEMANAGER_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <mutex>

class ResourceManager {
public:
    static ResourceManager *instance();

    std::vector<cv::Mat> getResourceImages();

    void loadResourcesFromDirectory(std::string path);

    std::mutex *getMutex();

    std::vector<int> similar_refs_;
    double similarity_threshold_;
private:
    static ResourceManager *instance_;

    ResourceManager();

    ~ResourceManager();

    std::vector<cv::Mat> resource_images_;
    std::mutex *resources_lock_;

};

#endif //SHADOWDRAWGUI_RESOURCEMANAGER_H
