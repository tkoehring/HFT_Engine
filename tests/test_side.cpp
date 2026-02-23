#include <gtest/gtest.h>
#include <matching/side.h>

namespace {

    using matching::Side;

    TEST(Side, OppositeWorks) {
        EXPECT_EQ(matching::opposite(Side::Buy), Side::Sell);
        EXPECT_EQ(matching::opposite(Side::Sell), Side::Buy);
    }

    TEST(Side, ToChar) {
        EXPECT_EQ(matching::to_char(Side::Buy), 'B');
        EXPECT_EQ(matching::to_char(Side::Sell), 'S');
    }

    TEST(Side, FromCharValid) {
        auto s = matching::from_char('B');
        ASSERT_TRUE(s.has_value());
        EXPECT_EQ(*s, Side::Buy);
    }

    TEST(Side, FromCharInvalid) {
        EXPECT_FALSE(matching::from_char('X').has_value());
    }
}