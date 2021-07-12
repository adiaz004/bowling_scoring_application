#ifndef BOWLINGGAMEMANAGER_H
#define BOWLINGGAMEMANAGER_H
#include <QStack>
#include <QMap>
#include <QObject>

class BowlingGameManager: public QObject
{
    Q_OBJECT
public:
    BowlingGameManager();
    ~BowlingGameManager();
    void NewGame();
    void RecordScore(int frame, int score);
    QMap<QChar, int> getScoreMap();
signals:
    void currentFrameSignal(QString);
private slots:
    void startNewGame();
private:
    bool gameInProgress;
    int currentFrame;
    int currentFrameScore;
    int totalScore;
    int currentRoll;
    QStack<int> stack;
    QMap<QChar, int> scoreMap;
    void setupValidScoreValues();
};

#endif // BOWLINGGAMEMANAGER_H
