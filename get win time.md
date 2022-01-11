# 获取精确时间

`QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);`

```c++
void gap::PerformanceTimer::BeginCalculating()// code in gcmp
{
    if (m_nestedCount == 0 && (!m_pParentTimer || m_pParentTimer->hasBegun()))
    {
        m_hasBegun = true;
#ifdef _WINDOWS
        QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);
#endif
    }
    ++m_nestedCount;
}
```

