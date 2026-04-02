#pragma once

#include <cstdint>
#include <optional>

namespace matching {

enum class Side : uint8_t { Buy = 0, Sell = 1 };

constexpr Side opposite(Side s) noexcept {
    assert((s == Side::Buy || s == Side::Sell) && "Side::opposite param must be Buy or Sell");
    return s == Side::Buy ? Side::Sell : Side::Buy;
}

constexpr char to_char(Side s) noexcept {
    assert((s == Side::Buy || s == Side::Sell) && "Side::to_char param must be Buy or Sell");
    return s == Side::Buy ? 'B' : 'S';
}

[[nodiscard("Must check Side::from_char result")]]
constexpr std::optional<Side> from_char(char c) noexcept {

    if (c == 'B' || c == 'b')
        return Side::Buy;
    if (c == 'S' || c == 's')
        return Side::Sell;
    return std::nullopt;
}

} // namespace matching