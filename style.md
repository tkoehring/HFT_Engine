# Style Guide

## 1) Naming

### Types
- **PascalCase**: `Price`, `Qty`, `OrderBook`, `ReplayEngine`
- Strong IDs: `OrderId`, `InstrumentId`, `SeqNo`

### Constants
- **`k` prefix** for constants: `kScale`, `kDecimals`, `kMaxLevels`
- Prefer `static constexpr` (or `inline constexpr` in headers)

### Member variables
- **Trailing underscore**: `ticks_`, `side_`, `orders_`
- Avoid `m_` (don’t mix conventions)

### Functions
- **snake_case**: `to_string()`, `parse_price()`, `best_bid()`, `apply_event()`
- Accessors: `ticks()` not `get_ticks()` (unless a name collision forces it)

### Enums
- Use `enum class`
- Enumerators in PascalCase: `Side::Buy`, `Side::Sell`

### Namespaces
- `namespace matching { ... }`
- No `using namespace ...` in headers.

---

## 2) Files & Layout

### Headers
- Use **snake_case.hpp**: `order_book.hpp`, `price.hpp`, `primitives.hpp`
- Keep “aggregator” headers obvious: `primitives.hpp` (preferred over `types.hpp`)

### Sources
- Match header naming: `order_book.cpp`, `price.cpp` (only if needed)

### Tests
- `test_<thing>.cpp`: `test_price.cpp`, `test_order_book.cpp`
- Test cases use `SuiteName.CaseName` convention (GoogleTest)

---

## 3) Includes & Dependencies

### Headers must stay light
- No `<iostream>` in headers
- Avoid heavy includes (e.g. `<sstream>`) in headers
- Prefer forward declarations where reasonable

### .cpp files can include heavier headers
- Parsing/formatting that needs `<string>`/`<sstream>` belongs in `.cpp` or `codec/`

---

## 4) Safety & Correctness Defaults

- **No floating point** in core matching/book logic
- Prefer fixed-width integers: `int64_t`, `uint64_t`, etc.
- Use `std::string_view` for parsing inputs
- Use `[[nodiscard]]` on parse functions returning `optional/expected`
- Use `noexcept` on small pure helpers (accessors, `opposite(Side)`)
- Use assertions for invariants in debug builds; keep release fast

---

## 5) Formatting

- Use `clang-format` with a single repo-wide config
- 4-space indent (or follow the `.clang-format` exactly)
- Keep lines readable; avoid overly clever templates in hot paths unless justified

---

## 6) Layering Rule (Dependency Direction)

`primitives` → `events` → `order_book` → `replay tool`

Lower layers do not include higher layers.
Tests and tools may include anything.