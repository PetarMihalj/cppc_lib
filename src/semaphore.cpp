#include "cppc.h"
#include <iostream>
#include <memory>
#include <vector>
#include "rule_traits.h"

static_assert(rule_traits::is_no_copy_move<cppc::semaphore>::value);

void cppc::semaphore::get(){
    _mm.lock();
    while (true){
        if (counter){
            counter--;
            _mm.unlock();
            break;
        }
        else{
            _cv.wait(_mm);
        }
    }
}

void cppc::semaphore::put(const std::size_t val){
    _mm.lock();
    counter += val;
    _cv.notify_all();
    _mm.unlock();
}
