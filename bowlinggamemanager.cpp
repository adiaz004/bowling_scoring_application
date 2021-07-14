#include "bowlinggamemanager.h"
#include "common.h"
#include <QDebug>

BowlingGameManager::BowlingGameManager()
{
    this->newGame();
    setupValidScoreValues();
    setupFrames(NUM_FRAMES);
}

BowlingGameManager::~BowlingGameManager()
{
    delete this;
    /* TODO: delete scoreMap */
    /* TODO: delete stack */
}

/*
 * Reset all valuts and start a new game.
 */
void BowlingGameManager::newGame()
{
    this->currentFrame = 0;
    this->currentFrameScore = 0;
    this->totalScore = 0;
    this->gameInProgress = true;
    /* empty stack */
    while (this->stack.size() != 0) {
        this->stack.pop();
    }

    /* reset all frames */
    for (int i = 0; i < frames.size(); i++) {
       frames.at(i)->resetFrame();
    }
    emit currentFrameSignal(QString::number(this->currentFrame + 1));
}

/*
 * This function takes in a raw char representing the score for current
 * frame and round, process the score and add it to the stack.
 */
void BowlingGameManager::recordScore(QChar scoreAsChar)
{
    if (!scoreMap.contains(scoreAsChar)) {
        qDebug() << "invalid scored passed in.";
        return;
    }
    if (!gameInProgress) {
        qDebug() << "Game Over...";
        return;
    }

    /* Get current frame and record score. */
    int score = scoreMap[scoreAsChar];

    for (int i = 0; i < currentFrame; i++) {
        Frame* frame = frames.at(i);
        if (frame->getRemainingBonus() > 0) {
            frame->addBonus(score);
        }
    }

    Frame* frame = frames.at(this->currentFrame);
    frame->recordRound(score);

    if (frame->isFrameComplete()) {
        bumpFrame();
    }

    updateGameScore();
}

/*
 * Bump Frame to the next frame if needed.
 */
void BowlingGameManager::bumpFrame() {
    /* no need to increment frame if we're on the 10th frame. */
    if (currentFrame != 9) {
        currentFrame++;
        /* notify others that the frame has been bumped */
        emit currentFrameSignal(QString::number(this->currentFrame + 1));
    }
}

void BowlingGameManager::updateGameScore()
{
    int totalScore = 0;
    for (int i = 0; i < currentFrame + 1; i++) {
        Frame* frame = frames.at(i);
        emit frameInfoSignal(i, 1, frame->getRoundScore(1));
        emit frameInfoSignal(i, 2, frame->getRoundScore(2));
        emit frameInfoSignal(i, 3, frame->getRoundScore(3));
        if (frame->getRemainingBonus() == 0) {
            if (frame->isFrameComplete()) {
                totalScore += frame->getFrameScore();
                emit frameScoreSignal(i, totalScore);
            }

        } else {
            break;
        }

    }
    qDebug() << "Final Score: " << totalScore;
}

/*
 * Setup the scoreMap with all valid mappings.
 */
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
    scoreMap.insert('X', 10);
}

/*
 * Returns current scoreMap.
 */
QMap<QChar, int> BowlingGameManager::getScoreMap()
{
    return scoreMap;
}

/*
 * Allows others outside this class to start a new game.
 */
void BowlingGameManager::startNewGame()
{
    this->newGame();
}

/*
 * Setup all 10 frames at the beginning of a new game.
 */
void BowlingGameManager::setupFrames(int numFrames)
{
    for (int i = 0; i < numFrames; i++) {
        Frame* frame = new Frame(i);
        frames.append(frame);
    }
}
