#ifndef FRAMEFORM_H
#define FRAMEFORM_H

#include <QWidget>

namespace Ui {
class FrameForm;
}

class FrameForm : public QWidget
{
    Q_OBJECT

public:
    explicit FrameForm(QWidget *parent = nullptr, int frameNumber = 0);
    ~FrameForm();

private:
    Ui::FrameForm *ui;
};

#endif // FRAMEFORM_H
