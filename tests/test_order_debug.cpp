#include <gtest/gtest.h>
#include <matching/order.h>

using Price4 = matching::Price<4>;

TEST(OrderDeathTest, ReduceCannotOverfill) {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    matching::Order o{matching::OrderId::from_uint64(1),
                      matching::OrderType::Limit,
                      Price4::from_ticks(10000),
                      matching::Qty::from_units(5),
                      matching::Side::Buy};

    EXPECT_DEATH(o.reduce(matching::Qty::from_units(6)), ".*");
}