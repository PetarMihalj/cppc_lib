#include "cppc.h"
#include <iostream>
#include <memory>
#include <vector>

cppc::barrier::barrier(std::size_t reset_point): _reset_point{reset_point}, _current_cnt{reset_point}{};

void cppc::barrier::decrement(){
    lock_guard lg(_mm);

    _current_cnt--;
    if (_current_cnt == 0){
        _current_cnt = _reset_point;
        for (auto& sp : _blocked){
            sp->unlock();
        }
        _blocked.clear();
    }
}

void cppc::barrier::wait(){
    auto sp = std::make_shared<mutex>();
    {
        lock_guard lg{_mm};
        _blocked.push_back(sp);
        sp->lock();
    }
    sp->lock();
}

void cppc::barrier::decrement_and_wait(){
    auto sp = std::make_shared<mutex>();
    {
        lock_guard lg{_mm};

        _current_cnt--;
        if (_current_cnt == 0){
            _current_cnt = _reset_point;
            for (auto& sp : _blocked){
                sp->unlock();
            }
            _blocked.clear();
        }
        else{
            _blocked.push_back(sp);
            sp->lock();
        }
    }
    sp->lock();
    sp->unlock();
}
