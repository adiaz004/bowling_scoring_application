#include "frameform.h"
#include "ui_frameform.h"

FrameForm::FrameForm(QWidget *parent, int frameNumber) :
    QWidget(parent),
    ui(new Ui::FrameForm)
{
    ui->setupUi(this);
    ui->frameNumberLabel->setText(QString("Frame %1").arg(frameNumber));
}

FrameForm::~FrameForm()
{
    delete ui;
}
