#pragma once

#include <matching/order.h>
#include <matching/order_id.h>
#include <matching/order_type.h>
#include <matching/order_book.h>
#include <matching/price.h>
#include <matching/qty.h>
#include <matching/side.h>

namespace test {

using matching::Order;
using matching::OrderId;
using matching::OrderType;
using matching::OrderBook;
using matching::Qty;
using matching::Side;

using Price4 = matching::Price<4>;

} // namespace test