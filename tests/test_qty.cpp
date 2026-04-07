#include <gtest/gtest.h>

#include "test_common.h"

namespace {

using namespace test;

TEST(Qty, FromUnitsFactory) {
    auto q = Qty::from_units(100);
    EXPECT_EQ(q.units(), 100);
}

TEST(Qty, Addition) {
    auto a = Qty::from_units(50);
    auto b = Qty::from_units(25);

    auto c = a + b;
    EXPECT_EQ(c.units(), 75);
}

TEST(Qty, Subtraction) {
    auto a = Qty::from_units(50);
    auto b = Qty::from_units(25);

    auto c = a - b;
    EXPECT_EQ(c.units(), 25);
}

TEST(Qty, OrderingWorks) {
    auto a = Qty::from_units(10);
    auto b = Qty::from_units(20);

    EXPECT_LT(a, b);
    EXPECT_GT(b, a);
    EXPECT_EQ(a, a);
}

} // namespace
