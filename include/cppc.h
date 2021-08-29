#include <bits/c++config.h>
#include <bits/stdint-uintn.h>
#include <memory>
#include <pthread.h>

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

template<typename T>
class unique_lock{
private:
    T* _mutex;
public:
    unique_lock(T&);
    unique_lock(const unique_lock&) = delete;
    unique_lock(unique_lock&&);
    unique_lock& operator=(const unique_lock&) = delete;
    unique_lock& operator=(unique_lock&&);
    ~unique_lock();
};

template<typename T>
class shared_lock{
private:
    T* _mutex;
public:
    shared_lock(T&);
    shared_lock(const shared_lock&) = delete;
    shared_lock(shared_lock&&);
    shared_lock& operator=(const shared_lock&) = delete;
    shared_lock& operator=(shared_lock&&);
    ~shared_lock();
};

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

}
