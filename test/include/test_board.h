#ifndef TEST_BOARD_H
#define TEST_BOARD_H

#include  "board.h"

void BoardCreateBeginingBoard_VariousPosition_ReturnsIsThere(const std::string &position, bool expected, char type = '\0');

void BoardToString_BeginingHumanWhite_ReturnsString();

void BoardToString_BeginingHumanBlack_ReturnsString();

void BoardToString_HumanBlackKingInPosition_ReturnsString();

void BoardToString_HumanBlackWhiteKingInPosition_ReturnsString();

void BoardGetState_AfterInit_ReturnsDefault();

#endif // TEST_BOARD_H
