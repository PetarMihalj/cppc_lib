#include <chrono>
#include <iostream>
#include <thread>
#include <memory>

#include "cppc.h"
#include "iro.h"

/*
cppc::barrier b(3);

void f(char c, int s){
    for (int i=0;i<5;i++){
        b.decrement_and_wait();
        std::this_thread::sleep_for(std::chrono::seconds(s));
        std::cout << c << std::flush;
        b.decrement_and_wait();
        std::cout << c << std::flush;
    }
}


int main(){
    std::thread t1([]()->void{
        f('a',1);
    });
    std::thread t2([]()->void{
        f('b',2);
    });
    std::thread t3([]()->void{
        f('c',3);
    });

    t1.join();
    t2.join();
    t3.join();

    return 0;
}*/

cppc::semaphore sem;

void f(char c){
    for (int i=0;i<5;i++){
        sem.get();
        std::cout << c << std::flush;
    }
}


int main(){
    std::thread t1([]()->void{
        f('a');
    });
    std::thread t2([]()->void{
        f('b');
    });
    std::thread t3([]()->void{
        f('c');
    });

    for (int i=0;i<20;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        sem.put(1);
    }

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

/*
cppc::condition_variable cv;
cppc::mutex cvm;

static int v;
static int id;

void consumer(int i){
    while (true){
        cv.wait(cvm);
        if (v>0){
            std::cout << "Consuming: " << i << std::endl;
            v--;
        }
        cvm.unlock();
    }
}

void producer(int i, int ms){
    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        cvm.lock();
        std::cout << i << " Producing: " << i << std::endl;
        v++;
        cvm.unlock();
        cv.notify_one();
    }
}

int main(){
    for (int i=1;i<5;i++){
        new std::thread ([i]()->void{
            consumer(i);
        });

    }
    for (int i=1;i<5;i++){
        new std::thread ([i]()->void{
            producer(i, (i*i)*300);
        });

    }

    while (true){
        std::this_thread::yield();
    }
    return 0;
}*/
