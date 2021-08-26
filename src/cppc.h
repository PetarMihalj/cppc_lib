#include <bits/stdint-uintn.h>
#include <memory>
#include <pthread.h>
#include <type_traits>
#include <vector>
#include "iro.h"
#include <functional>

namespace cppc{

class mutex{
private:
    pthread_mutex_t _mutex;
public:
    mutex();
    ~mutex();
    mutex& operator=(mutex& that) = delete;
    mutex(mutex& that) = delete;

    void lock();
    void unlock();
    bool try_lock();
};
static_assert(rule_traits::is_no_copy_move<mutex>::value);

class lock_guard{
private:
    mutex* _mutex;
public:
    lock_guard(mutex&);
    lock_guard(const lock_guard&) = delete;
    lock_guard(lock_guard&&);
    lock_guard& operator=(const lock_guard&) = delete;
    lock_guard& operator=(lock_guard&&);
    ~lock_guard();
};
static_assert(rule_traits::is_three_move<lock_guard>::value);

class barrier{
private:
    std::size_t _current_cnt;
    std::size_t _reset_point;
    std::vector<std::shared_ptr<mutex>> _blocked;
    mutex _mm;

public:
    barrier(std::size_t);
    ~barrier() = default;
    barrier& operator=(barrier& that) = delete;
    barrier(barrier& that) = delete;

    void decrement();
    void wait();
    void decrement_and_wait();
};
static_assert(rule_traits::is_no_copy_move<barrier>::value);

// implement condition variable, fix barrier, implement semaphore
// implement future & promise paradigms

}
