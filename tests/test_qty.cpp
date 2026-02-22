#include <gtest/gtest.h>
#include <matching/qty.h>

namespace {

    using matching::Qty;

    TEST(QtyBasic, Construction) {
        auto q = Qty::from_units(100);
        EXPECT_EQ(q.units(), 100);
    }

    TEST(QtyArithmetic, Addition) {
        auto a = Qty::from_units(50);
        auto b = Qty::from_units(25);

        auto c = a + b;
        EXPECT_EQ(c.units(), 75);
    }

    TEST(QtyArithmetic, Subtraction) {
        auto a = Qty::from_units(50);
        auto b = Qty::from_units(25);

        auto c = a - b;
        EXPECT_EQ(c.units(), 25);
    }

    TEST(QtyComparison, OrderingWorks) {
        auto a = Qty::from_units(10);
        auto b = Qty::from_units(20);

        EXPECT_LT(a, b);
        EXPECT_GT(b, a);
        EXPECT_EQ(a, a);
    }
}
