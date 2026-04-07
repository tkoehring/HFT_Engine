#include <cassert>

#include <matching/order_book.h>

namespace matching {

OrderBook::Level& OrderBook::get_level(Side side, PriceT price) {
    if (side == Side::Buy) {
        return bids_[price];
    }

    return asks_[price];
}

void OrderBook::add_limit(const Order& o) {
    assert(o.quantity.units() > 0 && "add_limit requires quantity > 0");
    assert(order_map.find(o.id) == order_map.end() && "duplicate OrderId in add_limit");

    auto& book = get_level(o.side, o.price);

    book.push_back({o.id, o.quantity});

    order_map.emplace(o.id, std::pair{o.side, o.price});
}

std::optional<PriceT> OrderBook::best_bid() const {

    if (bids_.empty()) {
        return std::nullopt;
    }

    return bids_.begin()->first;
}
std::optional<PriceT> OrderBook::best_ask() const {
    if (asks_.empty()) {
        return std::nullopt;
    }

    return asks_.begin()->first;
}

bool OrderBook::empty() const {
    return bids_.empty() && asks_.empty();
}

} // namespace matching