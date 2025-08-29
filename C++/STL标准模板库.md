# STL标准模板库

### 容器⭐

用来存储数据，也就是数据结构

#### 序列式容器

vector,list(双向循环链表)，deque。

##### 容器的初始化

**无参构造**

![image-20250725191757381](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725191757381.png)

```C++
    vector<int> vec;
    deque<int> deq;
    list<int> l1;
```

**大括号初始化**

![](C:\Users\34078\Pictures\Screenshots\屏幕截图 2025-07-25 192508.png)

```C++
    //有参构造
    vector<int> vec2={1,2,3};
    print(vec2);
    deque<int> deq2={4,5,6};
    print(deq2);
    list<int> l2={7,9,8};
    print(l2);
```

![image-20250725191520191](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725191520191.png)

**初始化若干个相同的值**

![](C:\Users\34078\Pictures\Screenshots\屏幕截图 2025-07-25 191730.png)

```C++
//初始化为多个相同的值
    vector<int> vec3(10,1);
    print(vec3);
    deque<int> deq3(10,5);
    print(deq3);
    list<int> l3(10,8);
    print(l3);
```

![image-20250725191949898](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725191949898.png)

**利用拷贝构造函数/移动构造函数初始化**

![image-20250725192258563](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725192258563.png)

```C++
    //拷贝构造/移动构造初始化
    vector<int> vec_temp(vec2);
    vector<int> vec4(move(vec_temp));
    print(vec4);
    deque<int> deq4(deq2);
    print(deq2);
    cout<<"============="<<endl;
    list<int> l4(l2);
    list<int> l_temp(move(l4));
    print(l_temp);
    print(l4);//此时输出为空，因为移动构造函数将l4的资源给了l_temp
    cout<<"============="<<endl;
```

![image-20250725192133806](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725192133806.png)

**使用迭代器初始化**

![](C:\Users\34078\Pictures\Screenshots\屏幕截图 2025-07-25 191847.png)

```C++
    //使用迭代器初始化
    vector<int> vec5(vec3.begin(),vec3.end());
    print(vec5);
    deque<int> deq5(deq3.begin(),deq3.end());
    print(deq5);
    list<int> l5(l3.begin(),l3.end());
    print(l5);
```

![image-20250725192401609](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725192401609.png)

##### 容器的遍历

```C++
template <class T>
void print(T t){
    
    for(auto &i:t){
        cout<<i<<" ";
    }
  
    //list容器不可用
    for(int i=0;i<t.size();++i){
        cout<<t[i]<<" ";
    }
    
    auto it=t.begin();
    while(it!=t.end()){
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
}
```

```C++
//两种重命名方式
using A=int;
typedef int A;
```

在vector中的at与operator[] 一样都可以访问下标，但是at()会进行安全检查。

------



##### 容器的操作

**1.在尾部的插入和删除**

push_back:在容器尾部追加一个元素。

![image-20250725193312338](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725193312338.png)

pop_back:在容器尾部删除一个元素。

![image-20250725193412593](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725193412593.png)

```C++
vector<int> vec={1,2,3}
print(vec);
vec.push_back(4);
vec.push_back(5);
print(vec);
vec.pop_back();
print(vec);
```

![image-20250725193621722](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725193621722.png)

**三种序列式容器都支持push_back()和pop_back()操作。**

------

**2.在头部的插入和删除**

```C++
   //vec.push_front(5);error

    deque<int> deq={2,3,5,7};
    print(deq);
    deq.push_front(4);
    deq.push_front(5);
    print(deq);
    deq.push_back(6);
    deq.push_back(9);
    print(deq);
    deq.pop_back();
    deq.pop_front();
    print(deq);
```

![image-20250725194220256](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725194220256.png)

**vector不支持在头部插入和删除，deque和list支持在头部插入和删除。**

<font color='red'>**思考：为什么vector不支持？**</font>

vector的头部是固定的，当在vector头部进行插入或者删除时，会导致后面的元素移动，时间复杂度较高O(n)，导致效率低下，因此不提供在头部对vector进行操作。

------



##### 容器原理

**vector原理**

vector的底层是三个指针：

- _M_start:指向第一个元素
- _M_finish:指向最后一个元素的下一个位置
- _M_end_of_storage:指向最后一个空间的下一个位置

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250802091240831.png" alt="image-20250802091240831" style="zoom:67%;" />

vector中push_back的扩容机制：当vector中加入新元素时，会先判断当前容量是否可以存放，如果不行的话，会根据当前容量的2倍大小申请一片新的堆空间，将旧容器中的数据拷入新的vector,并将旧容器的堆空间释放，最后更新指针。

**deque原理**

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725195853034.png" alt="image-20250725195853034" style="zoom:50%;" />

deque的底层是一个二级指针，和一个长度（中控器的长度）。

deque底层有一个中控器，deque是由不同的片段组成的，片段内部是连续的，但是片段之间是不连续的，片段是由中控器进行控制的，deque是逻辑上连续的，物理上是分散的。

对于vector而言，其迭代器就是一个普通类型的指针，但是对于deque而言，其迭代器不是一个普通类型的指针，而是一个类，但是在类中重载了指针的功能。

**deuqe的扩容机制**

当`deque`的容量不足时，会按照以下步骤进行扩容：

- **创建新缓冲区**：在头部或者尾部创建一个新的固定大小缓冲区。

- **更新中控器**：把新缓冲区的指针添加到中控器里。

- **指针调整**：对中控器的大小进行调整，使其能够容纳新添加的缓冲区指针。

如果中控器的满了，中控器也会进行扩容。

**<font color='red'>中控器的扩容步骤</font>**

**步骤 1：分配更大的新数组**

- 通常按**指数方式增长**（例如 2 倍），减少扩容次数。
- 例如，原中控器容量为 4，扩容后变为 8。

**步骤 2：复制原有缓冲区指针**

- 将原中控器中的所有指针复制到新数组中。

**步骤 3：释放原中控器内存**

- 销毁原中控器数组。

**步骤 4：更新中控器指针**

- `deque`内部指向中控器的指针更新为新数组的地址。

**list原理**

list链表的底层是一个双向循环链表。但是首节点和尾节点中间有一个空节点。

![image-20250725200337506](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725200337506.png)

------



##### 如何获取容器的第一个元素的地址

```C++
 vector<int> vec={1,2,3};
    print(vec);
    deque<int> deq={4,5,6};
    print(deq);
    list<int> l={7,8,9};
    print(l);

    cout<<"vector第一个元素的地址:"<<&vec[0]<<endl;
    cout<<"vector第一个元素的地址:"<<vec.data()<<endl;//vector所独有的方法

    cout<<"deque第一个元素的地址:"<<&*deq.begin()<<endl;
    cout<<"list第一个元素的地址:"<<&*l.begin()<<endl;//list只能用此方法
```

![image-20250725201023032](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250725201023032.png)

------



##### **vector的迭代器失效**

**insert操作**

![image-20250727152236355](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250727152236355.png)

vector的insert插入元素，导致的迭代器失效，因为不知道每次插入元素的个数，有可能因为插入元素导致了容器扩容，这样迭代器会指向老的空间，如果选择还使用指向老空间的迭代器，那么后续的操作使用的都是无效的迭代器，会造成未定义行为。

解决方案：每次使用迭代器时，重新置位迭代器。

```C++
void test2(){
    vector<int> vec={1,3,5,7,9};
    print(vec);
    auto pos=vec.begin();
    cout<<vec.size()<<endl;
    cout<<vec.capacity()<<endl;
    cout<<*(pos+2)<<endl;
    vec.insert(pos+2,4);//找一个位置插入元素
    print(vec);
    cout<<"======================="<<endl;
    cout<<vec.size()<<endl;
    cout<<vec.capacity()<<endl;
    cout<<*(pos+2)<<endl;
    vec.insert(pos+2,3,2);//找一个位置插入相同个元素
    print(vec);
    cout<<"======================="<<endl;
    cout<<vec.size()<<endl;
    cout<<vec.capacity()<<endl;
    cout<<*(pos+2)<<endl;
    vec.insert(pos+2,{11,12,13});//找一个位置，插入大括号内的元素
    print(vec);
    cout<<"======================="<<endl;
    cout<<vec.size()<<endl;
    cout<<vec.capacity()<<endl;
    cout<<*(pos+2)<<endl;
    vector<int> v={100,200,300};
    vec.insert(pos+2,v.begin(),v.end());//找一个位置插入迭代器范围内的元素
    print(vec);
    cout<<"======================="<<endl;

}
```

![](C:\Users\34078\Pictures\container_insert.png)

------



##### 容器删除重复连续的元素

**erase**

![image-20250727153645104](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250727153645104.png)

三种容器都无法删除重复连续的元素，因为删除之后迭代器指向的元素的之后的元素会前移，如果再进行迭代器++操作会漏删元素。

```C++
#include <iostream>
#include <vector>
using namespace std;
void test(){
    vector<int> vec={1,2,3,2,2,2,4,2,2,5,6};
    for(auto it=vec.begin();it!=vec.end();++it){
        if(*it==2){
            vec.erase(it);
        }
    }
    for(auto &it:vec){
        cout<<it<<" ";
    }
    cout<<endl;
}

int main()
{
 test();
 return 0;
}

```

![image-20250727153757712](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250727153757712.png)

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250727153432210.png" alt="image-20250727153432210" style="zoom: 50%;" />

```C++
//正确解法
 for(auto it=vec.begin();it!=vec.end();){
        if(*it==2){
            vec.erase(it);
            it=ve.erase(it);//1.erase返回的是被移除元素之后元素的迭代器位置
        }else{
            ++it;//2.当vector没有移除元素时才移动迭代器的位置
        }
    }
```

