
#pragma once

#include <cstdint>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <future>
#include <condition_variable>

typedef std::function<void()> TaskFunction;
class ThreadPool final
{
public:
    ThreadPool(uint32_t threadCount);
    bool GetTaskStatus();
    void StartTask();
    void StopTask();
    ~ThreadPool();

    template<class F, class... Args>
    auto AddTask(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(m_taskMutex);
            m_taskQueue.emplace([task]() { (*task)(); });
        }
        m_conditionVariable.notify_one();
        return res;
    }

private:
    TaskFunction TakeTask();    // 从任务队列中拿单个任务
    void PollTask();            // 轮询处理任务

private:
    std::vector<std::thread> m_threadVec;
    std::queue<TaskFunction> m_taskQueue;
    std::mutex m_taskMutex;
    std::condition_variable m_conditionVariable;
    std::atomic<bool> m_isStarted;
    uint32_t m_threadCount;
};

