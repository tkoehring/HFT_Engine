#include <gtest/gtest.h>

#include "test_common.h"

namespace {

using namespace test;

TEST(Order, ConstructsAndReadsState) {
    const auto id = OrderId::from_uint64(100);
    const auto type = OrderType::Limit;
    const auto price = Price4::from_ticks(12345); // 1.2345 if Decimals=4
    const auto qty = Qty::from_units(10);
    const auto side = Side::Buy;

    const Order o{id, type, price, qty, side};

    EXPECT_TRUE(o.id == id);
    EXPECT_TRUE(o.type == type);
    EXPECT_TRUE(o.price == price);
    EXPECT_TRUE(o.quantity == qty);
    EXPECT_TRUE(o.side == side);

    EXPECT_FALSE(o.is_filled());
}

TEST(Order, ReduceDecreasesQuantity) {
    const Order order0{OrderId::from_uint64(1),
                       OrderType::Limit,
                       Price4::from_ticks(10000),
                       Qty::from_units(10),
                       Side::Sell};

    Order order1 = order0;
    EXPECT_EQ(order1.quantity.units(), 10u);
    EXPECT_FALSE(order1.is_filled());
    order1.reduce(Qty::from_units(3));
    EXPECT_EQ(order1.quantity.units(), 7u);
    EXPECT_FALSE(order1.is_filled());
}

TEST(Order, ReduceToZeroMarksFilled) {
    Order o{OrderId::from_uint64(1),
            OrderType::Limit,
            Price4::from_ticks(10000),
            Qty::from_units(5),
            Side::Sell};

    EXPECT_EQ(o.quantity.units(), 5u);
    EXPECT_FALSE(o.is_filled());
    o.reduce(Qty::from_units(5));
    EXPECT_EQ(o.quantity.units(), 0u);
    EXPECT_TRUE(o.is_filled());
}

TEST(Order, ComparisonDefaulted) {
    const Order a{OrderId::from_uint64(1),
                  OrderType::Limit,
                  Price4::from_ticks(10000),
                  Qty::from_units(5),
                  Side::Buy};

    const Order a2 = a;

    const Order b{OrderId::from_uint64(2),
                  OrderType::Limit,
                  Price4::from_ticks(10000),
                  Qty::from_units(5),
                  Side::Buy};

    EXPECT_TRUE(a == a2);
    EXPECT_FALSE(a != a2);

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
}

} // namespace
