#include "cppc.h"
#include "rule_traits.h"

static_assert(rule_traits::is_three_move<cppc::shared_lock<cppc::shared_mutex>>::value);

template<typename T>
cppc::shared_lock<T>::shared_lock(T& m):_mutex(&m){
    this->_mutex->lock_shared();
}

template<typename T>
cppc::shared_lock<T>::~shared_lock(){
    this->_mutex->unlock_shared();
}

template<typename T>
cppc::shared_lock<T>::shared_lock(cppc::shared_lock<T>&& that):_mutex(that._mutex){};

template<typename T>
cppc::shared_lock<T>& cppc::shared_lock<T>::operator=(cppc::shared_lock<T>&& that){
    std::swap(this->_mutex, that._mutex);
    return *this;
};

template class cppc::shared_lock<cppc::shared_mutex>;
