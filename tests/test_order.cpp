#include <gtest/gtest.h>
#include <matching/order.h>
#include <matching/order_id.h>
#include <matching/order_type.h>
#include <matching/price.h>
#include <matching/qty.h>
#include <matching/side.h>

namespace {
using Price4 = matching::Price<4>;
}

TEST(Order, ConstructsAndReadsState) {
    const auto id = matching::OrderId::from_uint64(100);
    const auto type = matching::OrderType::Limit;
    const auto price = Price4::from_ticks(12345); // 1.2345 if Decimals=4
    const auto qty = matching::Qty::from_units(10);
    const auto side = matching::Side::Buy;

    const matching::Order o{id, type, price, qty, side};

    EXPECT_TRUE(o.id_ == id);
    EXPECT_TRUE(o.type_ == type);
    EXPECT_TRUE(o.price_ == price);
    EXPECT_TRUE(o.quantity_ == qty);
    EXPECT_TRUE(o.side_ == side);

    EXPECT_FALSE(o.is_filled());
}

TEST(Order, ReduceDecreasesQuantity) {
    const matching::Order order0{matching::OrderId::from_uint64(1),
                                 matching::OrderType::Limit,
                                 Price4::from_ticks(10000),
                                 matching::Qty::from_units(10),
                                 matching::Side::Sell};

    matching::Order order1 = order0;
    EXPECT_EQ(order1.quantity_.units(), 10u);
    EXPECT_FALSE(order1.is_filled());
    order1.reduce(matching::Qty::from_units(3));
    EXPECT_EQ(order1.quantity_.units(), 7u);
    EXPECT_FALSE(order1.is_filled());
}

TEST(Order, ReduceToZeroMarksFilled) {
    matching::Order o{matching::OrderId::from_uint64(1),
                      matching::OrderType::Limit,
                      Price4::from_ticks(10000),
                      matching::Qty::from_units(5),
                      matching::Side::Sell};

    EXPECT_EQ(o.quantity_.units(), 5u);
    EXPECT_FALSE(o.is_filled());
    o.reduce(matching::Qty::from_units(5));
    EXPECT_EQ(o.quantity_.units(), 0u);
    EXPECT_TRUE(o.is_filled());
}

TEST(Order, ComparisonDefaulted) {
    const matching::Order a{matching::OrderId::from_uint64(1),
                            matching::OrderType::Limit,
                            Price4::from_ticks(10000),
                            matching::Qty::from_units(5),
                            matching::Side::Buy};

    const matching::Order a2 = a;

    const matching::Order b{matching::OrderId::from_uint64(2),
                            matching::OrderType::Limit,
                            Price4::from_ticks(10000),
                            matching::Qty::from_units(5),
                            matching::Side::Buy};

    EXPECT_TRUE(a == a2);
    EXPECT_FALSE(a != a2);

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
}