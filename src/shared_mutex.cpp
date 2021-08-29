#include "cppc.h"
#include "rule_traits.h"

static_assert(rule_traits::is_no_copy_move<cppc::shared_mutex>::value);

void cppc::shared_mutex::lock(){
    _m.lock();
    
    while (true){
        if (_locked_share_count == 0 && !_locked){
            _locked = true;
            _m.unlock();
            return;
        }
        else{
            _cv.wait(_m);
        }
    }
}

void cppc::shared_mutex::unlock(){
    _m.lock();
    _locked = false;
    _cv.notify_all();
    _m.unlock();
}

void cppc::shared_mutex::lock_shared(){
    _m.lock();
    
    while (true){
        if (!_locked){
            _locked_share_count += 1;
            _m.unlock();
            return;
        }
        else{
            _cv.wait(_m);
        }
    }
}

void cppc::shared_mutex::unlock_shared(){
    _m.lock();
    _locked_share_count -= 1;
    _cv.notify_all();
    _m.unlock();
}
