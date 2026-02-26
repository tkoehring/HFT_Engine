#include <cstdint>
#include <gtest/gtest.h>
#include <matching/price.h>
#include <string>

using P = matching::Price<4>;

struct InvalidParseData {
    const char* name;
    const char* input;
};

// Fixture
class PriceParseInvalid : public ::testing::TestWithParam<InvalidParseData> {};

// Test for invalid inputs
TEST_P(PriceParseInvalid, Invalid) {
    const auto& tc = GetParam();
    EXPECT_FALSE(P::parse(tc.input).has_value()) << "ERROR: Expected no value. "
                                                 << "Input: " << tc.input;
}

static std::string InvalidParseTestName(const ::testing::TestParamInfo<InvalidParseData>& info) {
    return info.param.name;
}

INSTANTIATE_TEST_SUITE_P(PriceParse,
                         PriceParseInvalid,
                         ::testing::Values(InvalidParseData{"LeadingDot", ".1"},
                                           InvalidParseData{"TrailingDot", "1."},
                                           InvalidParseData{"MultipleDots", "1..2"},
                                           InvalidParseData{"TooManyDecimals", "1.23456"},
                                           InvalidParseData{"NonDigit", "12a"},
                                           InvalidParseData{"Empty", ""}),
                         InvalidParseTestName);

struct ValidParseData {
    const char* name;
    const char* input;
    int64_t expectedTicks;
};

// Fixture
class PriceParseValid : public ::testing::TestWithParam<ValidParseData> {};

// Test for valid inputs
TEST_P(PriceParseValid, Valid) {
    const auto& tc = GetParam();
    auto p = P::parse(tc.input);

    // Assert true before accessing p->ticks() to avoid dereferencing nullopt
    ASSERT_TRUE(p.has_value()) << "ERROR: Expected value. "
                               << "Input: " << tc.input;
    EXPECT_EQ(p->ticks(), tc.expectedTicks)
        << "ERROR: Expected matching ticks. "
        << "Parsed Ticks: " << p->ticks() << " Expected Ticks: " << tc.expectedTicks;
}

static std::string ValidParseTestName(const ::testing::TestParamInfo<ValidParseData>& info) {
    return info.param.name;
}

INSTANTIATE_TEST_SUITE_P(PriceParse,
                         PriceParseValid,
                         ::testing::Values(ValidParseData{"ParsesInteger", "123", 1230000},
                                           ValidParseData{"ParsesFractional", "123.4", 1234000},
                                           ValidParseData{"PadsFractionalDigits", "1.23", 12300}),
                         ValidParseTestName);
