//
// Created by stephan on 03.04.19.
//
#include <QtWidgets>
#include "ScribbleArea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
        : QWidget(parent)
        // imageLabel(new QLabel)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::black;
    /*imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
     */
}

bool ScribbleArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    QImage newImage(newSize, QImage::Format_RGB32);


    newImage.fill(Qt::transparent);
    resizeImage(&loadedImage, newSize, &newImage);

    image = loadedImage;
    //setImage(image);

    modified = false;
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
void ScribbleArea::scaleImage(double factor){
    /*Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
     */
    const QSize d=image.size().scaled(factor*image.width(),factor*image.height(),Qt::KeepAspectRatio);
    //imageLabel->resize(factor * imageLabel->pixmap()->size());
    resizeImage(&image,d,&layer);

    //resizeImage(&image,newSize,&layer);
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
        lastPoint = event->pos();
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
    painter.drawImage(0, 0, /**imageLabel->pixmap()*/ image);
    painter.drawImage(dirtyRect, layer, dirtyRect);
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
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&layer);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                   .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void ScribbleArea::resizeImage(QImage *image, const QSize &newSize,const QImage *layer)
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

    QPainter painter(&newImage);


    layer=&newImage;

    painter.drawImage(QPoint(0, 0), *scaledImage);
    painter.drawImage(QPoint(0, 0),*layer);
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
