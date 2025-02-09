#include "test_checker.h"

#include "checker.h"
#include "test.h"

void CheckerToChar_VariousChecker_ReturnsExpected(char side, bool is_king,
                                                  char expected) {
    Checker c(side);
    if (is_king) {
        c.set_king();
    }

    char symbol = static_cast<char>(c);

    assertEquals(symbol, expected);
}
