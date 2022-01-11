全局变量 也是static storage

C++另外有一种匿名的命名空间,来保证生成的符号是局部的,这样对于匿名空间中的变量等,外部都是不可见的.

C++ 新的标准中提倡使用匿名命名空间,而不推荐使用static,因为static用在不同的地方,涵义不同,容易造成混淆.另外,static不能修饰class。

匿名的命名空间是C++的特性,相对于C的static声明来说,可以在匿名的空间里面声明很多变量和函数,这样可以省去了对每个变量和函数添加static声明.

实质上匿名空间的功能跟static声明是一样的.

[二进制兼](https://www.cnblogs.com/my_life/articles/12154978.htm)

[Windows下的bat文件的@echo off 作用](https://blog.csdn.net/fly_as_tadpole/article/details/85177379)

