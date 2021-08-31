#include "cppc.h"
#include "gtest/gtest.h"
#include <thread>

TEST(shared_mutex, one_after_other) {
    static cppc::shared_mutex sm;
    static int a = 0;

    sm.lock();
    std::thread t2([&]() -> void {
        sm.lock_shared();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        a = 2;
        sm.unlock_shared();
    });
    std::thread t3([&]() -> void {
        sm.lock_shared();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sm.unlock_shared();

        sm.lock();
        a = 3;
        sm.unlock();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    a = 1;
    sm.unlock();

    t2.join();
    t3.join();

    ASSERT_EQ(a, 3);
}
