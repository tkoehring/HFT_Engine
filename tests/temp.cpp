 #include <matching/qty.h>
#include <gtest/gtest.h>

TEST(FormatTest, BadFormatting) {

    auto       q = matching::Qty::from_units(10);

    if (q.units() == 10) {
        EXPECT_TRUE(true);
    } else {
        EXPECT_TRUE(false);
    }

    for ( int i = 0; i < 5; i++) {
        EXPECT_EQ(i, i);
    }
}