#include "cppc.h"
#include "gtest/gtest.h"
#include <thread>

TEST(unique_lock, one_after_other_sm) {
    cppc::shared_mutex sm{};
    int a = 0;
    std::thread *t2;

    {
        cppc::unique_lock<cppc::shared_mutex> ul(sm);

        t2 = new std::thread([&]() -> void {
            cppc::unique_lock<cppc::shared_mutex> ul(sm);
            a = 2;
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        a = 1;
    }
    t2->join();
    ASSERT_EQ(a, 2);
}
