#ifndef FRAME_H
#define FRAME_H

#include <QObject>



class Frame : public QObject
{
    Q_OBJECT
public:
    Frame(int frameNumber);
    ~Frame();
    void recordRound(int score);
    bool isFrameComplete();
    void resetFrame();
    void addBonus(int bonusScore);
    int getRemainingBonus();
    int getFrameScore();
    int getRoundScore(int round);
    void setFrameScore(int score);
    bool frameStarted();

signals:
    void frameDataSignal(int frame, int round, int score);

private:
    int frame;
    int frameScore;
    int bonus;
    int currentRound;
    int roundOne;
    int roundTwo;
    int roundThree;
    bool isStrike;
    bool isSpare;
    bool frameHasStarted;
    bool frameComplete;
    void recordFirstNineRounds(int score);
    void recordTenthRound(int score);
};

#endif // FRAME_H
