#include "frameform.h"
#include "ui_frameform.h"
#include "mainwindow.h"

#include <QObject>
#include <QTextEdit>

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
}

FrameForm::~FrameForm()
{
    delete ui;
}

void FrameForm::updateRoundScore(int frame, int round, int score)
{

}

void FrameForm::updateFinalRoundScore(int frame, int score)
{

}
