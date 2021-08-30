#include "cppc.h"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>
#include <random>

namespace {

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1000,2000);

std::atomic<int> cnt_unique;

cppc::mutex m;

void act_unique(){
    for (int i=0;i<10;i++){
        std::this_thread::sleep_for(std::chrono::microseconds(distribution(generator)));
        m.lock();
        cnt_unique++;

        ASSERT_EQ(cnt_unique,1);
        std::this_thread::sleep_for(std::chrono::microseconds(distribution(generator)));
        ASSERT_EQ(cnt_unique,1);
        std::this_thread::sleep_for(std::chrono::microseconds(distribution(generator)));
        ASSERT_EQ(cnt_unique,1);

        cnt_unique--;
        m.unlock();
    }
}

}

TEST(mutex, random_probe) {
    //generator.seed(6);
    //
    std::vector<std::thread> t;
    for (int i=0;i<10;i++){
        t.emplace_back([](){act_unique();});
    }

    for (auto& th : t) th.join();
    return;
}
