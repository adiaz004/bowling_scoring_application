#include "bowlinggamemanager.h"

BowlingGameManager::BowlingGameManager()
{
    this->NewGame();
}

BowlingGameManager::~BowlingGameManager()
{
    delete this;
}

void BowlingGameManager::NewGame()
{
    this->currentFrame = 1;
    this->currentFrameScore = 0;
    this->totalScore = 0;
    this->currentRoll = 1;
    /* empty stack */
    while (this->stack.size() != 0) {
        this->stack.pop();
    }
    setupValidScoreValues();
    emit currentFrameSignal(QString::number(this->currentFrame));
}

void BowlingGameManager::RecordScore(int frame, int score)
{
    if (currentRoll == 1) {
        /* check for anything less then a strike */
        if (score < 10) {
            currentFrameScore += score;
        } else if (score == 10) {
            /* we got a strike */
            /* do something with strike */
        }
        currentRoll += 1;
    } else if (currentRoll == 2) {
        /* check for spare */
        if (currentFrameScore + score == 10) {
            /* do something with a spare */
        }
    }
}

void BowlingGameManager::setupValidScoreValues()
{
    scoreMap.insert('0', 0);
    scoreMap.insert('1', 1);
    scoreMap.insert('2', 2);
    scoreMap.insert('3', 3);
    scoreMap.insert('4', 4);
    scoreMap.insert('5', 5);
    scoreMap.insert('6', 6);
    scoreMap.insert('7', 7);
    scoreMap.insert('8', 8);
    scoreMap.insert('9', 9);
    scoreMap.insert('/', 11);
    scoreMap.insert('X', 10);
}

QMap<QChar, int> BowlingGameManager::getScoreMap()
{
    return scoreMap;
}

void BowlingGameManager::startNewGame()
{
    this->NewGame();
}
