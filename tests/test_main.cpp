#include <gtest/gtest.h>
#include <iostream>

class BannerListener : public ::testing::EmptyTestEventListener {
public:
    void OnTestSuiteStart(const ::testing::TestSuite& suite) override {
        std::cout << "\033[33m" << "\n===== Starting Test Suite: " << suite.name() << " =====\n" << "\033[0m";
    }

    /*void OnTestSuiteEnd(const ::testing::TestSuite& suite) override {
        std::cout << "\033[33m" << "===== Finished Test Suite: " << suite.name()
             << " (failed=" << suite.failed_test_count() << ") =====\n\n" << "\033[0m";
    }*/
};

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    auto& listeners = ::testing::UnitTest::GetInstance()->listeners();
    auto* default_printer = listeners.Release(listeners.default_result_printer());
    listeners.Append(default_printer);
    listeners.Append(new BannerListener);
    return RUN_ALL_TESTS();
}