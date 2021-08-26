#include "cppc.h"

cppc::lock_guard::lock_guard(mutex& m):_mutex(&m){
    this->_mutex->lock();
}

cppc::lock_guard::~lock_guard(){
    this->_mutex->unlock();
}

cppc::lock_guard::lock_guard(cppc::lock_guard&& that):_mutex(that._mutex){};

cppc::lock_guard& cppc::lock_guard::operator=(cppc::lock_guard&& that){
    std::swap(this->_mutex, that._mutex);
    return *this;
};
