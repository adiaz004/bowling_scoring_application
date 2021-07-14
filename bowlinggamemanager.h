#ifndef BOWLINGGAMEMANAGER_H
#define BOWLINGGAMEMANAGER_H
#include <QStack>
#include <QMap>
#include <QObject>
#include <QChar>
#include "frame.h"

class BowlingGameManager: public QObject
{
    Q_OBJECT
public:
    BowlingGameManager();
    ~BowlingGameManager();
    void newGame();
    int recordScore(QChar score);
    QMap<QChar, int> getScoreMap();

signals:
    void currentFrameSignal(QString);
    void frameInfoSignal(int frame, int round, int score);
    void frameScoreSignal (int frame, int score);
private slots:
    void startNewGame();
private:
    bool gameInProgress;
    int currentFrame;
    int currentFrameScore;
    int totalScore;
    int currentRound;
    QStack<int> stack;
    QVector<Frame*> frames;
    QMap<QChar, int> scoreMap;
    void setupValidScoreValues();
    void setupFrames(int numFrames);
    void bumpFrame();
    void updateGameScore();
};

#endif // BOWLINGGAMEMANAGER_H
