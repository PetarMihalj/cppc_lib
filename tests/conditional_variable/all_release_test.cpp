#include "cppc.h"
#include "gtest/gtest.h"
#include <thread>

TEST(condition_variable, all_release) {
    static cppc::mutex m;
    static cppc::condition_variable cv;
    static int a = 1;
    static bool go = false;

    std::vector<std::thread*> vt;
    for (int i=0;i<5;i++){
        vt.push_back(new std::thread([&]()->void{
            m.lock();
            while (true){
                if (go){
                    a++;
                    m.unlock();
                    break;
                }
                else{
                    cv.wait(m);
                }
            }
        }));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    a = 0;
    go = true;
    cv.notify_all();
    for (auto tp : vt){
        tp->join();

    }
    ASSERT_EQ(a, 5);
}
