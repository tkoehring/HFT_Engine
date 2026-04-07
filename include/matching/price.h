#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
// #include <cassert>
#include <string_view>
// #include <string>
#include <compare>
#include <limits>
#include <type_traits>

// Example usage:
// using Price4 = Price<4>;
// Gives a Price object with 4 decimals, i.e. 1.2345 will be represented as 12345 in ticks_

namespace matching {

template <int Decimals>
struct Price {
    static_assert(Decimals >= 0 && Decimals <= 9, "Price<Decimals>: Decimals must be between 0 and 9");

private:
    int64_t ticks_;
    constexpr explicit Price(int64_t ticks) noexcept : ticks_(ticks) {}

public:
    static constexpr int kDecimals = Decimals;

    static constexpr int64_t kScale = [] {
        int64_t v = 1;
        for (int i = 0; i < Decimals; ++i)
            v *= 10;
        return v;
    }();

    static constexpr Price from_ticks(int64_t ticks) noexcept { return Price{ticks}; }

    friend constexpr auto operator<=>(const Price&, const Price&) noexcept = default;

    constexpr int64_t ticks() const noexcept { return ticks_; }

    // std::string to_string() const;

    [[nodiscard("Must check Price::parse result")]]
    static std::optional<Price> parse(std::string_view str) noexcept {
        int64_t p = 0;
        std::size_t pos = 0;
        bool seenDot = false;
        bool neg = false;
        int fractionalDigits = 0;
        int digitCount = 0;

        if (str.empty()) {
            return std::nullopt;
        }

        if ((str[0] < '0' || str[0] > '9') && str[0] != '-' && str[0] != '+') {
            return std::nullopt;
        }

        if (str[0] == '-') {
            neg = true;
            pos++;
        } else if (str[0] == '+') {
            pos++;
        }

        if (pos == str.size()) {
            return std::nullopt;
        }

        for (; pos < str.size(); pos++) {
            char c = str[pos];

            if (c == '.') {
                if (seenDot) {
                    return std::nullopt;
                }

                if (digitCount == 0) {
                    return std::nullopt;
                }

                if (pos + 1 == str.size()) {
                    return std::nullopt;
                }

                seenDot = true;
                continue;
            }

            if (c < '0' || c > '9') {
                return std::nullopt;
            }

            int digit = c - '0';
            digitCount++;

            if (seenDot) {
                if (fractionalDigits >= Decimals) {
                    return std::nullopt;
                }

                fractionalDigits++;
            }

            if (p > (std::numeric_limits<int64_t>::max() - digit) / 10) {
                return std::nullopt;
            }

            p = p * 10 + digit;
        }

        for (; fractionalDigits < Decimals; fractionalDigits++) {
            if (p > std::numeric_limits<int64_t>::max() / 10) {
                return std::nullopt;
            }

            p *= 10;
        }

        if (neg) {
            p = -p;
        }

        return Price<Decimals>::from_ticks(p);
    }
};

} // namespace matching