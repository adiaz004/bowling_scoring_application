#include "frame.h"
#include "common.h"
#include <QDebug>

Frame::Frame(int frameNumber)
{
    frame = frameNumber;
    resetFrame();
}

Frame::~Frame()
{
    delete this;
}

bool Frame::frameStarted()
{
    return frameHasStarted;
}

void Frame::recordRound(int score)
{
    if (!frameHasStarted) {
       frameHasStarted = true;
    }
    if (frameComplete) {
        qDebug() << "Frame " << frame << " complete. ignoring score";
        return;
    }

    if (frame < 9) {
        recordFirstNineRounds(score);
    } else {
        recordTenthRound(score);
    }
}

/*
 * This function handels the score logic for each the individual frame.
 */
void Frame::recordFirstNineRounds(int score)
{
    qDebug() << frame << " recording " << score << " for round " << currentRound;
    if (currentRound == 1 && score == 10) {
        /* stike */
        isStrike = true;
        frameScore = score;
        roundOne = score;
        roundTwo = 0;
        bonus = STRIKE_BONUS;
        frameComplete = true;
    } else if (currentRound == 2 && (score + frameScore) == 10) {
        /* spare */
        isSpare = true;
        roundTwo = SPARE;
        frameScore += score;
        frameComplete = true;
        bonus = SPARE_BONUS;
    } else {
        frameScore += score;
        if (currentRound == 1) {
            qDebug () << "RECORDING " << score <<  " round " << currentRound;
            roundOne = score;
        } else if (currentRound == 2) {
            roundTwo = score;
            qDebug () << "RECORDING " << score <<  " round " << currentRound;
            frameComplete = true;

        } else {
            frameComplete = true;
        }
    }

    /* new score means new roll, increase round */
    currentRound++;

    qDebug() << "frame: " << frame << " frameScore: " << frameScore;
}

void Frame::recordTenthRound(int score)
{
    qDebug() << "Recording last round!!!!!!!";
    if (currentRound == 1) {
        if (score == 10) {
            isStrike = true;
        }
        currentRound++;
        roundOne = score;
        frameScore += score;
    } else if (currentRound == 2) {
        if (!isStrike && (frameScore + score) == 10) {
            isSpare = true;
            roundTwo = SPARE;
        } else {
            if (score != 10) {
                frameComplete = true;
            }
            roundTwo = score;
        }

        frameScore += score;
        currentRound++;

    } else if (currentRound == 3) {
        frameScore += score;
        roundThree = score;
        frameComplete = true;
    }
}

/*
 * Returns whether or not this Frame is complete.
 */
bool Frame::isFrameComplete()
{

    /*
     * Frame is complete if we striked, got a spare, or rolled 2
     * balls.
     */
    return frameComplete;
}

/*
 * Resets frame values to default
 */
void Frame::resetFrame()
{

    isSpare = false;
    isStrike = false;
    frameScore = 0;
    currentRound = 1;
    bonus = 0;
    frameHasStarted = false;
    frameComplete = false;
    roundOne = MAYBE_NOT_USED;
    roundTwo = MAYBE_NOT_USED;
    roundThree = MAYBE_NOT_USED;
}

/*
 * Adds the bonus score to this frame.
 */
void Frame::addBonus(int bonusScore)
{
    if (bonus > 0) {
        frameScore += bonusScore;
        bonus--;
    }
}

/*
 * Returns the number of remaining bonuses earned for this
 * frame.
 */
int Frame::getRemainingBonus()
{
    return bonus;
}

/*
 * Returns the frame score.
 */
int Frame::getFrameScore() {
    if (frameComplete && bonus == 0){
        return frameScore;
    }
    return -1;
}

/*
 * Returns the individual round score.
 */
int Frame::getRoundScore(int round)
{
    int score;
    switch(round) {
    case 1:
        score = roundOne;
        break;
    case 2:
        score = roundTwo;
        break;
    case 3:
        score = roundThree;
        break;
    default:
        score = INVALID_ROUND;
        break;
    }
    return score;
}

/*
 * This allows outside entities to set the frame score,
 * in the case of bonuses earned from a stike or spare.
 */
void Frame::setFrameScore(int score) {
    frameScore = score;
}