![image-20250727155016595](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250727155016595.png)

------



##### 元素的清空

clear()：删除容器元素

```C++
   vector<int> vec={1,2,3,4,5};
    cout<<"size:"<<vec.size()<<endl;
    cout<<"capacity:"<<vec.capacity()<<endl;
    vec.clear();
    cout<<"size:"<<vec.size()<<endl;
    cout<<"capacity:"<<vec.capacity()<<endl;
```

![image-20250727155408504](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250727155408504.png)

shrink_to_fit() 回收多余空间

```C++
   vec.shrink_to_fit();
```

![image-20250727155514149](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250727155514149.png)

list和deque中没有capacity()函数。

list中没有shrink_to_fit()函数。

------



##### 重置元素个数

**resize()**

`vector`的`resize`方法能够改变容器的元素数量。要是新的大小比当前大小大，新添加的元素会被初始化为默认值；要是新的大小比当前小，容器尾部的元素就会被删除。

若当前vector的容量为size,resize(n)。

- 当n<=size时，容器会删除尾部元素，容量不变。
- 当n>size时，容器会发生扩容，以当前容量大小的二倍进行扩容。

```C++
#include <iostream>
#include <vector>
using namespace std;
void test(){
    vector<int> vec;
    cout<<"扩容前vec的容量:"<<vec.capacity()<<endl;
    for(int i=1;i<=10;++i){
        vec.resize(i);
        cout<<"resize("<<i<<")后vec的容量:"<<vec.capacity()<<endl;
    }
}
int main()
{
 test();
 return 0;
}

```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250728192135591.png" alt="image-20250728192135591" style="zoom: 67%;" />



------

##### **vector的insert扩容机制**

因为vector的insert进行扩容时，每次新增的元素不是固定的，所以扩容的方式也不固定，而push_back可以按照2倍扩容，是因为push_back插入的元素个数是固定的。

假设size=n,capacity=m,新插入元素个数t。

1.t<m-n,此时不会发生扩容。

2.m-n<t<n，此时会按照两倍size进行扩容。

3.m-n<t<m,t>n，此时按照t+n进行扩容。

4.t>m，此时按照t+n进行扩容。

```C++
void test(){
    vector<int> vec={1,2,3};
    cout<<"原始容量:"<<vec.capacity()<<endl;//3
    cout<<"原始容器大小:"<<vec.size()<<endl;//3
    vec.insert(vec.begin(),1,1);//两倍扩容
    cout<<"======================================="<<endl;
    cout<<"当前容器容量:"<<vec.capacity()<<endl;//6
    cout<<"当前容器大小:"<<vec.size()<<endl;//4
    cout<<"======================================="<<endl;
    vec.insert(vec.begin(),5,1);//按t+n扩容
    cout<<"======================================="<<endl;
    cout<<"当前容器容量:"<<vec.capacity()<<endl;//9
    cout<<"当前容器大小:"<<vec.size()<<endl;//9
    cout<<"======================================="<<endl;
    vec.insert(vec.begin(),3,1);//两倍扩容
    cout<<"======================================="<<endl;
    cout<<"当前容器容量:"<<vec.capacity()<<endl;//18
    cout<<"当前容器大小:"<<vec.size()<<endl;//12
    cout<<"======================================="<<endl;
    vec.insert(vec.begin(),13,1);//t+n扩容
    cout<<"======================================="<<endl;
    cout<<"当前容器容量:"<<vec.capacity()<<endl;//25
    cout<<"当前容器大小:"<<vec.size()<<endl;//25
    cout<<"======================================="<<endl;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730160858998.png" alt="image-20250730160858998" style="zoom: 67%;" />

##### 交换容器元素

**swap()**

```C++
    vec={1,2,3,4,5};
    cout<<"交换前vec:";
    print(vec);
    vector<int> vec2={1,3,5,7};
    cout<<"交换前vec2:";
    print(vec2);
    swap(vec,vec2);
    cout<<"交换后vec:";
    print(vec);
    cout<<"交换后vec2";
    print(vec2);
```

![](C:\Users\34078\Pictures\Screenshots\屏幕截图 2025-07-27 160009.png)



##### 获取首尾元素

front():获取第一个元素

back():获取最后一个元素

```C++
   cout<<"首元素:"<<vec2.front()<<endl;
   cout<<"尾元素:"<<vec2.back()<<endl;
```

![image-20250727160220500](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250727160220500.png)

------



##### emplace_back()和push_back

```C++
#include <iostream>
#include <vector>
using namespace std;
class Point{
public:
    Point(int x,int y)
    :_x(x)
    ,_y(y)
    {
        cout<<"Point(int int)"<<endl;
    }
    Point(const Point &rhs)
    :_x(rhs._x)
    ,_y(rhs._y)
    {
        cout<<"Point (const &rhs)"<<endl;
    }
    Point(Point &&rhs)
    :_x(rhs._x)
    ,_y(rhs._y)
    {
        cout<<"Point(&&rhs)"<<endl;
    }
private:
    int _x;
    int _y;
};
void test(){
    vector<Point> vec;
    cout<<"================"<<endl;
    vec.emplace_back(5,6);
    cout<<"================"<<endl;
    vec.push_back(Point(1,2));
    cout<<"================"<<endl;
    Point p(1,3);
    vec.push_back(p);
    cout<<"================"<<endl;
    vec.emplace_back(1,3);
    cout<<"================"<<endl;
    vec.emplace_back(Point(2,4));
    cout<<"================"<<endl;
    vec.push_back({1,3});
}

int main()
{
 test();
 return 0;
}

```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250728193434246.png" alt="image-20250728193434246" style="zoom:67%;" />

当push_back添加一个类类型时，如果传递的是一个左值此时会调用该类的拷贝构造函数，如果传递的是一个右值此时会调用该类的移动构造函数。

emplace_back(5,6)此时添加元素时，不会调用类的拷贝构造函数和移动构造函数，而是直接调用其构造函数，极大的提高了效率。

##### <font color='red'>list的特殊操作（重要）</font>

**1.reverse()的使用**

用于反置链表。

```C++
void test(){
    list<int> l={1,3,7,8,9,5,4};
    cout<<"list使用reserve()之前:"<<endl;
    print(l);
    cout<<"list使用reserve()之后:"<<endl;
    l.reverse();
    print(l);
}
```

![image-20250728194250141](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250728194250141.png)

**<font color='red'>2.sort()的使用</font>**

默认不指定排序方式，采用升序。

可以指定排序方式

指定方式有三种：std::less，std::greater,自定义排序方式。

**3.unique()**

去除重复连续的函数，因此建议先排序再使用。

```C++
void test1(){
    list<int> l={1,3,3,3,7,8,9,5,5,3};
    cout<<"list使用unique()之前:"<<endl;
    print(l);
    cout<<"list使用unique()之后:"<<endl;
    l.unique();
    print(l);
    cout<<"==================="<<endl;
    l.sort();
    l.unique();
    print(l);
}
```

![image-20250728194924959](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250728194924959.png)

**4.merge()**

在 C++ 中，`std::list` 的 `merge()` 方法用于将**另一个有序链表**合并到当前链表中，并保持合并后的链表仍然有序。这个操作是**原地的**（in-place），且时间复杂度为 **O(n)**，其中 `n` 是两个链表的总长度。

两个链表进行merge的时候，最好两个链表都进行排序，再进行合并，才能保证合并后有序。

```C++
void test2(){
    list<int> l1={1,3,7,8,9,5,4};
    list<int> l2={10，2,4,6};
    cout<<"merage之前:"<<endl;
    cout<<"l1:";
    print(l1);
    cout<<"l2:";
    print(l2);
    l1.sort(); 
    l2.sort(); 
    l1.merge(l2);
    cout<<"merage之后:"<<endl;
    cout<<"l1:";
    print(l1);
    cout<<"l2:";
    print(l2);
}
```

![image-20250728195956765](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250728195956765.png)

![image-20250728200150806](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250728200150806.png)

<font color='red'>**5.splice()**</font>

从一个链表中转移元素到另一个链表中

```C++
//1、移动other链表到另一个链表的某个指定位置前面
void splice(const_iterator pos, list& other);
void splice(const_iterator pos, list&& other);

//2、移动other链表中的某个元素到另一个链表的某个指定位置前面
void splice(const_iterator pos, list& other, const_iterator it);
void splice(const_iterator pos, list&& other, const_iterator it);

//3、移动other链表的一对迭代器范围元素到另一个链表的某个指定位置前面
void splice(const_iterator pos, 
            list& other, const_iterator first, const_iterator last);
void splice(const_iterator pos, 
            list&& other,const_iterator first, const_iterator last);
