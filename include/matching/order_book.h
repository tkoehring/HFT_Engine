#pragma once

#include <deque>
#include <functional>
#include <map>
#include <optional>
#include <unordered_map>

#include <matching/config.h>
#include <matching/order.h>

namespace matching {

class OrderBook {
private:
    struct OrderNode {
        OrderId order_id_;
        Qty qty_remaining_;
    };

    using Level = std::deque<OrderNode>;

    std::map<PriceT, Level> asks_;
    std::map<PriceT, Level, std::greater<>> bids_;
    std::unordered_map<OrderId, std::pair<Side, PriceT>> order_map;

    void assert_invariants() const;

    Level& get_level(Side side, PriceT price);

public:
    void add_limit(const Order& o);
    bool cancel_order(const OrderId order_id);
    std::optional<PriceT> best_bid() const;
    std::optional<PriceT> best_ask() const;

    bool empty() const;
};

} // namespace matching