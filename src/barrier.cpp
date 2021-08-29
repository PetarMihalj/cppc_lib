#include "cppc.h"
#include <iostream>
#include <memory>
#include <vector>
#include "rule_traits.h"

static_assert(rule_traits::is_no_copy_move<cppc::barrier>::value);

cppc::barrier::barrier(const std::size_t reset_point): 
    _reset_point{reset_point}, 
    _current_cnt{reset_point},
    _ind{std::make_shared<bool>(false)}
{};

void cppc::barrier::decrement(){
    _mm.lock();
    _current_cnt--;
    if (_current_cnt == 0){
        *_ind = true;
        _ind = std::shared_ptr<bool>();
        _current_cnt = _reset_point;
        _cv.notify_all();
    }
    _mm.unlock();
}

void cppc::barrier::wait(){
    _mm.lock();
    auto my_ind = _ind;
    
    while (true){
        _cv.wait(_mm);
        if (*my_ind){
            _mm.unlock();
            break;
        }
        else{
            _mm.unlock();
        }
    }
}

void cppc::barrier::decrement_and_wait(){
    _mm.lock();
    _current_cnt--;
    if (_current_cnt == 0){
        *_ind = true;
        _ind = std::make_shared<bool>(false);
        _current_cnt = _reset_point;
        _cv.notify_all();
        _mm.unlock();
    }
    else{
        auto my_ind = _ind;
        
        while (true){
            _cv.wait(_mm);
            if (*my_ind){
                _mm.unlock();
                break;
            }
            else{
                _mm.unlock();
            }
        }
    }
}
