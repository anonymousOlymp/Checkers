#include "test_position.h"

#include <stdexcept>

#include "position.h"
#include "test.h"

void PositionFromString_VariousString_ReturnPosition(const std::string &string,
                                                     bool expected) {
    Position position = Position::from_string(string);

    assertEquals(position, expected);
}

void PositionEquality_VariousPosition_ReturnExpected(const std::string &first,
                                                     const std::string &second,
                                                     bool expected) {
    Position f = Position::from_string(first);
    Position s = Position::from_string(second);

    bool result = (f == s);

    assertEquals(result, expected);
}

void MoveToDirection_DiagonalMove_ReturnExpected(const std::string &first,
                                                 const std::string &second,
                                                 Direction expected) {
    Position f = Position::from_string(first);
    Position s = Position::from_string(second);
    Move move(f, s);

    Direction casted = move;

    assertEquals(static_cast<int>(casted), static_cast<int>(expected));
}

void MoveToDirection_StraightMove_ThrowsLogicError(const std::string &first,
                                                   const std::string &second) {
    Position f = Position::from_string(first);
    Position s = Position::from_string(second);
    Move move(f, s);

    assertThrowsWithMessage((void)static_cast<Direction>(move),
                            std::logic_error,
                            "Error. Some coordinates are equal!");
}

void PositionAdd_CorrectDirection_ReturnsExpectedPosition(
    const std::string &current, const std::string &expected,
    Direction direction) {
    Position c = Position::from_string(current);
    Position e = Position::from_string(expected);

    Position n = c + direction;

    assertEquals(n, e);
}

void PositionAdd_IncorrectDirection_ThrowsLogicError(
    const std::string &current, Direction direction,
    const std::string &message) {
    Position c = Position::from_string(current);

    assertThrowsWithMessage(c + direction, std::logic_error, message);
}

void ApplyIfExists_VariousDirection_ReturnsExpected(const std::string &position,
                                                    Direction direction,
                                                    bool expected) {
    Position p = Position::from_string(position);

    bool first_result = false;
    bool second_result = apply_if_exists(
        p, direction, [&first_result](Position p) { first_result = true; });
    assertEquals(first_result, expected);
    assertEquals(second_result, expected);
}

void Exists_VariousDirection_ReturnsExpected(const std::string &position,
                                             Direction direction,
                                             bool expected) {
    Position p = Position::from_string(position);

    bool result = exists(p, direction);
    assertEquals(result, expected);
}
