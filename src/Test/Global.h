#pragma once
#include <stdexcept>

namespace test {

#define NAME "test"

enum pm { t1, t2, t3 };

void testManager();

void testCore();

void testRegister();

inline void falseThrow(bool isFalse) {
    if (!isFalse) {
        std::runtime_error("API test failed, Please use the debugger to check the error");
    }
}

} // namespace test