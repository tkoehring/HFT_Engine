#pragma once

#include <cassert>
#include <compare>
#include <matching/order_id.h>
#include <matching/order_type.h>
#include <matching/qty.h>
#include <matching/side.h>
#include <matching/types.h>
#include <type_traits>

namespace matching {
struct Order {
    OrderId id_;
    PriceT price_;
    Qty quantity_;
    OrderType type_;
    Side side_;

    constexpr Order(OrderId id, OrderType type, PriceT price, Qty quantity, Side side) noexcept
        : id_(id), type_(type), price_(price), quantity_(quantity), side_(side) {
        assert(quantity.units() > 0 && "Order quantity must be positive");
        assert(price.ticks() > 0 && "Order price must be positive");
    }

    friend constexpr auto operator<=>(const Order&, const Order&) noexcept = default;

    constexpr void reduce(Qty filled) noexcept {
        assert(filled.units() <= quantity_.units() && "Filled quantity cannot exceed order quantity");
        quantity_ -= filled;
    }

    constexpr bool is_filled() const noexcept { return quantity_.units() == 0; }
};
} // namespace matching