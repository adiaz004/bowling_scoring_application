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
    void scoreButtonClicked();
    void startNewGame();
    void handleFrameUpdates(int frame, int round, int score);
    void handleFrameScoreUpdate(int frame, int score);
    void exitGame();
private:
    Ui::MainWindow *ui;
    QVector<FrameForm*> frameWidgetVector;
    BowlingGameManager* bowlingGM;

    void setupActions();

};
#endif // MAINWINDOW_H
