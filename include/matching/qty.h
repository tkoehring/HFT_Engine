#pragma once

#include <cstdint>
#include <cassert>
#include <compare>
#include <limits>
#include <type_traits>

namespace matching {
	struct Qty {		
	private:
		uint64_t units_;
		constexpr explicit Qty(uint64_t units) noexcept : units_(units) {}

	public:
		static constexpr Qty from_units(uint64_t u) noexcept { return Qty{ u }; }
		constexpr uint64_t units() const noexcept { return units_; }

		friend constexpr auto operator<=>(const Qty&, const Qty&) noexcept = default;

		friend constexpr Qty operator+(Qty a, Qty b) noexcept {
			assert(a.units_ <= std::numeric_limits<uint64_t>::max() - b.units_ && "Qty overflow");
			return Qty{ a.units_ + b.units_ };
		}

		friend constexpr Qty operator-(Qty a, Qty b) noexcept {
			assert(a.units_ >= b.units_ && "Qty underflow");
			return Qty{ a.units_ - b.units_ };
		}

		constexpr Qty& operator+=(Qty other) noexcept {
			assert(units_ <= std::numeric_limits<uint64_t>::max() - other.units_ && "Qty overflow");
			units_ += other.units_;
			return *this;
		}

		constexpr Qty& operator-=(Qty other) noexcept {
			assert(units_ >= other.units_ && "Qty underflow");
			units_ -= other.units_;
			return *this;
		}
	};

	static_assert(std::is_trivially_copyable_v<Qty>);
	static_assert(std::is_standard_layout_v<Qty>);
}