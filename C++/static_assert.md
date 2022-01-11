[static_assert](https://www.cnblogs.com/Braveliu/p/12220769.html)

编译期静态检查

```C++
template<class T>
class WeakPtr
{
        void Reset(const T* pObject=nullptr)
        {
            static_assert(std::is_base_of<WeakReferenceable, T>::value, "Object referenced by WeakPtr MUST be DERIVED from WeakReferenceable.");
        }
}
```
std::false_type

std::is_base_of

std::is_same<frist, second>::value == true;[std::is_same, std::decay](https://blog.csdn.net/czyt1988/article/details/52812797)

[跨dll释放内存的问题](https://blog.csdn.net/zj510/article/details/35290505?utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control&dist_request_id=&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control)

[OwnerPtr和内存释放](http://pm.glodon.com/wiki/pages/viewpage.action?pageId=73792070)

        template <typename T>
        inline static std::wstring ToWString(T t)
        {
            static_assert(
                std::is_same<T, short>::value ||
                std::is_same<T, unsigned short>::value ||
                std::is_same<T, int>::value ||
                std::is_same<T, unsigned int>::value||
                std::is_same<T, long>::value ||
                std::is_same<T, unsigned long>::value ||
                std::is_same<T, long long>::value ||
                std::is_same<T, unsigned long long>::value,
                "Only accept integers");
    
            std::wostringstream woss;
            woss << t;
            return woss.str();
        }