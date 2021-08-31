#include "cppc.h"
#include "gtest/gtest.h"
#include <chrono>
#include <random>
#include <thread>

namespace {
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1000, 2000);
std::atomic<int> cnt_unique;
std::atomic<int> cnt_shared;

void act_unique(cppc::shared_mutex& sm) {
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(
            std::chrono::microseconds(distribution(generator)));
        sm.lock();
        cnt_unique++;

        ASSERT_EQ(cnt_shared, 0);
        ASSERT_EQ(cnt_unique, 1);
        std::this_thread::sleep_for(
            std::chrono::microseconds(distribution(generator)));
        ASSERT_EQ(cnt_shared, 0);
        ASSERT_EQ(cnt_unique, 1);
        std::this_thread::sleep_for(
            std::chrono::microseconds(distribution(generator)));
        ASSERT_EQ(cnt_shared, 0);
        ASSERT_EQ(cnt_unique, 1);

        cnt_unique--;
        sm.unlock();
    }
}

void act_shared(cppc::shared_mutex& sm) {
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(
            std::chrono::microseconds(distribution(generator)));
        sm.lock_shared();
        cnt_shared++;

        ASSERT_GT(cnt_shared, 0);
        ASSERT_EQ(cnt_unique, 0);
        std::this_thread::sleep_for(
            std::chrono::microseconds(distribution(generator)));
        ASSERT_GT(cnt_shared, 0);
        ASSERT_EQ(cnt_unique, 0);
        std::this_thread::sleep_for(
            std::chrono::microseconds(distribution(generator)));
        ASSERT_GT(cnt_shared, 0);
        ASSERT_EQ(cnt_unique, 0);

        cnt_shared--;
        sm.unlock_shared();
    }
}
} // namespace

TEST(shared_mutex, random_probe) {
    generator = std::default_random_engine();
    cnt_unique = 0;
    cnt_shared = 0;
    cppc::shared_mutex sm{};


    std::vector<std::thread> t;
    for (int i = 0; i < 10; i++) {
        t.emplace_back([&]() { act_shared(sm); });
        t.emplace_back([&]() { act_unique(sm); });
    }

    for (auto &th : t)
        th.join();
    return;
}
