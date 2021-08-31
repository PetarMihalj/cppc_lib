#include "cppc.h"
#include "gtest/gtest.h"
#include <thread>

TEST(shared_lock, one_after_other) {
    static cppc::shared_mutex sm;
    static int a = 0;
    std::thread *t2;

    {
        cppc::shared_lock<cppc::shared_mutex> sl(sm);

        t2 = new std::thread([&]() -> void {
            cppc::shared_lock<cppc::shared_mutex> sl(sm);
            a = 2;
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        a = 1;
        t2->join();
    }
    ASSERT_EQ(a, 1);
}
