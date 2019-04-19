//
// Created by stephan on 03.04.19.
//

#ifndef SHADOWDRAWGUI_SCRIBBLEAREA_H
#define SHADOWDRAWGUI_SCRIBBLEAREA_H

#include <QtWidgets>
#include "Blending.h"

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    ScribbleArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool openMultipleImages();
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    void zoomIn();
    void zoomOut();
public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize,const QImage *layer);
    void resizePixmap(QPixmap *image, const QSize &newSize);
    void scaleImage(double factor);
    void setImage(const QImage &newImage);
    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    QImage layer;
    QLabel *imageLabel;
};


#endif //SHADOWDRAWGUI_SCRIBBLEAREA_H
