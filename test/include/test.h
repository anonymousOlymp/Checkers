#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>

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

#define assertThrowsWithMessage(expression, type, message) \
    try { \
        expression; \
        std::cerr << __FUNC__ << " Assert fail: " #expression " not throws" << std::endl; \
        return; \
    } catch (type &exception) { \
        assertEquals(std::string(exception.what()), std::string(message)); \
    } catch (...) { \
        std::cerr << __FUNC__ << " Assert fail: " #expression " not throws " #type << std::endl; \
    }


#endif // TEST_H
