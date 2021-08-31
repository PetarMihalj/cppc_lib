#include "cppc.h"
#include "gtest/gtest.h"
#include <thread>

TEST(barrier, release) {
    cppc::barrier b(10);
    std::vector<int> r;
    cppc::mutex m{};
    std::vector<std::thread *> tv;
    for (int i = 0; i < 5; i++) {
        tv.push_back(new std::thread([&]() -> void {
            b.wait();
            m.lock();
            r.push_back(2);
            m.unlock();
        }));
    }

    for (int i = 0; i < 5; i++) {
        tv.push_back(new std::thread([&]() -> void {
            m.lock();
            r.push_back(1);
            m.unlock();
            b.decrement_and_wait();
            m.lock();
            r.push_back(2);
            m.unlock();
        }));
        tv.push_back(new std::thread([&]() -> void {
            m.lock();
            r.push_back(1);
            m.unlock();
            b.decrement();
        }));
    }
    for (auto t : tv)
        t->join();

    for (int i = 0; i < 10; i++)
        ASSERT_EQ(r[i], 1);
    for (int i = 10; i < 20; i++)
        ASSERT_EQ(r[i], 2);
}
