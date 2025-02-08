#ifndef TEST_H
#define TEST_H

#include <iostream>

#define assertEquals(a, b) \
    if ((a) != (b)) { \
        std::cerr << __FUNC__ << " Assert fail: " #a " == " #b ": " << (a) << " == " << (b) << std::endl; \
        return; \
    }

#define assertTrue(condition) \
    if (!(condition)) { \
        std::cerr << __FUNC__ << " Assert fail: " #condition " must be true" << std::endl; \
        return; \
    }

#define assertFalse(condition) \
    if ((condition)) { \
        std::cerr << __FUNC__ << " Assert fail: " #condition " must be false" << std::endl; \
        return; \
    }

#endif // TEST_H
