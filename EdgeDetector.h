//
// Created by stephan on 25.04.19.
//

#ifndef SHADOWDRAWGUI_EDGEDETECTOR_H
#define SHADOWDRAWGUI_EDGEDETECTOR_H


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>


class EdgeDetector{
public:
    void detectEdges(cv::Mat img);
private:
    cv::Mat src; cv::Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;

    int dilation_elem = 0;
    int dilation_size = 0;
    int const max_elem = 2;
    int const max_kernel_size = 21;

    void CannyThreshold();
    void Dilation();
};

#endif //SHADOWDRAWGUI_EDGEDETECTOR_H
