//
// Created by stephan on 03.04.19.
//

#ifndef SHADOWDRAWGUI_SCRIBBLEAREA_H
#define SHADOWDRAWGUI_SCRIBBLEAREA_H

#include <QtWidgets>
#include "Blending.h"
#include <vector>
#include <iostream>

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    ScribbleArea(QWidget *parent = 0);
    float nowFactor;
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
    void drawLineTo(const QPointF &endPoint);
    void resizeImage(QImage *image, const QSize &newSize,const QPixmap *layer);
    void resizePixmap(QPixmap *image, const QSize &newSize);
    void scaleImage(float factor);
    void setImage(const QImage &newImage);
    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPointF lastPointF;
    QPixmap layer;
    QLabel *imageLabel;
    QLabel *drawLabel;
    std::vector<std::pair<QPointF,QPointF>> points;
};


#endif //SHADOWDRAWGUI_SCRIBBLEAREA_H
