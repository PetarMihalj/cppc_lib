#include <bits/stdint-uintn.h>
#include <pthread.h>
#include <vector>

namespace cppc{

class mutex{
private:
    pthread_mutex_t _mutex;
public:
    mutex();
    ~mutex();
    mutex& operator=(mutex&) = delete;

    void lock();
    void unlock();
    bool try_lock();
};

class lock_guard{
private:
    mutex& _mutex;
public:
    lock_guard(mutex&);
    ~lock_guard();
    lock_guard& operator=(lock_guard&) = delete;
};

class latch{
private:
    std::size_t _cnt;
    std::vector<mutex> blocked;
    mutex _mm;

    void _release_all();

public:
    latch(std::size_t cnt);
    ~latch();
    latch& operator=(latch&) = delete;

    void count_down();
    bool try_wait();
    void wait();
    void arrive_and_wait();
};

}
