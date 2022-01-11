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
    // ���ܴ���m_isStarted������Ϊfalse����������е�����ȫ����������߳̾Ͳ��ٹ���
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
    // �������Ϊ�գ��̳߳��������е�����£��߳̾͵ȴ���������
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
        // ֹͣ�������У�֪ͨ�����̲߳��ٵȴ��µ�������
        std::unique_lock<std::mutex> lock(m_taskMutex);
        m_isStarted.store(false);
        m_conditionVariable.notify_all();
    }
    // ֹͣ�������к󣬲����߳̿��ܻ��ڴ���������Ҫjoin�ȴ��������
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
