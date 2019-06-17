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
    lastP=0;
    nowFactor=1.0;
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
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
    imageLabel->setStyleSheet("border: 2px solid green");
    update();
    return true;
}
void ScribbleArea::setImage(const QImage &newImage){
    imageLabel->setPixmap(QPixmap::fromImage(newImage));
    update();

}
bool ScribbleArea::openMultipleImages()
{
    Blending b;
    cv::Mat img = b.blend();

    QImage loadedImage = QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize, &layer);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    visibleImage=drawLabel->pixmap()->toImage();
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
    drawLabel->resize(imageLabel->size());
    setFixedWidth(imageLabel->width());
    setFixedHeight(imageLabel->height());
    QPixmap l(imageLabel->size());
    std::cout<<image.size().width()<<"\n";
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
    std::cout<<nowFactor<<"\n";
    std::cout<<points.size()<<"\n";
    if(lastP< pointsSize){
        points.erase(points.begin()+lastP+1,points.begin()+points.size());
        lastP=points.size();
        pointsSize=lastP;
    }
    std::cout<<points.size()<<"\n";
    std::cout<<lastP<<"\n";

    painter.drawLine(lastPointF, endPointF);
    points.push_back(std::make_pair(lastPointF/nowFactor,endPointF/nowFactor));
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
    std::cout<<"layer"<<layer.size().width()<<"\n";
    std::cout<<"dL"<<drawLabel->size().width()<<"\n";
    std::cout<<"iL"<<imageLabel->size().width()<<"\n";
    std::cout<<"dL2"<<drawLabel->rect().width()<<"\n";

}
void ScribbleArea::undo(){
    std::cout<<lastP<<"\n";
    if (lastP>10) {
        lastP = lastP - 10;
    }
    else{
        lastP=0;
    }
    QPainter painter(&layer);
    painter.eraseRect(layer.rect());
    layer.fill(Qt::transparent);
    drawLabel->setPixmap(layer);
    for(int i=0;i<lastP;i++){
        painter.drawLine(points[i].first*nowFactor,points[i].second*nowFactor);
    }
}
void ScribbleArea::redo(){
    if(lastP+10<pointsSize){
        lastP=lastP+10;
    }
    else{
        lastP=pointsSize;
    }

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
