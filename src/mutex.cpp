#include "cppc.h"
#include <pthread.h>
#include <iostream>
#include "rule_traits.h"

static_assert(rule_traits::is_no_copy_move<cppc::mutex>::value);

cppc::mutex::mutex(){
    pthread_mutex_init(&this->_mutex, NULL);
}

cppc::mutex::~mutex(){
    pthread_mutex_destroy(&this->_mutex);
}

void cppc::mutex::lock(){
    auto st = pthread_mutex_lock(&this->_mutex);
}

void cppc::mutex::unlock(){
    pthread_mutex_unlock(&this->_mutex);
}

pthread_mutex_t& cppc::mutex::native_handle(){
    return _mutex;
}
