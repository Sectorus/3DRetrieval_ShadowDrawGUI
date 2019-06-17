//
// Created by stephan on 03.04.19.
//

#ifndef SHADOWDRAWGUI_MAINWINDOW_H
#define SHADOWDRAWGUI_MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class ScribbleArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void scratch();
    void open();
    void openMultiple();
    void save();
    void penColor();
    void penWidth();
    void about();
    void zoomIn();
    void zoomOut();
    void undo();
    void redo();
    void changeThreshold();
    void erase();
    void paint();
private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    ScribbleArea *scribbleArea;
    ScribbleArea *bg;


    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *scratchAct;
    QAction *openAct;
    QAction *openMultipleAct;
    QAction *eraseAct;
    QAction *paintAct;

    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *inZoom;
    QAction *outZoom;
    QAction *undoAct;
    QAction *redoAct;
    QAction *thresholdAct;
};


#endif //SHADOWDRAWGUI_MAINWINDOW_H
