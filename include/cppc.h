#include <bits/c++config.h>
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
    pthread_mutex_t& native_handle();
};
static_assert(rule_traits::is_no_copy_move<mutex>::value);

class condition_variable{
    pthread_cond_t _cond;
public:
    condition_variable();
    ~condition_variable();

    condition_variable& operator=(condition_variable& that) = delete;
    condition_variable(condition_variable& that) = delete;

    void notify_one();
    void notify_all();
    void wait(mutex& m);
};
static_assert(rule_traits::is_no_copy_move<condition_variable>::value);

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
    const std::size_t _reset_point;
    std::shared_ptr<bool> _ind; 
    mutex _mm;
    condition_variable _cv;
public:
    barrier(const std::size_t);
    ~barrier() = default;
    barrier& operator=(barrier& that) = delete;
    barrier(barrier& that) = delete;

    void decrement();
    void wait();
    void decrement_and_wait();
};
static_assert(rule_traits::is_no_copy_move<barrier>::value);

class semaphore{
private:
    std::size_t counter;
    mutex _mm;
    condition_variable _cv;
public:
    semaphore() = default;
    ~semaphore() = default;
    semaphore& operator=(semaphore& that) = delete;
    semaphore(semaphore& that) = delete;

    void get();
    void put(const std::size_t);
};
static_assert(rule_traits::is_no_copy_move<semaphore>::value);

class shared_mutex{
    mutex _m;
    condition_variable _cv;
    bool _locked;
    std::size_t _locked_share_count;
public:
    shared_mutex() = default;
    ~shared_mutex() = default;

    shared_mutex& operator=(shared_mutex& that) = delete;
    shared_mutex(shared_mutex& that) = delete;

    void lock();
    void unlock();

    void lock_shared();
    void unlock_shared();
};
static_assert(rule_traits::is_no_copy_move<shared_mutex>::value);



}
