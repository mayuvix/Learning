### 前言

- 在探讨c++11中的Move函数前，先介绍两个概念（左值和右值）

### 左值和右值

首先区分左值和右值，左值和右值只的是等号的左边和右边
左值是表达式结束后依然存在的持久对象(代表一个在内存中占有确定位置的对象)
右值是表达式结束时不再存在的临时对象(不在内存中占有确定位置的表达式）
便携方法：对表达式取地址，如果能，则为左值，否则为右值

```cpp
int val;
val = 4; // 正确 ①
4 = val; // 错误 ②
```

上述例子中，由于在之前已经对变量val进行了定义，故在栈上会给val分配内存地址，运算符=要求等号左边是可修改的左值，4是临时参与运算的值，一般在寄存器上暂存，运算结束后在寄存器上移除该值，故①是对的，②是错的

### std::move函数

- std::move作用主要可以将一个左值转换成右值引用，从而可以调用C++11右值引用的拷贝构造函数   
- std::move应该是针对你的对象中有在堆上分配内存这种情况而设置的，如下

### remove_reference源码剖析

在分析`std::move()`与`std::forward()`之前，先看看`remove_reference`，下面是`remove_reference`的实现：

```cpp
template<typename _Tp>
struct remove_reference
{ typedef _Tp   type; };
 
// 特化版本
template<typename _Tp>
struct remove_reference<_Tp&>
{ typedef _Tp   type; };
 
template<typename _Tp>
struct remove_reference<_Tp&&>
{ typedef _Tp   type; };
```

`remove_reference`的作用是去除`T`中的引用部分，只获取其中的类型部分。无论`T`是左值还是右值，最后只获取它的类型部分。

### std::forward源码剖析

- 转发左值

```cpp
template<typename _Tp>
constexpr _Tp&&
forward(typename std::remove_reference<_Tp>::type& __t) noexcept
{ return static_cast<_Tp&&>(__t); }
```

先通过获得类型type，定义`_t`为左值引用的左值变量，通过`static_cast`进行强制转换。`_Tp&&`会发生引用折叠，当`_Tp`推导为左值引用，则折叠为`_Tp& &&`，即`_Tp&`，当推导为右值引用，则为本身`_Tp&&`，即`forward`返回值与`static_cast`处都为`_Tp&&`。

### 引用折叠（引用坍塌）(reference-collapsing rules)

声明为T&& 的类型的形参在绑定实参时会发生类型推导，根据实参是左值还是右值推导为左值和右值，（cpp标准规定？有待确认）

```cpp
A&  &  => A& 	//左值形参+左值实参 =>左值
A&  && => A&	//左值形参+右值实参 =>左值
A&& &  => A&	//右值形参+左值实参 =>左值
A&& && => A&&	//右值形参+右值实参 =>右值
```

```cpp
void fr(int&& i)
{
    cout << i << endl;
}
void fl(int& i)
{
    cout << i << endl;
}
void flc(const int& i)
{
    cout << i << endl;
}
int&& geti()
{
    return 10;
}
int main()
{
    int&& a = 10;
    int b = 10;
    int&& c = geti();
    fr(10);
    fr(a); fr(c);//error. an rvalue reference cannot be bound to an lvalue ①
    fl(a);
    fr(b); //error. an rvalue reference cannot be bound to an lvalue
    fl(b);
    fr(geti());
    fl(geti()); //error. initial value of reference to non-const must be an lvalue
    flc(geti());
}
```

①[为什么右值引用可以转化为左值引用？](https://www.zhihu.com/question/436996358)->具名右值其实是左值?(以下1,2为解释)

1.[C++11尝鲜：右值引用和转发型引用](https://blog.csdn.net/zwvista/article/details/12306283)

2.[Rvalue Reference Declarator: &&](https://docs.microsoft.com/en-us/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-160#:~:text=The%20compiler%20treats%20a%20named,the%20body%20of%20the%20function.&text=In%20this%20example%2C%20the%20main%20function%20passes%20an%20rvalue%20to%20f%20.)

The compiler treats a named rvalue reference as an **lvalue** and an unnamed rvalue reference as an rvalue. When you write a function that takes an rvalue reference as its parameter, that parameter is treated as an lvalue in the body of the function

[如何理解c++中的引用折叠?](https://www.zhihu.com/question/40346748/answer/88672920)

文献参考: [一文带你详细介绍c++中的std::move函数](https://www.cnblogs.com/shadow-lr/p/Introduce_Std-move.html)

[ std::move()右值引用详解](http://blog.sina.com.cn/s/blog_7f47cb430102vyy4.html)





注意阅读

https://blog.csdn.net/xiaolewennofollow/article/details/52559306