```

```C++
void test3(){
    list<int> l1={1,3,7,8,9,5,4};
    list<int> l2={10,2,4,6};
    auto pos=l1.begin();
    pos++;
    pos++;
    cout<<*pos<<endl;//7
    l1.splice(pos,l2);
    print(l1);//1 3 10 2 4 6 7 8 9 5 4 
    cout<<"===================="<<endl;
    auto pos2=l1.begin();
    ++pos2;
    ++pos2;
    cout<<*pos2<<endl;//7
    auto it=l2.end();
    --it;
    --it;
    cout<<*it<<endl;//4
    l1.splice(pos2,l2,it);
    print(l1);//1 3 4 7 8 9 5 4 
    cout<<"====================="<<endl;
    auto pos3=l1.begin();
    ++pos3;
    ++pos3;
    cout<<*pos3<<endl;//7
    l1.splice(pos3,l2,l2.begin(),l2.end());
    print(l1);//1 3 10 2 4 6 7 8 9 5 4 
}
```

splice可以在同一个链表中进行操作。

```C++
void test4(){
    list<int> l={1,3,5,7,9,2,4,6,8,10};
    auto pos=l.begin();
    ++pos;
    ++pos;
    cout<<*pos<<endl;//5
    auto first=l.end();
    --first;
    --first;
    --first;
    cout<<*first<<endl;//6
    l.splice(pos,l,first,l.end());//当产生交集时，会出现错误。
    print(l);
}
```

![image-20250728202745519](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250728202745519.png)



#### 关联式容器：

##### **1.set**

**1.查找**

find()

count()

```C++
void test(){
    set<int> s={2,3,2,4,5,1,8};
    print(s);
    //查找
    int ret=s.count(4);
    if(ret){
        cout<<"查找成功"<<endl;
    }else{
        cout<<"查找失败"<<endl;
    }
    auto it=s.find(3);
    if(it!=s.end()){
        cout<<"找到了"<<*it<<endl;
    }else{
        cout<<"查找失败"<<endl;
    }
```

**2.插入**

insert()

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730161326651.png" alt="image-20250730161326651" style="zoom:67%;" />

```C++
    //插入单个元素
    s.insert(1);
    print(s);
    set<int> temp={1,3,5,7,9};
    //插入迭代器范围元素
    s.insert(temp.begin(),temp.end());
    print(s);
    //插入大括号内元素
    s.insert({17,9,10,11});
    print(s);
```

**3.删除**

erase()

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730161507027.png" alt="image-20250730161507027" style="zoom:67%;" />

```C++
    //删除
    s.erase(3);//删除指定key值的元素
    s.erase(s.begin());//删除迭代器位置元素
    print(s);
    auto first=s.begin();
    ++first;
    ++first;
    auto second=s.end();
    --second;
    s.erase(first,second);//删除迭代器范围内元素
    print(s);
```

删除连续的奇数

```C++
void test2(){
    //删除连续奇数
    set<int> s={1,3,5,6,8,9};
    print(s);
    for(auto it=s.begin();it!=s.end();){
        if(*it%2==1){
            it=s.erase(it);
        }else{
            ++it;
        }
    }
    print(s);
}
```

重定向输出错误流的位置

g++ xxx.cpp 2>err.log 

**<font color='red'>4.针对自定义类型的写法（非常重要）</font>**

![image-20250729195029788](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729195029788.png)

对于set而言，如果模板参数中的key类型是内置类型，那么可以不管第二个参数模板Compare,但是如果key类型是自定义类型或者类类型，那么就需要改写第二个模板参数Compare，原因是自定义类型不能比较大小。

实现方法有三种：函数重载，函数对象，特化模板。

```C++
#include <iostream>
#include <set>
#include <cmath>
#include <ostream>
using namespace std;
class Point{
public:
    Point(int x,int y)
        :_x(x)
         ,_y(y)
    {

    }
    double getDistance() const{
        return hypot(_x,_y);
    }
    friend ostream &operator<<(ostream &os,const Point &rhs);
    friend struct ComparePoint;
    friend bool operator <(const Point &lhs,const Point &rhs);
    friend struct less<Point>;
private:
    int _x;
    int _y;
};
ostream &operator<<(ostream &os,const Point &rhs){
    os<<"("<<rhs._x<<","<<rhs._y<<")";
    return os;
}
template <class Container>
void print(const Container &c){
    for(auto &i:c){
        cout<<i<<endl;
    }
}
//函数对象
struct ComparePoint{
    bool operator()(const Point &lhs,const Point &rhs) const {
        if(lhs.getDistance()<rhs.getDistance()){
            return true;
        }
        else if(lhs.getDistance()==rhs.getDistance()){
            if(lhs._x<rhs._x){
                return true;
            }
            else if(lhs._x==rhs._x){
                if(lhs._y<rhs._y){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        else{
            return false;
        }
    }   
};
//运算符重载
bool operator<(const Point &lhs,const Point &rhs){
    cout<<"运算符重载"<<endl;
    if(lhs.getDistance()<rhs.getDistance()){
        return true;
    }
    else if(lhs.getDistance()==rhs.getDistance()){
        if(lhs._x<rhs._x){
            return true;
        }else if(lhs._x==rhs._x){
            if(lhs._y<rhs._x){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    else{
        return false;
    }
}
//特化模板
namespace std{
template<>
    struct less<Point>{
        bool operator()(const Point &lhs,const Point &rhs) const{
            if(lhs.getDistance()<rhs.getDistance()){
                return true;
            }
            else if(lhs.getDistance()==rhs.getDistance()){
                if(lhs._x<rhs._x){
                    return true;
                }else if(lhs._x==rhs._x){
                    if(lhs._y<rhs._x){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
    };
}
void test(){
    set<Point> s;
    s.insert(Point(1,3));
    s.insert(Point(-1,3));
    s.insert(Point(2,2));
    s.insert(Point(2,-2));
    print(s);
}

int main()
{
    test();
    return 0;
}

```

##### **2.multiset**

基本特征：可以存放重复元素，按照key值，升序排序。

**常用操作：**插入（insert），删除（erase），查找（find，count）与set一样。

**bound系列函数**

![image-20250729193233457](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729193233457.png)

**upper_bound:**返回第一个大于给定key值的迭代器。

**lower_bound:**返回第一个大于等于给定key值的迭代器。

**equal_range：**返回的是一个范围的迭代器，第一个迭代器指向的是不小于给定key值的迭代器，第二个迭代器指向的大于给定key值的迭代器

```C++
    multiset<int> s={1,3,5,6,3,8,4,3,8,9};
    auto pos=s.upper_bound(8);
    cout<<*pos<<endl;//9
    auto pos1=s.lower_bound(8);
    cout<<*pos1<<endl;//8
    while(pos1!=pos){
        cout<<*pos1<<endl;//8 8 
        ++pos1;
    }
    auto ret=s.equal_range(3);
    while(ret.first!=ret.second){
        cout<<*ret.first<<" ";
        ++ret.first;
    }
    cout<<endl;
```

!(C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729193951606.png)

![image-20250729193955105](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729193955105.png)

**针对自定义类型**

![image-20250729194156402](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729194156402.png)

对于multiset而言，如果模板参数中的Key类型是内置类型，那么可以不用管第二个模板参数Compare，但是如果Key类型是自定义类型或者类类型，那么就需要改写第二个模板参数Compare，原因是自定义类型不能比较大小，所以改写的方式有三种：模板的特化、运算符重载、函数对象的写法。

##### 3.map

**基本特征：**

不可以存放相同key值的key-Value，但是value值不唯一。按照key值，升序排序。底层实现是红黑树。

**常用操作：**

构建pair的三种方式

```C++
map<int,string> m={
   pair<int,string>(1,"Beijing"),
    pair<int,string>(1,"hubei"),
    make_pair(3,"jiangxi"),
    make_pait(2,"hunan"),
    {5,"shenzhen"},
    {6,"shanghai"}
}
```

![image-20250729141600379](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729141600379.png)

**insert**

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730162039890.png" alt="image-20250730162039890" style="zoom:67%;" />

插入单个元素，此时insert函数的返回值是一个pair（第一个对象成员是map元素相应的迭代器，第二个对象成员是bool值）。

```C++
  map<int,string> m={
        pair<int,string>(1,"beijing"),
        pair<int,string>(1,"nanjing"),
        make_pair(3,"shanghai"),
        make_pair(2,"shenzhen"),
        {5,"wuhan"},
        {7,"nanchang"}
    };
    print(m);
    auto it=m.insert(make_pair(10,"hunan"));//1.插入单个元素
    if(!it.second){
        cout<<"插入失败"<<endl;
    }else{
        cout<<"插入成功"<<endl;
    }
    cout<<"======================"<<endl;
    m.insert({{8，"jl"},{9,"heb"},{10,"gd"}});//2.插入大括号范围的元素
    print(m);

    cout<<"======================"<<endl;
    map<int,string> city={{3,"jx"},{4,"zj"},{11,"js"}};//3.插入迭代器范围内的元素
    m.insert(city.begin(),city.end());
    print(m);
```

**erase**

![image-20250729142327892](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729142327892.png)

map可以删除迭代器指向的一个元素、迭代器范围的元素、按照key值进行删除。

```C++
map<int,string> m={
        pair<int,string>(1,"Beijing"),
        pair<int,string>(1,"hubei"),
        make_pair(3,"jiangxi"),
        make_pair(2,"hunan"),
        {5,"shenzhen"},
        {6,"shanghai"}
    };
    m.erase(1);
    print(m);
    cout<<"===================="<<endl;
    auto pos=m.begin();
    ++pos;
    ++pos;
    m.erase(pos,m.end());
    print(m);
    cout<<"===================="<<endl;
```

![image-20250729194815714](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729194815714.png)

**下标操作**

```C++
cout<<m[2]<<endl;//hunan 此时下标不是从0开始，而是一个key值。
cout<<m[4]<<endl;//会直接插入一个新的元素，key=4 value=""。
m[6]="nanjing";//将原先的value值修改为nanjing。
```

**针对自定义数据类型**

![image-20250729194937799](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729194937799.png)

map针对于自定义类型的时候，<span style=color:red;background:yellow;font-size:20px>**注意：这里只管Key与T类型是没有关系的**</span>。如果模板参数中的Key类型是内置类型，那么可以不用管第三个模板参数Compare，但是如果Key类型是自定义类型或者类类型，那么就需要改写第三个模板参数Compare，原因是自定义类型不能比较大小，所以改写的方式有三种：模板的特化、运算符重载、函数对象的写法。

```C++
#include <iostream>
#include <map>
#include <cmath>
#include <ostream>
using namespace std;
class Point{
public:
    Point(int x,int y)
        :_x(x)
         ,_y(y)
    {

    }
    double getDistance() const{
        return hypot(_x,_y);
    }
    friend ostream &operator<<(ostream &os,const Point &rhs);
    friend bool operator<(const Point &lhs,const Point &rhs);
    friend struct myCompare;
    friend struct less<Point>;
private:
    int _x;
    int _y;
};

template <class Container>
void print(const Container &c){
    for(auto &it:c){
        cout<<it.first<<" "<<it.second<<endl;
    }
}
ostream &operator<<(ostream &os,const Point &rhs){
    os<<"("<<rhs._x<<","<<rhs._y<<")";
    return os;
}

bool operator<(const Point &lhs,const Point &rhs){
    cout<<"operator<"<<endl;
    if(lhs.getDistance()>rhs.getDistance()){
        return true; 
    }
    else if(lhs.getDistance()==rhs.getDistance()){
        if(lhs._x>rhs._x){
            return true;
        }
        else if(lhs._x==rhs._x){
            if(lhs._y>=rhs._y){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}
struct myCompare{
    bool operator()(const Point &lhs,const Point &rhs) const{
        cout<<"myCompare"<<endl;

        if(lhs.getDistance()>rhs.getDistance()){
            return true; 
        }
        else if(lhs.getDistance()==rhs.getDistance()){
            if(lhs._x>rhs._x){
                return true;
            }
            else if(lhs._x==rhs._x){
                if(lhs._y>=rhs._y){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }

    }

};
namespace std{
template<>
    struct less<Point>{
        bool operator()(const Point &lhs,const Point &rhs) const{
            if(lhs.getDistance()>rhs.getDistance()){
                return true; 
            }
            else if(lhs.getDistance()==rhs.getDistance()){
                if(lhs._x>rhs._x){
                    return true;
                }
                else if(lhs._x==rhs._x){
                    if(lhs._y>=rhs._y){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{
                return false;
            }

        }
    };
}
void test(){
    map<Point,int,myCompare> m={
        {Point(2,-2),1},
        {Point(2,2),3},
        {Point(1,-1),2},
        {Point(1,1),4}
    };
    print(m);
}
int main()
{
    test();
    return 0;
}

```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730170215026.png" alt="image-20250730170215026" style="zoom:67%;" />

##### 4.multimap

**基本特征：**

key值不唯一，可以重复

value值既可以重复，也可以不重复。

默认按key值升序排序。

**其它操作：**

count,find,erase，insert与map基本一样。

**<font color='red'>不支持下标操作</font>**，因为存在相同的key值，访问会出现二义性。

**针对自定义数据类型**

![image-20250729195153650](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729195153650.png)

map针对于自定义类型的时候，<span style=color:red;background:yellow;font-size:20px>**注意：这里只管Key与T类型是没有关系的**</span>。如果模板参数中的Key类型是内置类型，那么可以不用管第三个模板参数Compare，但是如果Key类型是自定义类型或者类类型，那么就需要改写第三个模板参数Compare，原因是自定义类型不能比较大小，所以改写的方式有三种：模板的特化、运算符重载、函数对象的写法。

##### <font color='red'>5.关联式容器的使用总结</font>

1.元素是有序的。

2.底层实现都是红黑树。

3.只要带了multi开头的，key值都可以是重复的，否则key值是唯一的。

4.只有map具备下标，其它三种关联式容器不具备下标。

5.对于自定义类型而言，都需要考虑模板参数Compare，特别注意：Compare只关注Key类型。

#### 无序关联式容器：  

哈希相关概念

**1.哈希函数**

```C++
index=H(key)
```

通过哈希函数，可以找到key值在哈希表中的位置。

**2.哈希函数的构造**

- 定址法：  H(key) = a * key + b；

- 平方取中法： key^2 = 1234^2 = 1522756 ------>227；

- 数字分析法：H(key) = key % 10000；

- 除留取余法：H(key) = key mod p  (p <= m, m为表长)；

**3.哈希冲突**

```C++
H(key1)=H(key2) key1!=key2
```

不同的key值通过哈希函数进行运算之后，在哈希表的位置值一样，这种情况称为哈希冲突。

**4.解决哈希冲突**

- 开放定址法；
- <span style=color:red;background:yellow>链地址法 (推荐使用这种，这也是STL中使用的方法)；</span>
- 再散列法；
- 建立公共溢出区；

**5.装载因子**

a=元素个数/表的长度(元素的个数往往都要小于表的长度)。

如果a的大小比较大，那么哈希冲突的概率会比较高，空间利用率也会比较高，如果a的大小比较小，那么哈希冲突的概率比较低，但是空间利用率也比较低。大概在0.5~0.75之间。

##### 1.unorder_set

**1.基本特征**

- 存放的是key类型，key值是唯一的，不能重复。
- key值没有顺序。
- 底层是哈希。

**2.其它操作**

unorder_set的初始化，遍历，insert(插入)，erase(删除)，count,find(查找)与set的操作一样。

**<font color='red'>3.针对自定义数据类型</font>**

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729195527133.png" alt="image-20250729195527133" style="zoom: 67%;" />

unorder_set针对自定义类型的时候，有两个模板参数Hash与keyEqual,如果key类型是内置数据类型，此时无需改写，因为常见的内置类型都已经针对hash做了特化，或者可以直接比较是否相等，<font color='red'>**如果key类型是自定义类型或者类类型，那么需要改写Hash与KeyValue**</font>，**原因是自定义类型不能设置哈希函数以及设置比较是否相等**。

对于Hash而言，改写方式有两种：特化模板，函数对象。

```C++
//特化模板
namespace std{
template<>
    struct hash<Point>{
        bool operator()(const Point &lhs) const{
        cout<<"hash<Point>"<<endl;
        return (lhs.getX()*1)^(lhs.getY()*2);
    }
    };
}
//函数对象
struct HashPoint{
    bool operator()(const Point &lhs) const{
        cout<<"HashPoint"<<endl;
        return (lhs.getX()*1)^(lhs.getY()*2);
    }
};
```

对于KeyValue而言有三种改写方式：特化模板，函数对象，函数重载。

```C++
//函数重载
bool operator==(const Point &lhs,const Point &rhs){
    cout<<"bool operator=="<<endl;
    return ((lhs.getX())>rhs.getX())&&(lhs.getY()>rhs.getY());
}
//函数对象
struct myequal{
    bool operator()(const Point &lhs,const Point &rhs) const{
        cout<<"myequal"<<endl;
        return ((lhs.getX())==rhs.getX())&&(lhs.getY()==rhs.getY());
    }
};
//特化模板
namespace std{
template<>
    struct equal_to<Point>{
        bool operator()(const Point &lhs,const Point &rhs) const{
           cout<<"equal_to<Point>"<<endl;
           return ((lhs.getX())==rhs.getX())&&(lhs.getY()==rhs.getY());
         }
    };
}
```

##### 2.unorderd_multiset

**1.基本特征**

- 存放的是key类型，key值不唯一，可以重复。
- key值没有顺序。
- 底层使用的是哈希。

**2.其它操作**

unorderd_multiset的查找（count，find），插入（insert），删除（erase）在使用上与multiset是完全一样的。

**3.针对自定义类型**

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729195640930.png" alt="image-20250729195640930" style="zoom: 67%;" />

unorderd_multiset针对自定义类型的时候，有两个模板参数Hash与keyEqual,如果key类型是内置数据类型，此时无需改写，因为常见的内置类型都已经针对hash做了特化，或者可以直接比较是否相等，**如果key类型是自定义类型或者类类型，那么需要改写Hash与KeyValue，原因是自定义类型不能设置哈希哈函数以及比较是否相等**

改写方式与unordered_set一样。

##### 3.unordered_map

**1.基本特征**

- 存放的是key-value，key值唯一，不能重复，但是value可以重复
- key值没有顺序
- 底层使用的是哈希

**2.其它操作**

**unordered_map**的查找（count、find）、插入（insert）、删除（erase）在使用上与map是完全一样的。

**3.支持下标操作**

```C++
   unordered_map<int,string> m={
        pair<int,string>(1,"Beijing"),
        pair<int,string>(1,"hubei"),
        make_pair(3,"jiangxi"),
        make_pair(2,"hunan"),
        {5,"shenzhen"},
        {6,"shanghai"}
    };
    print(m);
    cout<<"================"<<endl;
    cout<<m[3]<<endl;
    cout<<m[4]<<endl;
    cout<<"================"<<endl;
    print(m);
    cout<<"================"<<endl;
    m[2]="zhejiang";
    print(m);
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729200456976.png" alt="image-20250729200456976" style="zoom:50%;" />

总结：**unordered_map**的下标传递的是key类型，unordered_map的下标具备查找、插入、修改的功能，所以功能比较丰富，但是需要注意：下标访问运算符重载的时候，没有const版本的。

**4.针对自定义类型**

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250729200649303.png" alt="image-20250729200649303" style="zoom:67%;" />

**unordered_map**针对于自定义类型的时候，有两个模板参数Hash与KeyEqual，如果Key类型是内置类型，此时无需改写，因为常见的内置类型都已经针对hash做了特化，或者可以直接比较是否相等。<span style=color:red;background:yellow;font-size:20px>如果Key类型是自定义类型或者类类型，那么需要改写Hash与KeyEqual，原因是自定义类型不能设置哈希函数以及比较是否相等。</span>改写的方式与unordered_set是完全一样。

##### 4.unordered_multimap

**1.基本特征**

- 存放的是key-value，key值不唯一，可以重复。
- key值没有顺序
- 底层使用的是哈希

**2.其它操作**

**unordered_multimap**的查找（count、find）、插入（insert）、删除（erase）在使用上与map是完全一样的。

**3.针对自定义类型**

unorderd_multiset针对自定义类型的时候，有两个模板参数Hash与keyEqual,如果key类型是内置数据类型，此时无需改写，因为常见的内置类型都已经针对hash做了特化，或者可以直接比较是否相等，**如果key类型是自定义类型或者类类型，那么需要改写Hash与KeyValue，原因是自定义类型不能设置哈希哈函数以及比较是否相等**。**<font color='red'>改写方式与unordered_set一致。</font>**

##### **5.无序关联式容器的使用总结**

#### <font color='red'>容器的选择（重要）</font>

##### 1.元素是否有顺序

- 首先选择的是关联式容器；
- 不应该选择的是无序关联式容器；
- 其次选择的是序列式容器，因为list有sort函数进行排序，vector与deque可以使用算法库中的sort函数进行排序；

##### 2.容器是否支持下标

序列式容器：vector,deque；

关联式容器：map;

无序关联式容器：unordered_map;

##### 3.查找的时间复杂度

序列式容器：O(N);

关联式容器：O(logN);

无序关联式容器：O(1);

##### 4.迭代器的类型

随机访问迭代器：vector，deque，

双向迭代器：list，关联式容器；

前向迭代器：无序关联式容器；

#### 容器适配器

适配器有三种，对于容器而言有容器适配器，而STL中列举出来的容器适配器有三种stack（栈）、deque（队列）、priority_queue（优先级队列）。

##### 优先级队列

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730194419881.png" alt="image-20250730194419881" style="zoom:67%;" />

priority_queue的底层实现原理：堆排序，默认大根堆。

**大根堆构建步骤**

当有新元素插入的时候，会将堆顶与新插入的元素进行比较，如果堆顶比新插入的元素要小，也就是满足std：less，那么新插入的元素会作为新的堆顶。当堆顶比新插入的元素要大的时候，那么就不满足std：less，那么久的堆顶依旧是堆顶。

##### 优先级队列的初始化

主要有三种方式：创建无参对象、拷贝构造或者移动构造、迭代器范围。<span style=color:red;background:yellow;>注意：没有大括号范围的初始化方式</span>

```C++
void test(){
    //1.创建无参对象
    priority_queue<int> pque;
    print(pque);
    //2.迭代器范围
    vector<int> vec={1,4,8,3,5};
    priority_queue<int> pque1(vec.begin(),vec.end());
    print(pque1);
    //3.拷贝构造或者移动构造
    priority_queue<int> pque2(pque1);
    print(pque2);
    priority_queue<int> pque3(move(pque1));
    print(pque3);
}
```

![image-20250730200513784](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730200513784.png)

##### 优先级队列的遍历

<span style=color:red;background:yellow;>注意：优先级队列是没有迭代器与下标操作的，所以是不能使用传统的方式进行遍历，但是可以通过判断优先级队列是不是为空进行遍历。</span>

```C++
template <class Container>
void print(Container c){
    while(!c.empty()){
        cout<<c.top()<<" ";
        c.pop();
    }
    cout<<endl;
}
```



##### 优先级队列常用函数

**插入与删除**

```C++
//将给定的元素value插入到容器中（传递左值或者右值都可以）
void push( const value_type& value);
void push( value_type&& value);

//删除顶部元素(删除优先级最高的元素，即堆顶元素)
void pop();
```

**获取顶部元素**

```C++
//获取顶部元素（也就是优先级最高的元素）
const_reference top() const;
```

**其他操作**

```C++
//交换两个优先级队列中的元素内容
void swap( priority_queue& other);

//向优先级队列中存入元素
template< class... Args >
void emplace( Args&&... args );
```

**优先级队列针对内置数据类型**

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730202225681.png" alt="image-20250730202225681" style="zoom:67%;" />

```C++
void test2(){
    vector<int> number{2, 3, 6, 8, 9, 1, 4, 7, 5};
    priority_queue<int, vector<int>, greater<int>> pque;
    for(size_t idx = 0; idx != number.size(); ++idx)
    {
        pque.push(number[idx]);
        cout << "当前优先级队列中，优先级最高的元素是: " << pque.top() << endl;
    }
    while(!pque.empty())
    {
        cout << pque.top() << " ";
        pque.pop();
    }
    cout << endl;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730202156279.png" alt="image-20250730202156279" style="zoom:67%;" />

**优先级队列针对自定义数据类型**

```C++
//函数重载
bool operator<(const Point &lhs,const Point &rhs){
    if(lhs.getDistance()<rhs.getDistance()){
        return true;
    }
    else if(lhs.getDistance()==rhs.getDistance()){
        if(lhs.getX()<rhs.getX()){
            return true;
        }
        else if(lhs.getX()==rhs.getX()){
            if(lhs.getY()<rhs.getY()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}
//函数对象
struct myCompare{
    bool operator()(const Point &lhs,const Point &rhs) const{

        if(lhs.getDistance()<rhs.getDistance()){
            return true;
        }
        else if(lhs.getDistance()==rhs.getDistance()){
            if(lhs.getX()<rhs.getX()){
                return true;
            }
            else if(lhs.getX()==rhs.getX()){
                if(lhs.getY()<rhs.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};
//模板特化
namespace std{
template<>
    struct less<Point>{
        bool operator()(const Point &lhs,const Point &rhs) const{
            if(lhs.getDistance()<rhs.getDistance()){
                return true;
            }
            else if(lhs.getDistance()==rhs.getDistance()){
                if(lhs.getX()<rhs.getX()){
                    return true;
                }
                else if(lhs.getX()==rhs.getX()){
                    if(lhs.getY()<rhs.getY()){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
    };
}
void test(){
    vector<Point> number = {
        Point(1, 2),
        Point(3, 4),
        Point(-1, 2),
        Point(5, 6),
        Point(0, 2),
        Point(-3, 2),
        Point(7, 8),
    };

    priority_queue<Point, vector<Point>> pque;

    for(size_t idx = 0; idx != number.size(); ++idx)
    {
        pque.push(number[idx]);
        cout << "当前优先级队列中，优先级最高的元素 : " << pque.top() << endl;
    }

    while(!pque.empty())
    {
        cout << pque.top() << " ";
        pque.pop();
    }
    cout << endl;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250730205437654.png" alt="image-20250730205437654" style="zoom:67%;" />



### 迭代器

具备指针的功能，可以访问容器中的元素，迭代器是一种泛型指针。

是容器与算法之间的 “桥梁”，负责数据的访问。迭代器模拟了指针的行为，提供了统一的接口（如 `*` 解引用、`++` 递增）来遍历容器中的元素，屏蔽了不同容器内部数据结构的差异。

#### 1、基本概念

迭代器(iterator)模式又称为游标(Cursor)模式，用于提供一种方法顺序访问一个聚合对象中各个元素, 而又不需暴露该对象的内部表示。就是使用迭代器访问容器中的元素。

#### 2、分类

输入迭代器(InputIterator)、输出迭代器(OutputIterator)、前向迭代器(ForwardIterator)、双向迭代器(BidirectionalIterator)、随机访问迭代器(RandomAccessIterator)。

每个迭代器类型对应的操作。

| 类别<br />简写 | 输出<br />output | 输入<br />input | 前向<br />Forward | 双向<br />Bidirection | 随机<br />Random |
| :------------: | :--------------: | :-------------: | :---------------: | :-------------------: | :--------------: |
|       读       |                  |       =*p       |        =*p        |          =*p          |       =*p        |
|      访问      |                  |       ->        |        ->         |          ->           |      -> []       |
|       写       |       *p=        |                 |        *p=        |          *p=          |       *p=        |
|      迭代      |        ++        |       ++        |        ++         |         ++/--         | ++/--/+/-/+=/-=  |
|      比较      |                  |      ==/!=      |       ==/!=       |         ==/!=         | ==/!=/</>/<=/>=  |

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250731200220551.png" alt="image-20250731200220551" style="zoom: 67%;" />

每个容器所对应的迭代器类型

|        容器        | 类内迭代器类别 |
| :----------------: | :------------: |
|       vector       | 随机访问迭代器 |
|       deque        | 随机访问迭代器 |
|        list        |   双向迭代器   |
|        set         |   双向迭代器   |
|      multiset      |   双向迭代器   |
|        map         |   双向迭代器   |
|      multimap      |   双向迭代器   |
|   unordered_set    |   前向迭代器   |
| unordered_multiset |   前向迭代器   |
|   unordered_map    |   前向迭代器   |
| unordered_multimap |   前向迭代器   |

#### **3.流迭代器**

流迭代器是特殊的迭代器，可以将输入/输出流作为<span style=color:red;>**容器**</span>看待(因为输入输出都有<span style=color:red;>**缓冲区**</span>的概念)。因此，任何接受迭代器参数的算法都可以和流一起工作。

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250731200503059.png" alt="image-20250731200503059" style="zoom: 50%;" />

<img src="C:\Users\34078\Pictures\Screenshots\屏幕截图 2025-07-31 200809.png" style="zoom: 50%;" />

**1.输入/输出流迭代器的构造方法**

```C++
//输入流迭代器的构造函数
constexpr istream_iterator();
istream_iterator( istream_type& stream );
istream_iterator( const istream_iterator& other ) = default;
//输出流迭代器的构造函数
ostream_iterator(ostream_type& stream, const CharT* delim);
ostream_iterator(ostream_type& stream);
```

**2.输入/输出流迭代器的使用**

`std::copy` 是 C++ 标准库中一个非常实用的泛型算法，定义在 `<algorithm>` 头文件中。它的主要功能是将一个范围内的元素复制到另一个目标位置，是容器间数据传递的常用工具。

```cpp
template< class InputIt, class OutputIt >
OutputIt copy( InputIt first, InputIt last, OutputIt d_first );
```

- **参数**：
  - `first, last`：输入范围的迭代器（`[first, last)`），指定要复制的元素范围
  - `d_first`：目标范围的起始迭代器，指定复制的目标位置
- **返回值**：
  - 指向目标范围中最后一个复制元素之后位置的迭代器

**工作原理：**

`std::copy` 会遍历 `[first, last)` 范围内的所有元素，将每个元素依次复制到以 `d_first` 开始的目标位置。

```C++
void test{
    vector<int> vec;
    istream_iteritor<int> isi(cin);
    copy(isi,istream_iterator<int>(),back_inserter(vec));
    copy(vec.begin(),vec.end(),ostream_iterator<int>(cout,"  "));
    cout<<endl;
}
```

![image-20250731202437083](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250731202437083.png)

**3.三组插入迭代器**

std::back_inserter是函数模板，该函数模板的返回结果是类模板back_insert_iteritor,而类模板的底层重载赋值运算符函数，该函数的实现是调用容器的push_back函数。

std::front_inserter是函数模板，该函数模板的返回结果是类模板front_insert_iteritor,而类模板的底层重载赋值运算符函数，该函数的实现是调用容器的push_front函数。

inserter是函数模板，该函数模板的返回结果是类模板insert_iteritor,而类模板的底层重载赋值运算符函数，该函数的实现是调用容器的insert函数。

```c++
void test3(){
    vector<int> vec={1,3,5,7,9};
    list<int> l={2,4,6,8,10};
    //1.将list中的所有元素插入vector的尾部
    copy(l.begin(),l.end(),back_inserter(vec));
    copy(vec.begin(),vec.end(),ostream_iterator<int>(cout,"  "));
    cout<<endl;
    cout<<"===================================="<<endl;

    //2.将vector中的所有元素插入list的头部
    copy(vec.begin(),vec.end(),front_inserter(l));
    copy(l.begin(),l.end(),ostream_iterator<int>(cout,"  "));
    cout<<endl;
    cout<<"===================================="<<endl;

    //3.将vector中的所有元素插入到set中
    set<int> s;
    copy(vec.begin(),vec.end(),inserter(s,s.begin()));
    copy(s.begin(),s.end(),ostream_iterator<int> (cout,"  "));
    cout<<endl;
    cout<<"===================================="<<endl;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250731203557165.png" alt="image-20250731203557165" style="zoom: 80%;" />

#### **反向迭代器**

反向迭代器（`std::reverse_iterator`）是 C++ 标准库提供的一种迭代器适配器，用于**反向遍历容器元素**（从尾到头）。它可以将普通迭代器（正向迭代器）转换为反向迭代器，使得我们可以像正向遍历一样便捷地进行反向遍历。

##### 核心特性

- 反向迭代器通过 `rbegin()` 和 `rend()` 获得（容器提供这两个成员函数）
- `rbegin()` 指向容器的最后一个元素，`rend()` 指向容器第一个元素的前一个位置
- 递增反向迭代器（`++it`）实际上是向容器的起始方向移动
- 递减反向迭代器（`--it`）实际上是向容器的末尾方向移动

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250731203714688.png" alt="image-20250731203714688" style="zoom: 80%;" />

```C++
void test3(){
    vector<int> vec;
    vector<int> dest;
    istream_iterator<int> isi(cin);
    copy(isi,istream_iterator<int>(),back_inserter(vec));
    copy(vec.rbegin(),vec.rend(),back_inserter(dest));
    copy(dest.begin(),dest.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
}

```

![image-20250731205557902](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250731205557902.png)

```c++
void test4(){
    vector<int> vec={1,3,5,7,9};

    vector<int>::reverse_iterator it1=vec.rbegin();
    vector<int>::reverse_iterator it2=vec.rend();
    for(it1;it1!=it2;++it1){
        cout<<*it1<<" ";
    }
    cout<<endl;
}
```

![image-20250731205612265](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250731205612265.png)

### 算法

对容器中的元素进行相应的操作。

在STL中，算法库中的算法都是属于普通函数，也就是非成员函数。

非修改式的序列操作：count，find，for_each;

修改式的序列操作：copy，remove，swap，remove_if，

排序操作：sort

二分搜索：lower_bound,upper_bound；

集合操作：set_intersection,set_union

堆相关的操作：make_heap，push_heap;

数值操作：accumulate

求最值：max，min

未初始化的内存操作：uninitialized_copy

#### for_each算法

一元函数：函数的参数只有一个，二元函数：函数的参数有两个。

一元断言/谓词：函数的参数只有一个，并且函数的返回类型是bool。

二元断言/谓词：函数的参数只有两个，并且函数的返回类型是bool。

```cpp
template< class InputIt, class UnaryFunction >
UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );
```

- **参数**：
  - `first, last`：迭代器范围 `[first, last)`，指定要遍历的元素范围
  - `f`：一元函数（可调用对象），将对范围内的每个元素执行此函数（参数为元素值）
- **返回值**：
  - 执行完所有操作后的函数对象 `f`（可用于获取函数对象的状态）

**核心功能**

对 `[first, last)` 范围内的每个元素 `element`，调用 `f(element)`，即对每个元素应用函数 `f`。

```C++
void test(){
    vector<int> vec={1,2,3,4,5};
    for_each(vec.begin(),vec.end(),[](int x){
    cout<<x<<" ";
    });//输出1，2，3，4，5
cout<<endl;
}
```



#### lambda表达式（匿名函数）

##### 1.基本语法规则

```C++
[ ](){}()
//[]是捕获列表
//()函数的参数列表
//{}函数的函数体
//()表示立即调用该 lambda 表达式（定义后直接执行）,没加则表示只定义
//在lambda表达式的函数体中，不能直接访问外部的局部变量，除非在捕获列表中进行捕获。
```

##### 2.**两种捕获方式**

**1.值捕获：**将外部局部变量以值传递的方式在lambda表达式中进行访问（也就是拷贝到lambda表达式中），此时不可以对该变量进行修改，如果一定要进行修改，可以使用mutable关键字进行修饰，但是修改的是副本，对外部变量没有影响。

```C++
void test(){
    int num=10;
    [num](int value) mutable{
        num++//error，直接使用会错误，需加上mutable
        value++;
        cout<<value<<endl;//101
        cout<<num<<endl;//11
    }(100)
    cout<<num<<endl;//10
}
```

**2.引用捕获：**可以将外部局部变量以引用的方式在lambda表达式中进行访问，但是此时可以在lambda表达式中对引用捕获的变量进行修改，因为是引用，所以外部该变量也会修改。

```C++
void test(){
    int num=10;
    [&num](int value){
        num++;
        value++;
        cout<<value<<endl;//101
        cout<<num<<endl;//11
    }(100)
    cout<<num<<endl;//101
}
```

##### 3.**混合捕获**

全部的外部局部变量是值捕获，可以采用[=]

全部的外部局部变量是引用捕获，可以采用[&]

如果外部局部变量，只有一个是引用捕获，其它全部是值捕获，可以使用[=,&num];

如果外部局部变量，只有一个是值捕获，其它全部是引用捕获，可以使用[&,num];

<font color='red'>**全局变量和静态变量不需要使用捕获，可以直接在lambda表达式的函数体中进行使用。**</font>

```C++
void test1(){
    int a=3,b=4,c=5;
    [&,c](){
        a++;
        b++;
        /* c++; */
        globalnum++;
        cout<<globalnum<<endl;
        cout<<a<<" "<<b<<" "<<c<<endl;
    }();
    cout<<a<<" "<<b<<" "<<c<<endl;
    cout<<globalnum<<endl;
    cout<<"============================"<<endl;
    static int num=10;
    [=,&c](){
        c++;
        num++;
        cout<<num<<endl;
        cout<<c<<endl;
    }();
    cout<<a<<" "<<b<<" "<<c<<endl;
    cout<<num<<endl;

}
```

![image-20250731220544180](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250731220544180.png)

<font color='red'>**[this]捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数同样的访问权限，可以修改类的成员变量，使用类的成员函数。如果已经使用了&或者=，默认添加次选项。**</font>

##### 4.lambda的本质

**lambda表达式的类型在c++11中会被看做是一个带operator()的类，即函数对象。**

按照C++标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量值的。mutable选项的作用就在于取消operator()的const属性 。

小网站：`https://cppinsights.io/`

##### 5.lambda表达式的使用误区

在使用lambda表达式的时候，不要捕获可能销毁的局部变量的引用，因为如果局部变量销毁了，但是使用的是引用捕获的话，那么会出现错误。但是如果使用值捕获，即使局部变量销毁了，也没有问题。

```C++
#include <iostream>
#include <vector>
#include <functional>
using namespace std;
vector<function<void (const string &)>> vec;
void test(){
    int num=10;
    string name="www";
    vec.push_back([&num,&name](const string &value){
        cout<<"num="<<num<<endl;
        cout<<"name="<<name<<endl;
        cout<<"value="<<value<<endl;
    });

    for(auto &elem:vec){
        elem("hello");
    }
    cout<<endl;
    cout<<endl;
}
void test2(){
    for(auto &elem:vec){
        elem("hello");
    }
}
int main()
{
 test();
 test2();
 return 0;
}

```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250801174007906.png" alt="image-20250801174007906" style="zoom:67%;" />

#### remove_if()算法

remove_if并不能一次将满足条件的元素进行删除，但是会返回一个指向待删除元素迭代器，再通过erase操作就可以实现删除多余元素。

```C++
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void test(){
    vector<int> vec={1,3,5,7,9,2,4,6,8,10};

    auto it=remove_if(vec.begin(),vec.end(),[](int val){
              return val>5;
              });

    vec.erase(it,vec.end());//没有这一行将输出1 3 5 2 4 2 4 6 8 10 
    //加上之后输出1，3，5，2，4
    for_each(vec.begin(),vec.end(),[](const int &val){cout<<val<<" ";});
    
    cout<<endl;
}
int main()
{
 test();
 return 0;
}
```

##### **bind1st**

可以绑定二元函数对象f，并且将f的第一个参数固定为x。

```c++
void test2(){
    vector <int> vec={1,3,5,4,3,2};
    auto it=remove_if(vec.begin(),vec.end(),bind1st(less<int>(),2));//2<lhs
    vec.erase(it,vec.end());
    for_each(vec.begin(),vec.end(),[](const int &val){cout<<val<<" ";});
    cout<<endl;
    vector <int> vec2={1,3,5,4,3,2};
    auto it2=remove_if(vec2.begin(),vec2.end(),bind1st(greater<int>(),2));//2>lhs
    vec2.erase(it2,vec2.end());
    for_each(vec2.begin(),vec2.end(),[](const int &val){cout<<val<<" ";});
    cout<<endl;
}
```

![image-20250801192538062](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250801192538062.png)

##### **bind2nd**

可以绑定二元函数对象f，并且将f的第二个参数固定为x。

```c++
void test3(){
    vector <int> vec={1,3,5,4,3,2};
    auto it=remove_if(vec.begin(),vec.end(),bind2nd(less<int>(),2));//rhs<2
    vec.erase(it,vec.end());
    for_each(vec.begin(),vec.end(),[](const int &val){cout<<val<<" ";});
    cout<<endl;
    vector <int> vec2={1,3,5,4,3,2};
    auto it2=remove_if(vec2.begin(),vec2.end(),bind2nd(greater<int>(),2));//rhs>2
    vec2.erase(it2,vec2.end());
    for_each(vec2.begin(),vec2.end(),[](const int &val){cout<<val<<" ";});
    cout<<endl;
}
```

![image-20250801192548195](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250801192548195.png)

#### bind

##### 1.绑定函数的形式

bind可以绑定二元函数，也可以绑定三元函数,可以绑定n元函数。

绑定普通函数

绑定成员函数，隐含一个this指针，需绑定一个对象。

绑定静态成员函数，可以不用取地址。

```C++
void print(){
    cout<<"hello c++"<<endl;
}
int add(int a,int b){
    return a+b;
}
int multiply(int a,int b,int c){
    return a*b*c;
}
class Point{
public:
    int _ix=10;
    int _iy=30;
    void print(){
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }
    static int add(int x,int y){
        cout<<"static aadd"<<endl;
        return x+y;
    }
};
void test(){
    auto f=bind(&add,1,2);
    cout<<f()<<endl;
    auto f2=bind(&print);
    f2();
    auto f3=bind(&multiply,3,4,5);
    cout<<f3()<<endl;
    Point p;
    auto f4=bind(&Point::print,&p);
    f4();
    auto f5=bind(Point::add,12,21);
    cout<<f5()<<endl;
}
```

![image-20250801194407290](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250801194407290.png)

##### 2.函数指针

函数指针的声明需要匹配函数的返回类型和参数列表，语法格式为：

```cpp
返回类型 (*指针名)(参数列表);
```

```C++
  //1.定义函数指针
   int (*pfunc)(int,int);
   pfunc=add;//2.绑定函数
   cout<<pfunc(1,3)<<endl;//3.执行函数 4
```

1. **普通函数指针**：
   - 声明时必须严格匹配函数的返回类型和参数列表
   - 赋值时直接使用函数名（函数名即函数地址）
   - 调用方式与直接调用函数相同（`指针名(参数)`）
2. **类成员函数指针**：
   - 声明时需要加上类名限定（`类名::*指针名`）
   - 赋值时必须使用 `&类名::成员函数名` 形式
   - 调用时需要通过对象或对象指针（`对象.*指针` 或 `对象指针->*指针`）

**延迟调用的思想**(c++中多态就是这一种思想，可以提高代码的灵活性)

##### 3.回调函数

在 C++ 中，回调函数是可以作为参数传递给另一个函数，并在某个时机调用的函数。。

回调函数的使用步骤：注册回调函数，执行回调函数。

```C++
pFUnc f=func;//回调函数的注册（交给函数指针）
//todo
//todo
cout<<"f()"<<f()<<endl;//执行回调函数（函数指针的执行间接激活了回调函数的执行）
```

```c++
//1.定义函数指针
typedef int (*pFunc)(int,int);
pFunc f=add;//注册回调函数
cout<<f(3,4)<<endl;//回调函数的执行
```

##### 3.占位符

bind绑定函数的时候，并不需要将所有的参数固定，因为可以使用占位符占据函数的参数。

这些占位符位于 `std::placeholders` 命名空间中，使用时需要显式指定（`std::placeholders::_1`），或通过 `using` 声明简化。

占位符整体代表的是函数的形参。

占位符中的数字代表的是函数的实参。

函数在传递实参的时候，实参的个数一定要大于等于占位符中数字的最大值。

没有使用的参数直接丢弃。

**占位符的使用**

```c++
int multiply(int a,int b,intc){
    return a*b+c;
}
int add(int a,int b){
    return a+b;
}
void test4(){                 
    using namespace std::placeholders;
    //1.固定部分参数          
    //绑定multiply的第一个参数为2，保留后两个参数
    auto func1=bind(multiply,2,_1,_2);
    cout<<func1(3,4)<<endl;//2*3+4
    //2.调整参数顺序          
    auto func2=bind(multiply,_2,_3,_1);
    cout<<func2(3,4,5)<<endl;//4*5+3
    //3.忽略部分参数          
    auto func3=bind(add,_1,5);//4+5                                             
    cout<<func3(4,8,10,20,30)<<endl;
}            
```

bind的默认传递是值传递，如果想使用引用传递，可以使用引用的包装器std::ref，std::cref。

std::ref=reference。

std::cref=cosnt reference。

##### 4.引用折叠

```C++
& &&----------->&
&& &&---------->&&
& &------------>&
&& &----------->&
```

只要有左值引用参与，那么最终的结果就是左值引用，只有同时都是右值引用之后，最终折叠的结果才是右值引用。

##### 5.bind绑定数据成员（了解）

```C++
class Point{
public:
    int _ix=10;
    int _iy=30;
    void print(){
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }
    static int add(int x,int y){
        cout<<"static aadd"<<endl;
        return x+y;
    }
};
void test(){
    Point p;
    auto f=bind(&Point::_ix,&p);
    cout<<f()<<endl;//10
}
```



##### 6.bind绑定成员函数的传参

bind绑定非静态成员函数的时候，第一个参数的位置可以传递地址，也可以传递对象。二者之间的区别是，以内存角度看，地址传递消耗的是一个指针大小，值传递（对象）会有对象大小的开销，从生命周期来看，地址传递的方式，如果对象销毁，会有空指针的使用风险，但是如果是值传递（对象），那么不会有这样的风险，因为已经拷贝了一份副本。

```C++
void test6(){
      Point p;
      auto f=bind(&Point::add,&p,30,40);//地址传递
      cout<<f()<<endl;//70
      auto f1=bind(&Point::add,p,30,40);//值传递
      cout<<f1()<<endl;//70
  }
```

#### functional

`std::function` 是 C++11 引入的一个通用函数包装器（位于 `<functional>` 头文件中），它可以存储、复制和调用任何可调用对象（函数、lambda 表达式、函数对象、成员函数指针等），为各种可调用对象提供了统一的接口。

##### **1.模板型式**

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250801204100384.png" alt="image-20250801204100384" style="zoom:67%;" />

R是函数返回类型，Args是函数参数列表。

##### 2.函数类型

函数的类型（形态，标签）：函数的返回类型与函数的参数列表（参数的个数，顺序，类型）。语法格式为：

```c++
std::function<返回值类型(参数类型1, 参数类型2, ...)> 变量名;
```

##### **3.function接收函数类型**

**基本使用步骤：**

1. 包含头文件 `<functional>`
2. 定义 `std::function` 对象，指定函数签名
3. 赋值可调用对象（函数、lambda 等）
4. 像普通函数一样调用它

```c++
#include <iostream>
#include <functional>
using namespace std;
int add(int a,int b){
    return a+b;
}
void test(){
    function<int()> func=bind(add,3,5);//存储普通函数
    cout<<func()<<endl;//8
}
void test2(){
    function<double(double ,double)> divide=[](double a,double b){//存储lambda表达式
        return a/b;
    };
    cout<<divide(10,2)<<endl;//5.0
}
class Math{
public:
    int multiply(int a,int b){
        return a*b;
    }

};
void test3(){
    Math math;
    using namespace std::placeholders;
    function<int(int,int)> func=bind(&Math::multiply,&math,_1,_2);//存储普通成员函数
    cout<<func(20,30)<<endl;//600
}
void process(int a,int b,function<void(int)> func){//作为函数参数
    int result=a-b;
    func(result);
}
void test4(){
    process(10,3,[](int res){
            cout<<"res="<<res<<endl;//7
            });

}
```

**function+bind 基于对象的形式，实现多态**

```C++
#include <math.h>
#include <iostream>
#include <functional>
using std::function;
using std::cout;
using std::endl;
using std::bind;

class Figure
{
public:
    using DisplayCallback=function<void()>;
    using AreaCallback=function<double()>;
    void setDisplayCallback(DisplayCallback &&dc){
            _display=std::move(dc);
    }
    void setAreaCallback(AreaCallback &&ac){
            _area=std::move(ac);
    }
    void HandleDisplayCallback() const{
        if(_display){
            _display();
        }
    }
    double HandleAreaCallback() const{
        if(_area){
          return _area();
        }else{
            return 0.0;
        }
    }
private:
    DisplayCallback _display;
    AreaCallback _area;

};

class Rectangle
: public Figure
{
public:
    Rectangle(double len = 0, double width = 0)
    : _len(len)
    , _width(width)
    {
        cout << "Rectangle(double = 0, double = 0)" << endl;
    }
    
    ~Rectangle()
    {
        cout << "~Rectangle()" << endl;
    }
    void display(){
        cout<<"矩形:"<<_len<<" "<<_width<<endl;
    }
    double area(){
        return _len*_width;
    }

private:
    double _len;
    double _width;

};

class Circle
: public Figure
{
public:
    explicit
    Circle(double radius = 0)
    : _radius(radius)
    {
        cout << "Circle(double = 0)" << endl;
    }

    ~Circle()
    {
        cout << "~Circle()" << endl;
    }
    void display(){
        cout<<"圆的半径:"<<_radius<<endl;
    }
    double area(){
        return _radius*_radius*3.14;
    }
private:
    double _radius;
};

class Triangle
: public Figure
{
public:
    Triangle(double a = 0, double b = 0, double c = 0)
    : _a(a)
    , _b(b)
    , _c(c)
    {
        cout << "Triangle(double = 0, double = 0, double = 0)" << endl;
    }

    ~Triangle()
    {
        cout <<"~Triangle()" << endl;
    }
    void display(){
        cout<<"三角形边长:"<<_a<<","<<_b<<","<<_c<<endl;
    }
    double area(){
        double tmp = (_a + _b + _c)/2;
        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp -_c));
    }
private:
    double _a;
    double _b;
    double _c;
};

void func(const Figure &ref)
{
    ref.HandleDisplayCallback();
    cout << "面积:" << ref.HandleAreaCallback() << endl;
}

int main(int argc, char **argv)
{
    Rectangle rec(10, 20);
    Circle cir(10);
    Triangle tri(3, 4, 5);
    rec.setDisplayCallback(bind(&Rectangle::display,&rec));
    rec.setAreaCallback(bind(&Rectangle::area,&rec));
    func(rec);
    cir.setDisplayCallback(bind(&Circle::display,&cir));
    cir.setAreaCallback(bind(&Circle::area,&cir));
    func(cir);
    tri.setDisplayCallback(bind(&Triangle::display,&tri));
    tri.setAreaCallback(bind(&Triangle::area,&tri));
    func(tri);
    return 0;
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250801220651992.png" alt="image-20250801220651992" style="zoom:67%;" />

### 适配器

起到适配作用。

**容器的适配器：** stack，queue,pirority_queue。

**迭代器适配器**： back_insert_iteritor。

**函数适配器** ：bind1st,bind2nd,bind,mem_fn.

#### 成员函数适配器mem_fn

```C++
#include <functional>
template< class M, class T >
/*unspecified*/ mem_fn(M T::* pm);

template< class M, class T >
/*unspecified*/ mem_fn(M T::* pm) noexcept;
```

**1.作用：**当成员函数在使用过程中，给成员函数起适配作用。

**2.特点：**因为成员函数与算法库中的算法不能直接很好的适配，所以二者结合使用的时候，需要使用成员函数适配器进行适配。例如：

```C++
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
class Num{
public:
    Num(int n)
    :num(n)
    {

    }
    void print() const {
        cout<<num<<" ";
    }

    bool isEven() const{
        return (num%2==0) ;
    }
    bool isPrime() const{
        if(num==1) return false;
        for(int i=2;i<num/2;++i){
            if(num%i==0){
                return false;
            }
        }
        return true;
    }
private:
    int num;
};
void test(){
    Num num(10);
    auto f=mem_fn(&Num::print);
    f(num);//10
    auto f2=bind(&Num::print,&num);
    f2();//10
    function<void()> f3=bind(&Num::print,&num);
    f3();//10
}
void test2(){
    vector<Num> vec;
    for(int i=1;i<=10;++i){
        vec.push_back(Num(i));
    }

    for_each(vec.begin(),vec.end(),mem_fn(&Num::print));
    cout<<endl;

    auto it=remove_if(vec.begin(),vec.end(),mem_fn(&Num::isEven));
    vec.erase(it,vec.end());
    for_each(vec.begin(),vec.end(),mem_fn(&Num::print));
    cout<<endl;

    vec.erase(remove_if(vec.begin(),vec.end(),mem_fn(&Num::isPrime)),vec.end());
    for_each(vec.begin(),vec.end(),mem_fn(&Num::print));
    cout<<endl;
}

int main()
{
 test2();
 return 0;
}

```

![image-20250802155846109](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250802155846109.png)

### 函数对象

起到定制化的操作。

**只要是可以与小括号进行结合，并且展示出函数含义的，统称函数对象。**

重载了函数调用运算符的类创建的对象。

lambda表达式也是函数对象。

function也是函数对象。

bind的返回结果也是函数对象。

函数指针也是函数对象。

### 空间配置器

管理内存的，管理空间的申请和释放。

空间配置器提供了四个函数，空间申请与释放，对象构建与销毁，也就是将空间的申请与对象的构建分开了。

```c++
//1、空间的申请，申请的是原始的，未初始化的空间
pointer allocate( size_type n, const void * hint = 0 );
T* allocate( std::size_t n, const void * hint);	
T* allocate( std::size_t n );

//2、空间的释放
void deallocate( T* p, std::size_t n );

//3、对象的构建，在指定的未初始化的空间上构建对象，使用的是定位new表达式
void construct( pointer p, const_reference val );

//4、对象的销毁
void destroy( pointer p );
```

**思考：为何要将空间的申请与对象的构建分开？**

在STL中，可能会大量的创建对象，那么如果还是创建一个对象申请一块空间，那么空间申请会非常频繁，所以为了提升效率，并没有采用一个创建对象申请一块空间的方式，而是采用一次性申请一大段空间，然后再到该空间创建对象。

#### 空间配置器的原理

空间配置器分为两级：

一级空间配置器使用类模板malloc_alloc_template,其底层使用malloc/free进行空间的申请和释放。

二级空间配置器使用类模板defalut_alloc_template,其底层根据申请的空间大小分为两个分支

```C++
if(n>128){
    malloc_alloc_template
}else{
    内存池+16个自由链表
}
```

#### 空间配置器的优缺点

一级空间配置器：使用malloc/free系统调用，缺点：频繁的用户态到内核态的切换，开销大(brk,mmap)

二级空间配置器：内存池+16个自由链表，优点：以空间换时间，缺点：内存占用比较大，如果内存有限，内存不可控，这也是早期STL提出时候不被重用的原因，那是内存较小。

#### 释放内存的deallocate

对应一级空间配置器，直接使用free将内存回收到堆空间。

对应二级空间配置器，直接将用完后的空间链回到相应的链表下面，使用头插法进行连接。

#### allocate源码分析

在STL的空间配置器中，有四个核心函数，特别需要研究的就是申请空间的函数allocate（只研究小片空间） allocate函数调用会申请空间，但是该函数的底层会调用S_freelist_index在自由链表下取下标；还会调用 S_round_up函数向上取整得到8的整数倍；allocate函数会调用S_refill函数，但是S_refill函数并不会真正 //申请空间，而是调用S_chunk_alloc申请空间，该函数有可能会递归调用，但是该函数如果要申请空间的话，底层 //还是调用的malloc。

**S_freelist_index函数**：就是在自由链表取下标;

 **S_round_up函数**：向上取整得到8的整数倍;

 **S_refill函数**：将从S_chunk_alloc函数中返回的结果进行切割，然后挂接在对应的自由链表下面;  

**_S_chunk_alloc函数**：申请空间，该函数有可能会递归调用，申请空间的时候使用的是malloc；

chunk_alloc函数以end_free-start_free来判断内存池的空间是否足够，如果空间充足，就直接调出20个区域返回给自由链表。如果不足以提供20个区块，但是还足够供应一个以上的区块，就拨出这不足20个区块的空间出去，并将nobjs参数修改为实际能够供应的区块数，如果连一个区块空间都无法供应，便利用malloc从堆中配置内存。如果系统堆空间也不够了，那么就四处寻找未用区块且足够存放需求的自由链表，找到就挖出一块出来使用。

在STL中，所有的容器的底层申请的都是堆空间.

### **补充知识**

#### **1.class与struct的区别**

1.默认访问权限不同 class的访问权限是private struct的访问权限是public。

2.默认继承方式不同 class的默认继承方式是private继承，struct的默认继承是public继承。

#### 2.类的默认函数

一个类声明会自动生成8个函数

无参构造，拷贝构造，移动构造，赋值运算符函数，移动赋值，const &运算符，非const &运算符，析构函数。

#### 3.模板文件的实现文件和头文件使用

模板文件不要分成头文件和实现文件。

如果要分，需要在头文件中包含实现文件。

```c++
#include xxx.tcc
```

并将实现文件改为xxx.tcc。

#### 4.静态数据成员的使用

静态数据成员需要在类的外部实现。如果涉及到头文件，实现文件，静态数据成员需要在实现文件实现。

在类中实现的成员函数，默认是内联函数。