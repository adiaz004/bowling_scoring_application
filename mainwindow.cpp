#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frameform.h"
#include "common.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < NUM_FRAMES; i++) {
        /* create a new frame form for the number of frames*/
        frame = new FrameForm(parent, i + 1);
        ui->horizontalLayout->addWidget(frame);

        /*
         * we want to keep track of each frame so we'll store them in
         * a vector for easy reference.
         */
        frameWidgetVector.push_back(frame);

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

