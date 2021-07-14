#include "bowlinggamemanager.h"
#include "common.h"

/**
 * @brief BowlingGameManager::BowlingGameManager
 * constructor for the bowling game manager. Sets up all
 * necessary data and sets up a new game.
 */
BowlingGameManager::BowlingGameManager()
{
    this->newGame();
    setupValidScoreValues();
    setupFrames(NUM_FRAMES);
}

/**
 * @brief BowlingGameManager::~BowlingGameManager
 */
BowlingGameManager::~BowlingGameManager()
{
    delete this;
    /* TODO: delete scoreMap */
    /* TODO: delete stack */
}

/**
 * @brief BowlingGameManager::newGame
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

/**
 * @brief BowlingGameManager::recordScore
 * This function takes in a raw char representing the score for current
 * frame and round, process the score and add it to the stack
 * @param scoreAsChar score that must be recorded
 */
int BowlingGameManager::recordScore(QChar scoreAsChar)
{
    if (!scoreMap.contains(scoreAsChar)) {
        return SUCCESS;
    }
    if (!gameInProgress) {
        return SUCCESS;
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
    int result = frame->recordRound(score);
    if (result == FAILURE) {
        return result;
    }
    if (frame->isFrameComplete()) {
        bumpFrame();
    }

    updateGameScore();
    return SUCCESS;
}

/**
 * @brief BowlingGameManager::bumpFrame
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

/**
 * @brief BowlingGameManager::updateGameScore
 * calculates the score for the current game.
 */
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
}

/**
 * @brief BowlingGameManager::setupValidScoreValues
 * setup the scoreMap with all valid mappings.
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

/**
 * @brief BowlingGameManager::getScoreMap
 * Returns current scoreMap.
 * @return the map representing all valid score options for
 * this game.
 */
QMap<QChar, int> BowlingGameManager::getScoreMap()
{
    return scoreMap;
}

/**
 * @brief BowlingGameManager::startNewGame
 * allows others outside this class to start a new game.
 */
void BowlingGameManager::startNewGame()
{
    this->newGame();
}

/**
 * @brief BowlingGameManager::setupFrames
 * setup all 10 frames at the beginning of a new game.
 * @param numFrames number of frames to setup.
 */
void BowlingGameManager::setupFrames(int numFrames)
{
    for (int i = 0; i < numFrames; i++) {
        Frame* frame = new Frame(i);
        frames.append(frame);
    }
}
