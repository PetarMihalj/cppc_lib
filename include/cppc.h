#include <bits/c++config.h>
#include <bits/stdint-uintn.h>
#include <pthread.h>

#include <memory>

namespace cppc {

// Interface to the mutex primitive. Mutex is mostly allocated in static/process level context,
// so that multiple threads can access it at the same time. An alternative is to share a pointer
// to stack or heap memory.
//  
// Beware:
// - A thread which locks the mutex should be the one to unlock it, UB otherwise
// - Destruction of locked mutex results in UB
class mutex {
  private:
    pthread_mutex_t _mutex;
  public:
    mutex();
    ~mutex();
    mutex &operator=(mutex &that) = delete;
    mutex(mutex &that) = delete;

    void lock();
    void unlock();
    pthread_mutex_t &native_handle();
};

// Interface to the condition variable primitive.
// Condition variables are used in conjuction with mutexes, and allow for implementation
// of complex synchronization primitives.
//
// Check out https://www.cplusplus.com/reference/condition_variable/condition_variable/wait/
// for use cases.
class condition_variable {
    pthread_cond_t _cond;

  public:
    condition_variable();
    ~condition_variable();

    condition_variable &operator=(condition_variable &that) = delete;
    condition_variable(condition_variable &that) = delete;

    // Mutex does not have to be locked when calling notify_one
    void notify_one();

    // Mutex does not have to be locked when calling notify_one
    void notify_all();

    // Mutex has to be locked when calling fuction wait.
    //
    // Wait is a blocking function. When invoked it releases the mutex
    // and blocks the calling thread in the condition variable queue.
    // After another thread notifies it (or other signal arrives),
    // mutex lock is again atomically aquired and execution continues.
    void wait(mutex &m);
};

// A shared mutex is a mutex which can be locked either 
// 1) exclusively (lock / unlock)
// 2) non-exclusively (lock_shared / unlock_shared)
//
// Non-exclusive lock can be aquired by multiple non-exclusive locking
// threads, while the exclusive lock allows only one thread to
// aquire it.
//
// Beware:
// - A thread which aquires the exclusive lock should be the one 
//   to unlock it, UB otherwise.
// - Only the threads which aquire the shared lock should be the ones
//   to unlock it, UB otherwise.
// - Destruction of locked shared mutex results in UB.
class shared_mutex {
    mutex _m;
    condition_variable _cv;
    bool _locked;
    std::size_t _locked_share_count;

  public:
    shared_mutex() = default;
    ~shared_mutex() = default;

    shared_mutex &operator=(shared_mutex &that) = delete;
    shared_mutex(shared_mutex &that) = delete;

    void lock();
    void unlock();

    void lock_shared();
    void unlock_shared();
};

// Implements a lifetime-based **exclusive** locking mechanism.
// Pass it a reference to either a
// 1) cppc::mutex
// 2) cppc::shared_mutex
// Unique_lock will lock the mutex upon construction,
// and release it upon destruction.
//
// Allows for moving (construction and assignment) the lock in order
// to transfer mutex aquisition to other contexts.
template <typename T> class unique_lock {
  private:
    T *_mutex;

  public:
    unique_lock(T &);
    unique_lock(const unique_lock &) = delete;
    unique_lock(unique_lock &&);
    unique_lock &operator=(const unique_lock &) = delete;
    unique_lock &operator=(unique_lock &&);
    ~unique_lock();
};

// Implements a lifetime-based **non-exclusive** locking mechanism.
// Pass it a reference to a **shared_mutex**, 
// and it will aquire it upon construction,
// and release it upon destruction.
//
// Allows for moving (construction and assignment) the lock in order
// to transfer mutex aquisition to other contexts.
template <typename T> class shared_lock {
  private:
    T *_mutex;

  public:
    shared_lock(T &);
    shared_lock(const shared_lock &) = delete;
    shared_lock(shared_lock &&);
    shared_lock &operator=(const shared_lock &) = delete;
    shared_lock &operator=(shared_lock &&);
    ~shared_lock();
};

// Barrier is a synchronization mechanism which
// allows for blocking of a group of threads until enough
// tokens have been consumed, releasing all the threads
// afterwards.
//
// The counter is immidiatelly reset to reset_pointer
// after reaching zero.
class barrier {
  private:
    std::size_t _current_cnt;
    const std::size_t _reset_point;
    std::shared_ptr<bool> _ind;
    mutex _mm;
    condition_variable _cv;

  public:
    barrier(const std::size_t);
    ~barrier() = default;
    barrier &operator=(barrier &that) = delete;
    barrier(barrier &that) = delete;

    // Decrement the counter
    void decrement();

    // Block in the queue
    void wait();

    // Decrement the counter and block in the queue afterwards.
    // If the counter reaches zero, the thread which invoked
    // the function also gets unlocked.
    void decrement_and_wait();
};

// A classic token-production/token-consumption semaphore.
class semaphore {
  private:
    std::size_t counter;
    mutex _mm;
    condition_variable _cv;

  public:
    semaphore() = default;
    ~semaphore() = default;
    semaphore &operator=(semaphore &that) = delete;
    semaphore(semaphore &that) = delete;

    // Acquire a token, or block until it is available
    void get();

    // Put some ammount of tokens in the semaphore
    void put(const std::size_t);
};

} // namespace cppc
