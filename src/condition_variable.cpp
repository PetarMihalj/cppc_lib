#include "cppc.h"
#include "rule_traits.h"
#include <cstddef>
#include <pthread.h>

static_assert(rule_traits::is_no_copy_move<cppc::condition_variable>::value);

cppc::condition_variable::condition_variable() {
    pthread_cond_init(&_cond, NULL);
}

cppc::condition_variable::~condition_variable() {
    pthread_cond_destroy(&_cond);
}

void cppc::condition_variable::notify_one() { pthread_cond_signal(&_cond); }

void cppc::condition_variable::notify_all() { pthread_cond_broadcast(&_cond); }

void cppc::condition_variable::wait(mutex &m) {
    pthread_cond_wait(&_cond, &m.native_handle());
}
