//
// Created by stephan on 03.04.19.
//

#include "MainWindow.h"
#include <QtWidgets>
#include "ScribbleArea.h"

MainWindow::MainWindow()
{
    scribbleArea = new ScribbleArea;
    QScrollArea *qScrollArea = new QScrollArea;
    qScrollArea->setWidget(scribbleArea);
    qScrollArea->setWidgetResizable(true);
    qScrollArea->setBackgroundRole(QPalette::Dark);
    qScrollArea->setAutoFillBackground(true);
    qScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    qScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setCentralWidget(qScrollArea);
   // printf("jeje");
    createActions();
    createMenus();
   // printf("jeje");
    setWindowTitle(tr("Scribble"));
    resize(500, 500);
    // printf("jejeje");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            scribbleArea->openImage(fileName);
    }
}

void MainWindow::openMultiple() {
    if (maybeSave()) {
            scribbleArea->openMultipleImages();
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        scribbleArea->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        scribbleArea->setPenWidth(newWidth);
}
void MainWindow::zoomIn(){
    scribbleArea->zoomIn();
}
void MainWindow::zoomOut(){
    scribbleArea->zoomOut();
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About Scribble"),
                       tr("<p>The <b>Scribble</b> example shows how to use QMainWindow as the "
                          "base widget for an application, and how to reimplement some of "
                          "QWidget's event handlers to receive the events generated for "
                          "the application's widgets:</p><p> We reimplement the mouse event "
                          "handlers to facilitate drawing, the paint event handler to "
                          "update the application and the resize event handler to optimize "
                          "the application's appearance. In addition we reimplement the "
                          "close event handler to intercept the close events before "
                          "terminating the application.</p><p> The example also demonstrates "
                          "how to use QPainter to draw an image in real time, as well as "
                          "to repaint widgets.</p>"));
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

            foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
            QString text = tr("%1...").arg(QString(format).toUpper());

            QAction *action = new QAction(text, this);
            action->setData(format);
            connect(action, SIGNAL(triggered()), this, SLOT(save()));
            saveAsActs.append(action);
        }

    openMultipleAct = new QAction(tr("&Open multiple..."), this);
    connect(openMultipleAct, SIGNAL(triggered()), this, SLOT(openMultiple()));


    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            scribbleArea, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    inZoom=new QAction(tr("&Zoom in"),this);
    inZoom->setShortcut(tr("Ctrl++"));
    connect(inZoom,SIGNAL(triggered()),this,SLOT(zoomIn()));

    outZoom=new QAction(tr("&Zoom out"),this);
    outZoom->setShortcut(tr("Ctrl+-"));
    connect(outZoom,SIGNAL(triggered()),this,SLOT(zoomOut()));

    undoAct=new QAction(tr("&Undo"),this);
    undoAct->setShortcut(tr("Ctrl+Z"));
    connect(undoAct,SIGNAL(triggered()),this,SLOT(undo()));
    
    redoAct=new QAction(tr("&Redo"),this);
    redoAct->setShortcut(tr("Ctrl+Y"));
    connect(redoAct,SIGNAL(triggered()),this,SLOT(redo()));
}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
            foreach (QAction *action, saveAsActs)
            saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(openMultipleAct);

    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);
    optionMenu->addAction(inZoom);
    optionMenu->addAction(outZoom);
    optionMenu->addAction(undoAct);
    optionMenu->addAction(redoAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}
void MainWindow::undo(){
    scribbleArea->undo();
}

void MainWindow::redo(){
    scribbleArea->redo();
}

bool MainWindow::maybeSave()
{
    if (scribbleArea->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Scribble"),
                                   tr("The image has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                            .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                            .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}