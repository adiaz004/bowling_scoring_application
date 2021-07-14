#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frameform.h"
#include "common.h"

#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QMap>

/**
 * @brief MainWindow::MainWindow
 * Constructor for main window, setups the game and creates a new
 * game and creates a new bowling manager.
 * @param parent
 */
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
    ui->errorLabel->setVisible(false);
    setupActions();
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
    /* delete each item in the frameWidgetVector */
    foreach (QWidget* widget, frameWidgetVector) {
        delete widget;
    }
}

/**
 * @brief MainWindow::setupActions
 * connects signals from the bolwing manager and UI to the correct slots.
 */
void MainWindow::setupActions()
{
    connect(bowlingGM, SIGNAL(currentFrameSignal(QString)), ui->activeFrameNumber, SLOT(setText(QString)));
    connect(bowlingGM, SIGNAL(frameInfoSignal(int, int, int)), this,SLOT(handleFrameUpdates(int, int, int)));
    connect(bowlingGM, SIGNAL(frameScoreSignal(int, int)), this,SLOT(handleFrameScoreUpdate(int, int)));
    connect(ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitGame()));
}

/**
 * @brief MainWindow::exitGame
 * exits the game gracefully.
 */
void MainWindow::exitGame()
{
    QCoreApplication::quit();
}

/**
 * @brief MainWindow::scoreButtonClicked
 * handler for whenever any of the score buttons are pressed.
 */
void MainWindow::scoreButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if( button != NULL )
    {
      int result = bowlingGM->recordScore(button->text().at(0));
      if (result == FAILURE) {
          ui->errorLabel->setVisible(true);
          qDebug() << "invalid score!";
      } else {
          ui->errorLabel->setVisible(false);
      }
    }
}

/**
 * @brief MainWindow::startNewGame
 * resets the form and tells the bowling game manager to start a
 * new game.
 */
void MainWindow::startNewGame()
{
    foreach (FrameForm* frame, frameWidgetVector){
        frame->resetFrame();
    }
    bowlingGM->newGame();
}

/**
 * @brief MainWindow::handleFrameUpdates
 * handles updates for round scores, it'll instruct the child frame
 * to update it's UI.
 * @param frame the frame to update
 * @param round the round to update
 * @param score the score to update too
 */
void MainWindow::handleFrameUpdates(int frame, int round, int score)
{
    FrameForm* frameFrom = frameWidgetVector.at(frame);
    frameFrom->updateRoundScore(frame, round, score);
}

/**
 * @brief MainWindow::handleFrameScoreUpdate
 * handles new frame score info and passes it into the correct
 * ui frame.
 * @param frame
 * @param score
 */
void MainWindow::handleFrameScoreUpdate(int frame, int score) {
    FrameForm* frameFrom = frameWidgetVector.at(frame);
    frameFrom->updateFinalRoundScore(score);
}
