#pragma once

#include <cassert>
#include <type_traits>
#include <compare>

#include <matching/order_id.h>
#include <matching/order_type.h>
#include <matching/price.h>
#include <matching/qty.h>
#include <matching/side.h>

namespace matching {
	struct Order {
		OrderId id;
		Price<4> price;
		Qty quantity;
		OrderType type;
		Side side;

		constexpr Order(OrderId id, Price<4> price, Qty quantity, Side side) noexcept
			: id(id), price(price), quantity(quantity), side(side) {
			assert(quantity.units() > 0 && "Order quantity must be positive");
			assert(price.ticks() > 0 && "Order price must be positive");
		}

		friend constexpr auto operator<=>(const Order&, const Order&) noexcept = default;

		constexpr void reduce(Qty filled) noexcept {
			assert(filled.units() <= quantity.units() && "Filled quantity cannot exceed order quantity");
			quantity -= filled;
		}

		constexpr bool is_filled() const noexcept {
			return quantity.units() == 0;
		}
	};

	static_assert(std::is_trivially_copyable_v<Order>);
	static_assert(std::is_standard_layout_v<Order>);
}