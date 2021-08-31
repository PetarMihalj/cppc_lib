#include "cppc.h"
#include "gtest/gtest.h"
#include <chrono>
#include <random>
#include <thread>

namespace {

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1000, 2000);
std::atomic<int> cnt_unique;

void act_unique(cppc::mutex& m) {
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(
            std::chrono::microseconds(distribution(generator)));
        m.lock();
        cnt_unique++;

        ASSERT_EQ(cnt_unique, 1);
        std::this_thread::sleep_for(
            std::chrono::microseconds(distribution(generator)));
        ASSERT_EQ(cnt_unique, 1);
        std::this_thread::sleep_for(
            std::chrono::microseconds(distribution(generator)));
        ASSERT_EQ(cnt_unique, 1);

        cnt_unique--;
        m.unlock();
    }
}

} // namespace

TEST(mutex, random_probe) {
    generator = std::default_random_engine();
    cnt_unique = 0;
    cppc::mutex m{};
    // generator.seed(6);
    //
    std::vector<std::thread> t;
    for (int i = 0; i < 10; i++) {
        t.emplace_back([&]() { act_unique(m); });
    }

    for (auto &th : t)
        th.join();
    return;
}
