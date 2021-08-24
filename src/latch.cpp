#include "cppc.h"
#include <bits/c++config.h>
#include <iostream>
#include <vector>

cppc::latch::latch(std::size_t cnt):_cnt{cnt}{};

cppc::latch::~latch(){};

void cppc::latch::_release_all(){
    for (auto& m : blocked){
        m.unlock();
    }
}

void cppc::latch::arrive_and_wait(){
    size_t i;
    {
        lock_guard lg{_mm};
        if (_cnt==1){
            _release_all();
            return;
        }
        else if (_cnt==0){
            return;
        }
        else{
            i = blocked.size();
            blocked.emplace_back();
            _cnt--;
        }
    }
    blocked[i].lock();
    blocked[i].lock();
}
