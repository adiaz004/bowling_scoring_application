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

        FrameForm* frame = new FrameForm(parent, i + 1);

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
        connect(button, SIGNAL(clicked()), this, SLOT(scoreButtonClicked()));
    }

    /* add a spacer to move the all score buttons to the left */
    QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->horizontalLayout_3->addItem(item);
    setupActions();
}

MainWindow::~MainWindow()
{
    delete ui;
    /* delete each item in the frameWidgetVector */
    foreach (QWidget* widget, frameWidgetVector) {
        delete widget;
    }
}

void MainWindow::setupActions()
{
    connect(bowlingGM, SIGNAL(currentFrameSignal(QString)), ui->activeFrameNumber, SLOT(setText(QString)));
    connect(bowlingGM, SIGNAL(frameInfoSignal(int, int, int)), this,SLOT(handleFrameUpdates(int, int, int)));
    connect(bowlingGM, SIGNAL(frameScoreSignal(int, int)), this,SLOT(handleFrameScoreUpdate(int, int)));
    connect(ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(startNewGame()));
}

void MainWindow::scoreButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if( button != NULL )
    {
      bowlingGM->recordScore(button->text().at(0));
    }
}

void MainWindow::startNewGame()
{
    foreach (FrameForm* frame, frameWidgetVector){
        frame->resetFrame();
    }
    bowlingGM->newGame();
}

void MainWindow::handleFrameUpdates(int frame, int round, int score)
{
    FrameForm* frameFrom = frameWidgetVector.at(frame);
    frameFrom->updateRoundScore(frame, round, score);
}

void MainWindow::handleFrameScoreUpdate(int frame, int score) {
    FrameForm* frameFrom = frameWidgetVector.at(frame);
    frameFrom->updateFinalRoundScore(score);
}
