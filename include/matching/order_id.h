#pragma once

#include <compare>
#include <cstdint>
#include <functional>

namespace matching {

struct OrderId {
private:
    uint64_t id_;
    constexpr explicit OrderId(uint64_t id) noexcept : id_(id) {}

public:
    constexpr static OrderId from_uint64(uint64_t id) noexcept { return OrderId{id}; }
    constexpr uint64_t id() const noexcept { return id_; }
    friend constexpr auto operator<=>(const OrderId&, const OrderId&) noexcept = default;
};
} // namespace matching

namespace std {
template <>
struct hash<matching::OrderId> {
    size_t operator()(const matching::OrderId& order_id) const noexcept {
        return hash<uint64_t>{}(order_id.id());
    }
};

} // namespace std