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
private:
    Ui::FrameForm *ui;
public slots:
    void updateRoundScore(int frame, int round, int value);
    void updateFinalRoundScore(int frame, int value);
};

#endif // FRAMEFORM_H
