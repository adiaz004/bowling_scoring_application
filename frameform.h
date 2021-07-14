#ifndef FRAMEFORM_H
#define FRAMEFORM_H

#include <QWidget>
#include "bowlinggamemanager.h"

namespace Ui {
class FrameForm;
}

class FrameForm : public QWidget
{
    Q_OBJECT
public:
    explicit FrameForm(QWidget *parent = nullptr, int frameNumber = 0);
    ~FrameForm();
    int frameNumber;
    void updateRoundScore(int frame, int round, int score);
    void updateFinalRoundScore(int value);
    void resetFrame();
protected:
    Ui::FrameForm *ui;

public slots:
};

#endif // FRAMEFORM_H
