# 绘制流程图


> We're living the future so

# This is an < > tag
## This is an < h2 > tag
###### This is an < h6 > tag

# 这个标题拥有 1 个 id {#my_id}
# 这个标题有 2 个 classes {.class1 .class2}
1. Item 1
1. Item 2
1. Item 3
   1. Item 3a
   1. Item 3b


*This text will be italic*
_This will also be italic_
**This text will be bold**
__This will also be bold__
_You **can** combine them_

- [x] @mentions, #refs, [links](), **formatting**, and <del>tags</del> supported
- [x] list syntax required (any unordered or ordered list supported)
- [x] this is a complete item
- [ ] this is an incomplete item



* Item 1
* Item 2
  * Item 2a
  * Item 2b
    * Item 2a
    * Item 2b
	  *sdfs
	    *dsggd





# UML Tutorial
```plantuml
@startuml
Title "单例模式(通用类图)"
class Client
class Singleton
Singleton <.. Client
class Singleton{
+ static final Singleton = new Singleton()
+ static Singleton getSingleton()
#int rivers()
- private Singleton()
}

class Client {
-- 通过 Singleton.getSingleton()方式访问
}
@enduml
```


First Header | Second Header
------------ | -------------
Content from cell 1 | Content from cell 2
Content in the first column | Content in the second column

泛化|实现| 关联|依赖| 聚合| 组合 
----|----|----|----|-----|-----


```plantuml
@startuml
ClassB <|-left- Generalization:泛化(带实线的三角箭头)
ClassB <|.. Realization:实现(带虚线的三角箭头)
ClassB <.. Dependency: 依赖(带虚线的箭头)
ClassB <-- Association:关联(实线的箭头)
Association o-- Aggregation:聚集(空心菱形箭头)
Association *-- Composition:组合(实心菱形箭头)

Class Generalization{
泛化（Generalization）
指的是类之间的继承关系
}
class Realization{
实现（Realization）
指的是类与接口之间的关系
}
class Dependency{
依赖（Dependency）
指的是类之间的调用关系
如果类A访问类B的属性或者方法，或者类A负责实例化类B，那么可以说类A依赖类B
和关联关系不同，无须在类A中定义类B类型的属性
A类(A类实例化对象)依赖B类(B类实例化对象)的意思就是
B类实例化的对象名作为参数传递给A类(对象)的方法,那么在A类对象就可以用B类实例化对象的方法
一个类要发送消息给另一个类；一个类将另一个类作为其数据的一部分；一个类的操作中将另一个类作为其参数。如果一个类改变了接口，则任何发送给该类的消息可能不再有效了。
}
class Association{
关联 （Association）
A类和B类关联意思是B类对象作为参数传递给A中并且封装成了A对象的一个属性
它使一个类知道另一个类的属性和方法
{static}表示类与类之间的联接分为聚合和组合
这种关系比依赖更强、不存在依赖关系的偶然性、关系也不是临时性的，一般是长期性的。
}
class Aggregation{
表示一种弱的“拥有”关系，体现的是A对象可以包含B对象，但B对象不是A对象的一部分，
用空心的菱形+实线箭头来表示   例如： 公司和员工
}
class Composition{
用实心的菱形+实线箭头来表示  组合：部分和整体的关系，并且生命周期是相同的。例如：人与手
}

@enduml
```
## 显示行号
```python{.line-numbers}
#（植物大战僵尸）依赖关系
class ZhiWu:#创建植物类
    def __init__(self,name,hp,attack):#初始化属性
        self.name=name
        self.hp=hp
        self.attack=attack
    def da(self,js):
        js.hp-=self.attack
 
class JiangShi:#创建僵尸类
    def __init__(self,name,hp,attack):#初始化属性
        self.name=name
        self.hp=hp
        self.attack=attack
    def eat(self,zw):
        zw.hp -= self.attack
# 创建僵尸和植物对象
zw=ZhiWu("紫罗兰",20,10)
js=JiangShi("躺尸",30,5)
# 植物攻击一次
zw.da(js)
print(js.hp)#20
# 僵尸攻击一次
js.eat(zw)
print(zw.hp)#15
```


# 流程图创建
```flow
st=>start: Start|past:>http://www.google.com[blank]
e=>end: End:>http://www.google.com
op1=>operation: get_hotel_ids|past
op2=>operation: get_proxy|current
sub1=>subroutine: get_proxy|current
op3=>operation: save_comment|current
op4=>operation: set_sentiment|current
op5=>operation: set_record|current

cond1=>condition: ids_remain空?
cond2=>condition: proxy_list空?
cond3=>condition: ids_got空?
cond4=>condition: 爬取成功??
cond5=>condition: ids_remain空?

io1=>inputoutput: ids-remain
io2=>inputoutput: proxy_list
io3=>inputoutput: ids-got

st->op1(right)->io1->cond1
cond1(yes)->sub1->io2->cond2
cond2(no)->op3
cond2(yes)->sub1
cond1(no)->op3->cond4
cond4(yes)->io3->cond3
cond4(no)->io1
cond3(no)->op4
cond3(yes, right)->cond5
cond5(yes)->op5
cond5(no)->cond3
op5->e
```

```dot
digraph G {
	A -> B
}
```

# 数学 & *LATEX*

A+$
 \begin{bmatrix}
   a & b & c & d & e\\
   f & g & h & i & j \\
   k & l & m & n & o \\
   p & q & r & s & t
  \end{bmatrix} 
$+ 

$$
\left[
    \begin{matrix}
   a & b & c & d & e\\
   f & g & h & i & j \\
   k & l & m & n & o \\
   p & q & r & s & t
    \end{matrix} 
\right]
$$

$$ 
\left[
    \begin{array}{cc|c}
      1 & 2 & 3 \\
      4 & 5 & 6
    \end{array}
\right] \tag{7}
$$


$
\begin{equation}
R^2 = 
\left({\begin{array}{cc} c & s \end{array}}\right)
\left(\begin{array}{cc} 1 & 0\\ 0 & 1 \end{array}\right)
\left(\begin{array}{c} c \\ s \end{array}\right) 
= c^2 + s^2
\end{equation}
$

$$A=
\left\{
 \begin{matrix}
   a & b & c & d & e\\
   f & g & h & i & j \\
   k & l & m & n & o \\
   p & q & r & s & t
  \end{matrix} 
\right\}
$$

$$A=
\left\{
 \begin{matrix}
    1 & 2 \\ 
    3 & 4 
  \end{matrix} 
\right\}
$$

//array必须为array
//{cccc|c}中的c表示矩阵元素，可以控制|的位置
$$A=
\left\{
 \begin{array}{c|c|c|c|c}{r|rrrr}
     a_{12} & b & c & d & e\\
     f & g & h & i & j \\
     k & l & m & n & o \\
     p & q & r & s & t
  \end{array} 
\right\}
$$

$$
F_\beta(x) =\sum_i^{1000} \sum_{m=0}^\infty \frac{(-1)^m+m!+\frac{1}{m}}{m! \Gamma (m^m + \beta + 1 + i^2)} {\left({ \frac{x}{2} }\right)}^{2^m + \beta}
$$

$$
A = 
\begin{bmatrix} 1 & 2 & 3 & 4 \end{bmatrix}
\begin{pmatrix} 1 \\ 2 \\ 3 \\ 4 \end{pmatrix}
$$