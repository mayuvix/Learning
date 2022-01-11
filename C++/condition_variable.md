### condition_variable

[C++11并发编程-条件变量(condition_variable)详解](https://www.2cto.com/kf/201506/411327.html)

头文件主要包含了与条件变量相关的类和函数。相关的类包括 `std::condition_variable`和 `std::condition_variable_any`，还有枚举类型`std::cv_status`。另外还包括函数 `std::notify_all_at_thread_exit()`，下面分别介绍一下以上几种类型。

```cpp
#include <thread>                // std::thread
#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable
 
std::mutex mtx; // 全局互斥锁.
std::condition_variable cv; // 全局条件变量.
bool ready = false; // 全局标志位.
 
void do_print_id(int id)
{
    std::unique_lock <std::mutex> lck(mtx);
    while (!ready) // 如果标志位不为 true, 则等待...
        cv.wait(lck); // 当前线程被阻塞, 当全局标志位变为 true 之后,
    // 线程被唤醒, 继续往下执行打印线程编号id.
    std::cout << "thread " << id << '\n';
}
 
void go()
{
    std::unique_lock <std::mutex> lck(mtx);
    ready = true; // 设置全局标志位为 true.
    cv.notify_all(); // 唤醒所有线程.
}
 
int main()
{
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(do_print_id, i);
 
    std::cout << "10 threads ready to race...\n";
    go(); // go!
 
  for (auto & th:threads)
        th.join();
 
    return 0;
}
```

结果：

```cpp
thread 1
thread 0
thread 2
thread 3
thread 4
thread 5
thread 6
thread 7
thread 8
thread 9
```



