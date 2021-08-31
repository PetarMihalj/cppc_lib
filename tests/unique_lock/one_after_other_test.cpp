#include "cppc.h"
#include "gtest/gtest.h"
#include <thread>

TEST(unique_lock, one_after_other) {
    static cppc::mutex m;
    static int a = 0;
    std::thread *t2;

    {
        cppc::unique_lock<cppc::mutex> ul(m);

        t2 = new std::thread([&]() -> void {
            cppc::unique_lock<cppc::mutex> ul(m);
            a = 2;
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        a = 1;
    }
    t2->join();
    ASSERT_EQ(a, 2);
}
