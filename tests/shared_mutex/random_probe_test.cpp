#include "cppc.h"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>
#include <random>


static std::default_random_engine generator;
static std::uniform_int_distribution<int> distribution(10,20);

static std::atomic<int> cnt_unique;
static std::atomic<int> cnt_shared;

static cppc::shared_mutex sm;

void act_unique(){
    for (int i=0;i<10;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(distribution(generator)));
        sm.lock();
        cnt_unique++;

        ASSERT_EQ(cnt_shared,0);
        ASSERT_EQ(cnt_unique,1);

        cnt_unique--;
        sm.unlock();
    }
}

void act_shared(){
    for (int i=0;i<10;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(distribution(generator)));
        sm.lock_shared();
        cnt_shared++;

        ASSERT_GT(cnt_shared,0);
        ASSERT_EQ(cnt_unique,0);

        cnt_shared--;
        sm.unlock_shared();
    }
}

TEST(shared_mutex, random_probe) {
    //generator.seed(6);
    //
    std::vector<std::thread> t;
    for (int i=0;i<10;i++){
        t.emplace_back([](){act_shared();});
        t.emplace_back([](){act_unique();});
    }

    for (auto& th : t) th.join();
    return;
}
