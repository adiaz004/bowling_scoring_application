#include "frame.h"
#include "common.h"

/**
 * @brief Frame::Frame
 * creates a new frame
 * @param frameNumber represents the frame number for this instance.
 */
Frame::Frame(int frameNumber)
{
    frame = frameNumber;
    resetFrame();
}

/**
 * @brief Frame::~Frame
 */
Frame::~Frame()
{
    delete this;
}

/**
 * @brief Frame::frameStarted
 * trackes whether or not the frame has started.
 * @return
 */
bool Frame::frameStarted()
{
    return frameHasStarted;
}

/**
 * @brief Frame::recordRound
 * record a score for the next round.
 * @param score score to record.
 */
int Frame::recordRound(int score)
{
    if (!frameHasStarted) {
       frameHasStarted = true;
    }
    if (frameComplete) {
        return SUCCESS;
    }

    if (frame < 9) {
        return recordFirstNineRounds(score);
    } else {
        return recordTenthRound(score);
    }
}

/**
 * @brief Frame::recordFirstNineRounds
 * handles the score logic for each of the first 9 frames.
 * @param score to record
 */
int Frame::recordFirstNineRounds(int score)
{
    int result = SUCCESS;
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
    } else if (currentRound == 2 && (score + roundOne) > 10) {
        result = FAILURE;
    } else {
        frameScore += score;
        if (currentRound == 1) {
            roundOne = score;
        } else if (currentRound == 2) {
            roundTwo = score;
            frameComplete = true;

        } else {
            frameComplete = true;
        }
    }

    /* new score means new roll, increase round */
    if (result == SUCCESS)
        currentRound++;
    return result;
}

/**
 * @brief Frame::recordTenthRound
 * records the score for the tenth frame as it operates a bit different then
 * the first nine frame.
 * @param score score to record
 */
int Frame::recordTenthRound(int score)
{
    int result = SUCCESS;
    if (currentRound == 1) {
        /* rolling a 10 on the first round means a strike */
        if (score == 10) {
            isStrike = true;
        }
        currentRound++;
        roundOne = score;
        frameScore += score;
    } else if (currentRound == 2) {
        if (!isStrike && (score + roundOne) > 10) {
            result = FAILURE;
        }
        /* if we're not a stike and rolled a spare, keep frame open. */
        if (!isStrike && (frameScore + score) == 10) {
            isSpare = true;
            roundTwo = SPARE;
        } else {
            /* else we didn't roll a spare, so close out frame */
            if (score != 10) {
                frameComplete = true;
            }
            roundTwo = score;
        }

        frameScore += score;
        currentRound++;
    } else if (currentRound == 3) {
        /* rolling a spare or stike in the first round gets us a third round */
        frameScore += score;
        roundThree = score;
        frameComplete = true;
    }
    return result;
}

/**
 * @brief Frame::isFrameComplete
 * returns whether or not this Frame is complete.
 * @return true if frame is complete, otherwise false.
 */
bool Frame::isFrameComplete()
{
    return frameComplete;
}

/**
 * @brief Frame::resetFrame
 * resets frame values to default
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

/**
 * @brief Frame::addBonus
 * adds the bonus score to this frame.
 * @param bonusScore
 */
void Frame::addBonus(int bonusScore)
{
    if (bonus > 0) {
        frameScore += bonusScore;
        bonus--;
    }
}

/**
 * @brief Frame::getRemainingBonus
 * @return the number of remaining bonuses.
 */
int Frame::getRemainingBonus()
{
    return bonus;
}

/**
 * @brief Frame::getFrameScore
 * returns the current frame score.
 * @return
 */
int Frame::getFrameScore() {
    if (frameComplete && bonus == 0){
        return frameScore;
    }
    return INVALID_ROUND;
}

/**
 * @brief Frame::getRoundScore
 * returns the score for the requested round.
 * @param round requested round
 * @return
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
