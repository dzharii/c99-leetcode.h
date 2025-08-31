#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#include "external/doctest/doctest.h"

#include <cstring>
#include <cstdlib>
#include <string>

#define C99_LEETCODE_IMPLEMENTATION
#include "c99-leetcode.h"

TEST_CASE("c99lc_version returns expected semantic version") {
    CHECK(std::strcmp(c99lc_version(), "0.1") == 0);
}