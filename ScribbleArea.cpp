//
// Created by stephan on 03.04.19.
//
#include <QtWidgets>
#include "ScribbleArea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
        : QWidget(parent),
         imageLabel(new QLabel),
         drawLabel(new QLabel)
{
    setStyleSheet("border: 1px solid red");
    pointsSize=0;
    nowFactor=1.0;
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 3;
    myPenColor = Qt::black;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->setParent(this);
    resize(480,480);
    setStyleSheet("border: 1px solid red");

}

bool ScribbleArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;
    pointsSize=0;
    QSize newSize = loadedImage.size().expandedTo(size());
    QImage newImage(newSize, QImage::Format_RGB32);
    std::cout<<newSize.width();

    newImage.fill(Qt::transparent);
    image = loadedImage;
    loadedRef = loadedImage;
    setFixedWidth(image.width());
    setFixedHeight(image.height());
    imageLabel->resize(newSize);
    //resizeImage(&loadedImage, newSize, &loadedImage);


    //setImage(image);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->show();

    modified = false;

    QPixmap l(newSize);
    layer=l;
    layer.fill(Qt::transparent);
    drawLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    drawLabel->setScaledContents(true);
    drawLabel->setPixmap(layer);
    drawLabel->setParent(this);
    drawLabel->show();
    drawLabel->setStyleSheet("border: 2px solid blue");
    update();
    return true;
}
void ScribbleArea::setImage(const QImage &newImage){
    imageLabel->setPixmap(QPixmap::fromImage(newImage));
    update();

}

void ScribbleArea::updateReferences(){

    //TODO clean up and move logic to other business layer
    Similarity sim;
    Blending blend;
    QPainter painter(&layer);

    QImage img = drawLabel->pixmap()->toImage();
    cv::Mat  mat( img.height(), img.width(),
                  CV_8UC4,
                  const_cast<uchar*>(img.bits()),
                  static_cast<size_t>(img.bytesPerLine()));

    std::vector<cv::Mat> pngChannels(4);
    cv::split(mat, pngChannels);
    pngChannels[0].setTo(cv::Scalar(255), pngChannels[3]==0);
    pngChannels[1].setTo(cv::Scalar(255), pngChannels[3]==0);
    pngChannels[2].setTo(cv::Scalar(255), pngChannels[3]==0);

    cv::Mat mat_without_alpha, result;
    cv::merge(pngChannels, mat_without_alpha);
    cv::cvtColor(mat_without_alpha, result, cv::COLOR_RGBA2RGB);

    //mat = cv::Scalar::all(123);
    //cv::imshow("Update", result);
    //std::cout << mat << std::endl;
    //cv::imwrite("out.png", mat);
    cv::Mat m = ResourceManager::instance()->getResourceImages().at(0);


    //double r = sum(sim.getMSSIM(m, result))[0]/3;
    //std::cout << "Similarity " << r << std::endl;
    std::vector<int> refs = sim.getSimilarReferences(result);
    std::cout << "Similar images: "  << refs.size() << std::endl;
    cv::Mat blended = blend.blend(refs);
    cv::Mat loadedI( loadedRef.height(), loadedRef.width(),
                  CV_8UC4,
                  const_cast<uchar*>(loadedRef.bits()),
                  static_cast<size_t>(loadedRef.bytesPerLine()));
    cv::Mat conv_loaded;
    cv::cvtColor(loadedI, conv_loaded, cv::COLOR_RGBA2RGB);
    cv::Mat finished;
    cv::addWeighted(blended, 0.5, conv_loaded, 0.5, 0, finished);


    QImage blendedImage( finished.data,
                         finished.cols, finished.rows,
                  static_cast<int>(finished.step),
                  QImage::Format_RGB888 );

    imageLabel->setPixmap(QPixmap::fromImage(blendedImage));
    imageLabel->show();
    update();

    /*
    cv::Mat result = ResourceManager::instance()->getResourceImages().at(refs.at(0));
    for(int i = 1; i < refs.size(); i++){
        cv::Mat mat = ResourceManager::instance()->getResourceImages().at(refs.at(i));
        result = blend.alphaBlend(result, 0.5, mat , 0.5);
    }

    QImage loadedImage = QImage((uchar*) result.data, result.cols, result.rows, result.step, QImage::Format_RGB888);
    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize, &layer);
    image = loadedImage;
    modified = false;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->show();
    update();
     */
}

bool ScribbleArea::openMultipleImages()
{
    /*
    Blending b;
    //cv::Mat img = b.blend();

    QImage loadedImage = QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize, &layer);
    image = loadedImage;
    modified = false;
    update();*/
    return true;
}

bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    visibleImage=layer.toImage();
    resizeImage(&visibleImage, size(),&layer);

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}
void ScribbleArea::zoomIn()
{
    scaleImage(1.25);
}

void ScribbleArea::zoomOut()
{
    scaleImage(0.8);
}
void ScribbleArea::scaleImage(float factor){
    /*Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
     */
    //const QSize d=image.size().scaled(factor*image.width(),factor*image.height(),Qt::KeepAspectRatio);
    //imageLabel->resize(factor * imageLabel->pixmap()->size());
    //resizeImage(&image,d,&layer);
    nowFactor=nowFactor*factor;
    //resizeImage(&image,newSize,&layer);
    imageLabel->resize(factor * imageLabel->size());
    drawLabel->resize(factor * imageLabel->size());
    setFixedWidth(imageLabel->width());
    setFixedHeight(imageLabel->height());
    QPixmap l(imageLabel->size()*nowFactor);
    layer=l;
    layer.fill(Qt::transparent);
    QPainter painter(&layer);
    painter.eraseRect(layer.rect());
    layer.fill(Qt::transparent);
    drawLabel->setPixmap(layer);
    for(int i=0;i<lastP;i++){
        painter.drawLine(points[i].first*nowFactor,points[i].second*nowFactor);
    }

    QApplication::processEvents();
}
void ScribbleArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void ScribbleArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPointF = event->pos();
        scribbling = true;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        updateReferences();
        scribbling = false;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    //painter.drawImage(0, 0, /**imageLabel->pixmap()*/ image);
    //painter.drawPixmap(dirtyRect, layer, dirtyRect);
    drawLabel->setPixmap(layer);
    drawLabel->show();
}

void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight),&layer);
        update();
    }
    QWidget::resizeEvent(event);
    printf("resizeEvent");
}

void ScribbleArea::drawLineTo(const QPointF &endPointF)
{
    QPainter painter(&layer);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    int n=points.size();
    for (int i=0; i<n; i++)
    {
        // "first" and "second" are used to access
        // 1st and 2nd element of pair respectively
        //std::cout << points[i].first.x() << " "
        //     << points[i].first.y() << endl;
    }
    //std::cout<<nowFactor<<"\n";


    painter.drawLine(lastPointF, endPointF);
    points.push_back(std::make_pair(lastPointF,endPointF));
    pointsSize++;
    lastP++;
    modified = true;
    std::cout << painter.viewport().size().width()<<","<<painter.viewport().size().height()<<"\n";
    int rad = (myPenWidth / 2) + 2;
    //update(QRect(lastPoint, endPoint).normalized()
     //              .adjusted(-rad, -rad, +rad, +rad));

    painter.setPen(QPen(Qt::green, 20, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    //painter.drawPoint(endPointF);
    painter.setPen(QPen(Qt::red, 20, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    //painter.drawPoint(lastPointF);

    lastPointF = endPointF;

}
void ScribbleArea::goBack(){
    lastP=lastP-10;
    QPainter painter(&layer);
    painter.eraseRect(layer.rect());
    layer.fill(Qt::transparent);
    drawLabel->setPixmap(layer);
    for(int i=0;i<lastP;i++){
        painter.drawLine(points[i].first*nowFactor,points[i].second*nowFactor);
    }
}
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize,const QPixmap *layer)
{

    setFixedWidth(image->width());
    setFixedHeight(image->height());
    if (image->size() == newSize){
        return;
    }
    QImage *scaledImage=image;
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    if(image!= nullptr){
        QImage newImage(image->size(), QImage::Format_RGB32);
        //newImage.fill(qRgb(255, 255, 255));
        newImage.fill(Qt::transparent);
        *scaledImage=image->scaled(newSize,Qt::KeepAspectRatio);
    }
    newImage.fill(qRgb(255, 255, 255));
    /*
    QPainter painter(&newImage);


    layer=&newImage;

    //painter.drawImage(QPoint(0, 0), *scaledImage);
    painter.drawImage(QPoint(0, 0),*layer);
     */
    //*image = newImage;
}
void ScribbleArea::resizePixmap(QPixmap *image, const QSize &newSize)
{
    setFixedWidth(image->width());
    setFixedHeight(image->height());
    if (image->size() == newSize){
        return;
    }

    QPixmap newImage(newSize);
    newImage.fill(qRgb(255, 255, 255));
    //QPainter painter(&newImage);
    //painter.drawPixmap(QPoint(0, 0), *image);
    *image = newImage;
}
