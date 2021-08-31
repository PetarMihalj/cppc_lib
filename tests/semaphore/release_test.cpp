#include "cppc.h"
#include "gtest/gtest.h"
#include <thread>

TEST(semaphore, release) {
    static cppc::semaphore s;
    static std::vector<std::thread*> tv;
    static std::atomic<int> a;

    a=0;
    for (int i=0;i<10;i++){
        tv.push_back(new std::thread([&](){
            s.put(2);
        }));
        tv.push_back(new std::thread([&](){
            s.get();
            a++;
        }));
        tv.push_back(new std::thread([&](){
            s.get();
            a++;
        }));
    }
    for (auto t: tv)
        t->join();

    ASSERT_EQ(a,20);
}
