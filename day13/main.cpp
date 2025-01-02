#include<iostream>
#include<thread>

std::atomic<int> counter(0);

int main() {
    std::thread t([](){
        while(true){
            std::cout<<"Hello from func1" << "\n";
        }
    });
    std::thread t2([](){
        while(counter < 100){
            std::cout<<"Hello from func2" << counter << "\n";
            counter++;
        }
    });
    t.detach();
    t2.detach();

    while(true) {
        std::cout<<"Hello there!" << counter << "\n";
    }
  
    return 0;
}