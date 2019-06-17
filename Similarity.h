//
// Created by stephan on 20.05.19.
//

#ifndef SHADOWDRAWGUI_SIMILARITY_H
#define SHADOWDRAWGUI_SIMILARITY_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include "ResourceManager.h"

#define THRESHOLD 0.90

class Similarity {
public:
        cv::Scalar getMSSIM( const cv::Mat& i1, const cv::Mat& i2);
        std::vector<int> getSimilarReferences(const cv::Mat& drawing);
private:
};
#endif //SHADOWDRAWGUI_SIMILARITY_H
