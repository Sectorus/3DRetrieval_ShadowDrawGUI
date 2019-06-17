//
// Created by stephan on 26.04.19.
//

#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    resources_lock_ = new std::mutex();
}

ResourceManager::~ResourceManager() {
    delete resources_lock_;
}

ResourceManager *ResourceManager::instance_ = 0;

ResourceManager *ResourceManager::instance() {
    if (!instance_) {
        instance_ = new ResourceManager();
    }
    return instance_;
}

std::vector<cv::Mat> ResourceManager::getResourceImages(){
    return resource_images_;
}

void ResourceManager::loadResourcesFromDirectory(std::string path) {
    std::vector<std::string> stringvec;
    DIR* dirp = opendir(path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        stringvec.push_back(dp->d_name);
    }
    closedir(dirp);

    for(int i = 2; i < stringvec.size(); i++)
    {
        auto file = stringvec.at(i);
        cv::Mat m = cv::imread(path+"/"+file);
       // std::cout <<"Resource "<< m.rows << "," << m.cols << std::endl;
        resource_images_.push_back(m);
    }
}

