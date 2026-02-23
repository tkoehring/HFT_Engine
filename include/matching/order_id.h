#pragma once

#include <cstdint>
#include <compare>

namespace matching
{
	struct OrderId {
	private:
		uint64_t id_;
		constexpr explicit OrderId(uint64_t id) noexcept : id_(id) {}

	public:
		constexpr static OrderId from_uint64(uint64_t id) noexcept { return OrderId{ id }; }
		constexpr uint64_t id() const noexcept { return id_; }
		friend constexpr auto operator<=>(const OrderId&, const OrderId&) noexcept = default;
	};
}