#include "cppc.h"
#include <pthread.h>
#include <iostream>

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

bool cppc::mutex::try_lock(){
    return (pthread_mutex_trylock(&this->_mutex)==0);
}

pthread_mutex_t& cppc::mutex::native_handle(){
    return _mutex;
}
