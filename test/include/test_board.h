#ifndef TEST_BOARD_H
#define TEST_BOARD_H

#include  "board.h"

void BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere(const std::string &position, bool expected, char type = '\0');

void BoardToString_BeginingHumanWhite_ReturnsString();

void BoardToString_BeginingHumanBlack_ReturnsString();

void BoardToString_HumanBlackKingInPosition_ReturnsString();

void BoardToString_HumanBlackWhiteKingInPosition_ReturnsString();

void BoardGetState_AfterInit_ReturnsDefault();

void BoardProcessHumanCheckers_NoValues_NoResult(char human_side);

void BoardProcessHumanCheckers_OppositeValues_NoResult(char human_side);

void BoardProcessHumanCheckers_ManyValues_ResultHuman(char human_side);

void BoardProcessComputerCheckers_NoValues_NoResult(char human_side);

void BoardProcessComputerCheckers_OppositeValues_NoResult(char human_side);

void BoardProcessComputerCheckers_TrueValues_ProcessResult(char human_side);

#endif // TEST_BOARD_H
