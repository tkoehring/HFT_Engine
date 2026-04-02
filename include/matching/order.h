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
    OrderId id;
    PriceT price;
    Qty quantity;
    OrderType type;
    Side side;

    constexpr Order(OrderId id, OrderType type, PriceT price, Qty quantity, Side side) noexcept
        : id(id), type(type), price(price), quantity(quantity), side(side) {
        assert(quantity.units() > 0 && "Order quantity must be positive");
        assert(price.ticks() > 0 && "Order price must be positive");
    }

    friend constexpr auto operator<=>(const Order&, const Order&) noexcept = default;

    constexpr void reduce(Qty filled) noexcept {
        assert(filled.units() <= quantity.units() && "Filled quantity cannot exceed order quantity");
        quantity -= filled;
    }

    constexpr bool is_filled() const noexcept { return quantity.units() == 0; }
};

} // namespace matching