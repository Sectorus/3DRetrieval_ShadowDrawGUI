//
// Created by stephan on 20.03.19.
//

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/utils/filesystem.hpp"


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

    cv::utils::fs::createDirectory(in_path);
    cv::utils::fs::createDirectory(out_path);


    DIR *dirp = opendir(in_path.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
        stringvec.push_back(dp->d_name);
    }
    closedir(dirp);

    EdgeDetector ed;

    for (unsigned int i = 2; i < stringvec.size(); i++) {
        auto file = stringvec.at(i);
        cv::Mat contour = ed.detectEdges(imread(in_path + "/" + file));
        imwrite(out_path + "/" + file, contour);
    }
    ResourceManager::instance()->loadResourcesFromDirectory(out_path);

    QApplication app(argc, argv);

    if(ResourceManager::instance()->getResourceImages().size() == 0){
        QMessageBox msgBox;
        msgBox.setText("No references available. Please store some reference images into your 'img' directory. Exiting now...");
        msgBox.exec();
        exit(0);
    }

    MainWindow window;
    window.show();

    return app.exec();
}

