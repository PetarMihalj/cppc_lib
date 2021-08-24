#include "cppc.h"

cppc::lock_guard::lock_guard(mutex& m):_mutex(m){
    this->_mutex.lock();
};

cppc::lock_guard::~lock_guard(){
    this->_mutex.unlock();
};


