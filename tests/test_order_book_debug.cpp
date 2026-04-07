#include <gtest/gtest.h>

#include "test_common.h"

namespace {

using namespace test;

Order make_limit_order(uint64_t id, Side side, const char* price_str, uint64_t qty_units) {
    const auto price = Price4::parse(price_str);
    assert(price.has_value() && "test price not parsing");

    return Order{OrderId::from_uint64(id), OrderType::Limit, *price, Qty::from_units(qty_units), side};
}
TEST(OrderBookDeathTest, DuplicateOrderIdTriggersAssert) {
    OrderBook book;

    const auto o1 = make_limit_order(42, Side::Buy, "100.00", 10);
    const auto o2 = make_limit_order(42, Side::Sell, "101.00", 20);

    book.add_limit(o1);
    EXPECT_DEATH(book.add_limit(o2), "duplicate OrderId in add_limit");
}

} // namespace