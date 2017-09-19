// See: http://www.acodersjourney.com/2017/08/top-20-cplusplus-multithreading-mistakes/

#include <iostream>
#include <thread>     // std::thread
#include <mutex>      // std::mutex, std::lock_guard
#include <functional> // std::ref

void log(std::mutex& mu, const std::string& message)
{
    std::lock_guard<std::mutex> lock(mu);
    std::cout << "Thread " << std::this_thread::get_id() << ": " << message << "\n";
}

int main()
{
    std::mutex mu;

    // std::mutex is not copyable
    // use std::ref to pass it by reference
    std::thread t1(log, std::ref(mu), "log1");
    std::thread t2(log, std::ref(mu), "log2");
    std::thread t3(log, std::ref(mu), "log3");

    log(mu, "log");

    std::thread t4(log, std::ref(mu), "log4");
    std::thread t5(log, std::ref(mu), "log5");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}

