#ifndef FRAME_H
#define FRAME_H

#include <QObject>



class Frame : public QObject
{
    Q_OBJECT
public:
    Frame(int frameNumber);
    ~Frame();
    int recordRound(int score);
    void resetFrame();
    void addBonus(int bonusScore);
    int getRemainingBonus();
    int getFrameScore();
    int getRoundScore(int round);
    bool isFrameComplete();
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
    int recordFirstNineRounds(int score);
    int recordTenthRound(int score);
};

#endif // FRAME_H
