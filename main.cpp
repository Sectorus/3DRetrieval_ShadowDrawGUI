//
// Created by stephan on 20.03.19.
//

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <QtWidgets>
#include <QtGui>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsScene>

#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>

#include "MainWindow.h"
#include "Blending.h"
#include "EdgeDetector.h"
#include "ResourceManager.h"
#include "Similarity.h"

using namespace cv;
using namespace std;


int main(int argc, char **argv) {

    std::string in_path = "img";
    std::string out_path = "sketch_ref";

    std::vector<std::string> stringvec;

    DIR* dirp = opendir(in_path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        stringvec.push_back(dp->d_name);
    }
    closedir(dirp);

    EdgeDetector ed;

    for(unsigned int i = 2; i < stringvec.size(); i++)
    {
        auto file = stringvec.at(i);
        cv::Mat contour = ed.detectEdges( imread(in_path+"/"+file) );
        imwrite( out_path+"/"+file, contour );
    }

    ResourceManager::instance()->loadResourcesFromDirectory(out_path);
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    //Quick test for similarity class
    cv::Mat img1 = cv::imread("sketch_ref/cva_athens_5_1_1-e.jpg");
    cv::Mat img2 = cv::imread("sketch_ref/cva_athens_5_1_2-e.jpg");

    Similarity sim;
    cv::Scalar s1 = sim.getMSSIM(img1, img1);
    cv::Scalar s2 = sim.getMSSIM(img1, img2);

    double similarity_score1 = sum(s1)[0]/3;
    double similarity_score2 = sum(s2)[0]/3;

    std::cout << "Similarity score of same image: " << similarity_score1*100 << "%" << std::endl;
    std::cout << "Similarity score of different images: " << similarity_score2*100 << "%" << std::endl;

    return app.exec();
}

