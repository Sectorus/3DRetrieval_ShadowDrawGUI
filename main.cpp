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

#include "MainWindow.h"

using namespace cv;
using namespace std;

static void help() {
    cout << "\nThis sample program demonstrates the use of the convexHull() function\n"
         << "Call:\n"
         << "./convexhull\n" << endl;
}

int main(int argc, char **argv) {

    /*
    //QT Library Dependency Test Code
    QApplication a(argc, argv);
    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsPixmapItem item(QPixmap("img/test.jpg"));
    scene.addItem(&item);
    layout->addWidget(&view);

    window.resize(800, 600);
    window.show();
    window.setWindowTitle(QApplication::translate("toplevel", "QTWidget Test"));

    //OpenCV Library Dependency Test Code
    CommandLineParser parser(argc, argv, "{help h||}");
    if (parser.has("help")) {
        help();
        return 0;
    }
    Mat img(500, 500, CV_8UC3);
    RNG &rng = theRNG();
    for (;;) {
        char key;
        int i, count = (unsigned) rng % 100 + 1;
        vector<Point> points;
        for (i = 0; i < count; i++) {
            Point pt;
            pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
            pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
            points.push_back(pt);
        }
        vector<int> hull;
        convexHull(Mat(points), hull, true);
        img = Scalar::all(0);
        for (i = 0; i < count; i++)
            circle(img, points[i], 3, Scalar(0, 0, 255), FILLED, LINE_AA);
        int hullcount = (int) hull.size();
        Point pt0 = points[hull[hullcount - 1]];
        for (i = 0; i < hullcount; i++) {
            Point pt = points[hull[i]];
            line(img, pt0, pt, Scalar(0, 255, 0), 1, LINE_AA);
            pt0 = pt;
        }
        imshow("hull", img);
        key = (char) waitKey();
        if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
            break;
    }
    delete layout;
    return 0;
     */

    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
