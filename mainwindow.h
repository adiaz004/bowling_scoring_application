#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bowlinggamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FrameForm;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void HandleFrameInput();

private:
    Ui::MainWindow *ui;
    FrameForm* frame;
    QVector<QWidget*> frameWidgetVector;
    BowlingGameManager* bowlingGM;

    void SetupActions();

};
#endif // MAINWINDOW_H
