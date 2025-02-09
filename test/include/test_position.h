#ifndef TEST_POSITION_H
#define TEST_POSITION_H

#include "position.h"

#include <string>

void PositionFromString_VariousString_ReturnPosition(const std::string &string, bool expected);
void PositionEquality_VariousPosition_ReturnExpected(const std::string &first, const std::string &second, bool expected);

void MoveToDirection_DiagonalMove_ReturnExpected(const std::string &first, const std::string &second, Direction expected);

void MoveToDirection_StraightMove_ThrowsLogicError(const std::string &first, const std::string &second);

void PositionAdd_CorrectDirection_ReturnsExpectedPosition(const std::string &current, const std::string &expected, Direction direction);

void PositionAdd_IncorrectDirection_ThrowsLogicError(const std::string &current, Direction direction, const std::string &message);

void ApplyIfExists_VariousDirection_ReturnsExpected(const std::string &position,
                                                    Direction direction,
                                                    bool expected);

void Exists_VariousDirection_ReturnsExpected(const std::string &position,
                                             Direction direction,
                                             bool expected);

#endif // TEST_POSITION_H
