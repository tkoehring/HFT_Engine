#include <matching/order.h>
#include <matching/order_id.h>
#include <matching/price.h>
#include <matching/qty.h>
#include <matching/side.h>
#include <type_traits>

// ABI/layout contracts (compile-time)
static_assert(std::is_trivially_copyable_v<matching::Qty>);
static_assert(std::is_standard_layout_v<matching::Qty>);

static_assert(std::is_trivially_copyable_v<matching::OrderId>);
static_assert(std::is_standard_layout_v<matching::OrderId>);

static_assert(std::is_enum_v<matching::OrderType>);
static_assert(static_cast<int>(matching::OrderType::Limit) == 0);
static_assert(static_cast<int>(matching::OrderType::Market) == 1);

static_assert(std::is_trivially_copyable_v<matching::Price<4>>);
static_assert(std::is_standard_layout_v<matching::Price<4>>);

// NOTE: Order may not be trivially copyable if it has a user-declared ctor.
// Keep standard-layout if that’s your intent; drop trivially-copyable if it fails.
static_assert(std::is_standard_layout_v<matching::Order>);