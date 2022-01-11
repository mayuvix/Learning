#include "TreadPool.h"


ThreadPool::ThreadPool(uint32_t threadCount)
    : m_threadCount(threadCount)
{
    std::atomic_init(&m_isStarted, false);
}

void ThreadPool::StartTask()
{
    if (m_isStarted.load())
        return;

    m_isStarted.store(true);
    m_threadVec.reserve(m_threadCount);
    for (uint32_t i = 0; i < m_threadCount; ++i)
    {
        m_threadVec.push_back(std::thread(&ThreadPool::PollTask, this));
    }
}

void ThreadPool::PollTask()
{
    // 可能存在m_isStarted被设置为false，而任务队列的任务全部处理完后，线程就不再工作
    while (true)
    {
        TaskFunction task = TakeTask();
        if (task)
            task();
        if (!m_isStarted.load() && m_taskQueue.empty())
            return;
    }
}

bool ThreadPool::GetTaskStatus()
{
    return m_isStarted.load();
}

TaskFunction ThreadPool::TakeTask()
{
    std::unique_lock<std::mutex> lock(m_taskMutex);
    // 任务队列为空，线程池正常运行的情况下，线程就等待任务来临
    m_conditionVariable.wait(lock, [this]() -> bool {
        return (!m_isStarted.load() || !m_taskQueue.empty());
        });

    TaskFunction task;
    if (!m_taskQueue.empty())
    {
        task = std::move(m_taskQueue.front());
        m_taskQueue.pop();
    }
    return task;
}

void ThreadPool::StopTask()
{
    {
        // 停止任务运行，通知所有线程不再等待新的任务了
        std::unique_lock<std::mutex> lock(m_taskMutex);
        m_isStarted.store(false);
        m_conditionVariable.notify_all();
    }
    // 停止任务运行后，部分线程可能还在处理任务，需要join等待任务完成
    for (auto& td : m_threadVec)
    {
        if (td.joinable())
            td.join();
    }
    m_threadVec.clear();
}

ThreadPool::~ThreadPool()
{
    StopTask();
}
