#include "cppc.h"
#include "gtest/gtest.h"
#include <thread>

TEST(mutex, one_after_other) {
    static cppc::mutex m;
    static int a = 0;

    m.lock();
    std::thread t2([&]() -> void {
        m.lock();
        a = 2;
        m.unlock();
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    a = 1;
    m.unlock();
    t2.join();

    ASSERT_EQ(a, 2);
}
