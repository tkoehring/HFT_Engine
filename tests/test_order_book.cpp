#include <gtest/gtest.h>
#include "test_common.h"

namespace {

using namespace test;

Order make_limit_order(uint64_t id, Side side, const char* price_str, uint64_t qty_units) {
    const auto price = Price4::parse(price_str);
    assert(price.has_value() && "test price not parsing");

    return Order{OrderId::from_uint64(id), OrderType::Limit, *price, Qty::from_units(qty_units), side};
}

TEST(OrderBookTest, EmptyBookHasNoBestBidOrAsk) {
    OrderBook book;

    EXPECT_TRUE(book.empty());
    EXPECT_EQ(book.best_bid(), std::nullopt);
    EXPECT_EQ(book.best_ask(), std::nullopt);
}

TEST(OrderBookTest, InsertSingleBuy) {
    OrderBook book;

    EXPECT_TRUE(book.empty());

    book.add_limit(make_limit_order(1, Side::Buy, "100.25", 10));

    EXPECT_FALSE(book.empty());

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(*book.best_bid(), *Price4::parse("100.25"));
    EXPECT_EQ(book.best_ask(), std::nullopt);
}

TEST(OrderBookTest, InsertSingleSell) {
    OrderBook book;

    EXPECT_TRUE(book.empty());

    book.add_limit(make_limit_order(1, Side::Sell, "101.50", 10));

    EXPECT_FALSE(book.empty());

    ASSERT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(*book.best_ask(), *Price4::parse("101.50"));
    EXPECT_EQ(book.best_bid(), std::nullopt);
}

TEST(OrderBookTest, InsertMultipleBuys) {
    OrderBook book;

    book.add_limit(make_limit_order(1, Side::Buy, "100.00", 10));
    book.add_limit(make_limit_order(2, Side::Buy, "101.00", 10));
    book.add_limit(make_limit_order(3, Side::Buy, "99.50", 10));

    EXPECT_FALSE(book.empty());

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(*book.best_bid(), *Price4::parse("101.00"));
    EXPECT_EQ(book.best_ask(), std::nullopt);
}

TEST(OrderBookTest, InsertMultipleSells) {
    OrderBook book;

    book.add_limit(make_limit_order(1, Side::Sell, "101.00", 10));
    book.add_limit(make_limit_order(2, Side::Sell, "100.50", 10));
    book.add_limit(make_limit_order(3, Side::Sell, "102.00", 10));

    EXPECT_FALSE(book.empty());

    ASSERT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(*book.best_ask(), *Price4::parse("100.50"));
    EXPECT_EQ(book.best_bid(), std::nullopt);
}

TEST(OrderBookTest, InsertMultipleBuysAndSells) {
    OrderBook book;

    book.add_limit(make_limit_order(1, Side::Buy, "100.00", 10));
    book.add_limit(make_limit_order(2, Side::Buy, "101.25", 10));
    book.add_limit(make_limit_order(3, Side::Sell, "102.00", 10));
    book.add_limit(make_limit_order(4, Side::Sell, "101.75", 10));

    EXPECT_FALSE(book.empty());

    ASSERT_TRUE(book.best_bid().has_value());
    ASSERT_TRUE(book.best_ask().has_value());

    EXPECT_EQ(*book.best_bid(), *Price4::parse("101.25"));
    EXPECT_EQ(*book.best_ask(), *Price4::parse("101.75"));
}

TEST(OrderBookTest, InsertMultipleSamePriceLevels) {
    OrderBook book;

    book.add_limit(make_limit_order(1, Side::Buy, "100.00", 10));
    book.add_limit(make_limit_order(2, Side::Buy, "100.00", 20));
    book.add_limit(make_limit_order(3, Side::Buy, "100.00", 30));

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(*book.best_bid(), *Price4::parse("100.00"));

    book.add_limit(make_limit_order(4, Side::Sell, "101.00", 10));
    book.add_limit(make_limit_order(5, Side::Sell, "101.00", 20));

    ASSERT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(*book.best_ask(), *Price4::parse("101.00"));
}

} // namespace