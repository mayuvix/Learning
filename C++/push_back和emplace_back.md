[emplace_back() 和 push_back 的区别](https://blog.csdn.net/xiaolewennofollow/article/details/52559364)

https://blog.csdn.net/ceasadan/article/details/79420533



[c++中有什么 push和insert可以但emplace做不到的操作么？](https://www.zhihu.com/question/347743586/answer/835340740)

```cpp
emplace_back是模板，是万能引用，里面会调用完美转发，在插入点构造。可传递多个参数，而push_back就不一样了，是模板里的函数，入参的类型已经被推导或者给定，调用时会利用template<T>里的T的隐形推导来完成入参构造。所以说这两个的区别在于一个是传入vector时已经构造好，一个是在插入点构造，由于后者是可变参数模板，所以可传入多个值在插入点构造，可以省去拷贝和move环节。
```

https://www.zhihu.com/question/387522517/answer/1151720189



```cpp
#include <vector>  
#include <string>  
#include <iostream>  

struct President  
{  
    std::string name;  
    std::string country;  
    int year;  

    President(std::string p_name, std::string p_country, int p_year)  
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year)  
    {  
        std::cout << "I am being constructed.\n";  
    }
    President(const President& other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being copy constructed.\n";
    }
    President(President&& other)  
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)  
    {  
        std::cout << "I am being moved.\n";  
    }  
    President& operator=(const President& other);  
};  

int main()  
{  
    std::vector<President> elections;  
    std::cout << "emplace_back:\n";  
    elections.emplace_back("Nelson Mandela", "South Africa", 1994); //直接调用构造函数创建  

    std::vector<President> reElections;  
    std::cout << "\npush_back:\n";  
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));  

    std::cout << "\nContents:\n";  
    for (President const& president: elections) {  
       std::cout << president.name << " was elected president of "  
            << president.country << " in " << president.year << ".\n";  
    }  
    for (President const& president: reElections) {  
        std::cout << president.name << " was re-elected president of "  
            << president.country << " in " << president.year << ".\n";  
    }

}

```

输出

```cpp
emplace_back:
I am being constructed.

push_back:
I am being constructed.
I am being moved.//如果将移动构造函数注释掉 这里显示 I am being copy constructed.

Contents:
Nelson Mandela was elected president of South Africa in 1994.
Franklin Delano Roosevelt was re-elected president of the USA in 1936.

```



```cpp
class Person {
    int _age = 0;

public:
    Person(int age) : _age(age) {
        cout << "Construct a person." << "age:"<<_age << endl;
    }

    Person(const Person& p) : _age(p._age) {
        cout << "Copy-Construct" << "age:" << _age << endl;
    }

    Person(Person&& p) noexcept : _age(p._age) {
        cout << "Move-Construct" << "age:" << _age << endl;
    }
};

int main() 
{
    using namespace std;
    vector<Person> person;
    person.reserve(10);
    auto p = Person(1); // >: Construct a person.1
    person.push_back(p);
    person.push_back(2);
    person.push_back(Person(2));
    person.emplace_back(move(p)); // >: Move-Construct1
    person.emplace_back(2);
}
/* output
Construct a person.age:1
Copy-Constructage:1
Construct a person.age:2
Move-Constructage:2
Construct a person.age:2
Move-Constructage:2
Move-Constructage:1
Construct a person.age:2
*/
```

