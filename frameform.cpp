#include "frameform.h"
#include "ui_frameform.h"
#include "mainwindow.h"
#include "common.h"

#include <QObject>
#include <QTextEdit>
#include <Qt>

/**
 * @brief FrameForm::FrameForm
 * creates a new frame form object, supports the frame from widget.
 * @param parent
 * @param frameNumber
 */
FrameForm::FrameForm(QWidget *parent, int frameNumber) :
    QWidget(parent),
    ui(new Ui::FrameForm)
{
    /* ensure we have a valid frame number */
    if (frameNumber < 0) {
        qCritical() << "Error: FrameForm initiated with invalid frameNumber\n";
    }
    ui->setupUi(this);

    this->frameNumber = frameNumber;   
    ui->frameNumberLabel->setText(QString("Frame %1").arg(frameNumber));

    if (frameNumber == 10) {
        QTextEdit* textEdit = new QTextEdit();
        textEdit->setObjectName("frameThreeRoundScore");
        textEdit->setMaximumSize(35, 20);
        textEdit->setReadOnly(true);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QString styleSheetString = "border: 2px solid black";
        textEdit->setStyleSheet(styleSheetString);

        ui->gridLayout->addWidget(textEdit, 0, 2, 1, 1);
    }
}

/**
 * @brief FrameForm::~FrameForm
 */
FrameForm::~FrameForm()
{
    delete ui;
}

/**
 * @brief FrameForm::updateRoundScore
 * updates UI with frame info.
 * @param frame
 * @param round
 * @param score
 */
void FrameForm::updateRoundScore(int frame, int round, int score)
{
    QString value = "";
    if (score == MAYBE_NOT_USED){
        value = "";
    } else if (score == 0) {
        value = "--";
    } else if ((round == 1 && score == 10) ||(frame == 10)) {
        value = "X";
    } else if (score == SPARE) {
        value = "/";
    } else {
        value = QString("%1").arg(score);
    }
    switch (round) {
    case 1:
        ui->frameFirstRoundScore->setText(value);
        break;
    case 2:
        ui->frameSecondRoundScore->setText(value);
        break;
    case 3:
        /*
         * this third wigdet is created at runtime for the tenth frame,
         * so we need to search for it by name as it may not exist.
         */
        QTextEdit* ts = this->findChild<QTextEdit*>("frameThreeRoundScore");
        if (ts != NULL) {
            ts->setText(value);
        }
        break;
    }
}

/**
 * @brief FrameForm::updateFinalRoundScore
 * updates the frame score
 * @param score
 */
void FrameForm::updateFinalRoundScore(int score)
{
    ui->frameTotalScore->setText(QString("%1").arg(score));
}

/**
 * @brief FrameForm::resetFrame
 * resets frame back to default vaules.
 */
void FrameForm::resetFrame()
{
    ui->frameFirstRoundScore->setText("");
    ui->frameSecondRoundScore->setText("");
    ui->frameTotalScore->setText("");
    /*
     * this third wigdet is created at runtime for the tenth frame,
     * so we need to search for it by name as it may not exist.
     */
    QTextEdit* ts = this->findChild<QTextEdit*>("frameThreeRoundScore");
    if (ts != NULL) {
        ts->setText("");
    }
}
