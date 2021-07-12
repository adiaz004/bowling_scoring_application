#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frameform.h"
#include "common.h"

#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , bowlingGM(new BowlingGameManager)
{
    ui->setupUi(this);

    /* setup the UI with the bowling frames. */
    for (int i = 0; i < NUM_FRAMES; i++) {
        /* create a new frame form for the number of frames. */
        frame = new FrameForm(parent, i + 1);
        ui->horizontalLayout->addWidget(frame);
        /*
         * we want to keep a reference of each frame wiget so we'll store them in
         * a vector for easy reference.
         */
        frameWidgetVector.push_back(frame);
    }

    /* create buttons which represent a valid score. */
    QMap<QChar, int> scoreMap = bowlingGM->getScoreMap();
    for (int i = 0; i < scoreMap.size(); i++) {
        QPushButton* button = new QPushButton(scoreMap.key(i), this);
        button->setMaximumWidth(50);
        button->setMaximumHeight(50);
        ui->horizontalLayout_3->addWidget(button);
    }

    /* add a spacer to move the all score buttons to the left */
    QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->horizontalLayout_3->addItem(item);
    SetupActions();
}

MainWindow::~MainWindow()
{
    delete ui;
    /* delete each item in the frameWidgetVector */
    foreach (QWidget* widget, frameWidgetVector) {
        delete widget;
    }
}

void MainWindow::SetupActions()
{
    connect(bowlingGM, SIGNAL(currentFrameSignal(QString)), ui->activeFrameNumber, SLOT(setText(QString)));
    connect(ui->actionNew_Game, SIGNAL(triggered()), bowlingGM, SLOT(startNewGame()));
}

void MainWindow::HandleFrameInput()
{

}
