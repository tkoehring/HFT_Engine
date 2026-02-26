#include <gtest/gtest.h>
#include <matching/order_id.h>

TEST(OrderId, FromUint64Factory) {
    const auto temp = matching::OrderId::from_uint64(42);
    EXPECT_EQ(temp.id(), 42u);
}

TEST(OrderId, Comparison) {
    const auto a = matching::OrderId::from_uint64(1);
    const auto b = matching::OrderId::from_uint64(2);
    const auto c = matching::OrderId::from_uint64(1);

    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a < b);
}