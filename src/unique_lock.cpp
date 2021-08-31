#include "cppc.h"
#include "rule_traits.h"

static_assert(
    rule_traits::is_three_move<cppc::unique_lock<cppc::mutex>>::value);
static_assert(
    rule_traits::is_three_move<cppc::unique_lock<cppc::shared_mutex>>::value);

template <typename T> cppc::unique_lock<T>::unique_lock(T &m) : _mutex(&m) {
    this->_mutex->lock();
}

template <typename T> cppc::unique_lock<T>::~unique_lock() {
    this->_mutex->unlock();
}

template <typename T>
cppc::unique_lock<T>::unique_lock(cppc::unique_lock<T> &&that)
    : _mutex(that._mutex){};

template <typename T>
cppc::unique_lock<T> &
cppc::unique_lock<T>::operator=(cppc::unique_lock<T> &&that) {
    std::swap(this->_mutex, that._mutex);
    return *this;
};

template class cppc::unique_lock<cppc::mutex>;
template class cppc::unique_lock<cppc::shared_mutex>;
