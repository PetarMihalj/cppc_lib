#include "cppc.h"
#include <iostream>
#include <memory>
#include <vector>
#include "rule_traits.h"

static_assert(rule_traits::is_no_copy_move<cppc::semaphore>::value);

void cppc::semaphore::get(){
    _mm.lock();
    while (true){
        _cv.wait(_mm);
        if (counter){
            counter--;
            _mm.unlock();
            break;
        }
        else{
            _mm.unlock();
        }
    }
}

void cppc::semaphore::put(const std::size_t val){
    _mm.lock();
    counter += val;
    for (std::size_t i = 0; i<val; i++){
        _cv.notify_one();
    }
    _mm.unlock();
}
