# c++运算符的重载

<font color='red'>**非常非常重要！！！**</font>

#### 1.友元

由于面向对象的封装性，如果类的数据成员被设置了private修饰访问权限，那么仅有类的内部可以访问这些数据成员，但是如果将某个函数或者某个类设置为当前这个类对象的友元，那么便可以访问私有数据成员，打破封装的限制。

用<font color='red'>**friend**</font>声明友元。

##### **友元的分类：**

友元普通函数

```C++
class Point{
public:
    Point(int x,int y)
    :_x(x)
    ,_y(y)
    {
        
    }
    //此方法破坏封装性
    int getX() const {
        return _x;
    }
    int getY() const{
        return _y;
    }
    //友元 
    friend float distance2(const Point &p1,const Point &p2)；
private:
    int _x;
    int _y;
}
//普通函数 不采用友元
float distance1(const Point &p1,const Point &p2){
    float result=Pow(p1.getX()-p2.getX(),2)+Pow(p1.getY()-p2.getY(),2);
    return sqrt(result);
}
//采用友元
//将当前函数声明为Point的友元
float distance2(const Point &p1,const Point &p2){
    float result=Pow(p1._x-p2._x,2)+Pow(p1._y-p2._y,2);
    return sqrt(result);
}
```

友元成员函数

```C++
#include <iostream>
#include <math.h>
using std::cout;
using std::endl;
using std::cin;
//友元之成员函数
class Point;
class Line{
public:
    float distance(const Point &p1,const Point &p2);
};
class Point{
public:
    Point(int x,int y)
    :_x(x)
    ,_y(y)
    {

    }
     friend float Line::distance(const Point &p1,const Point &p2);

private:
    int _x;
    int _y;
};

float Line::distance(const Point &p1,const Point &p2){
    float result=pow(p1._x+p2._x,2)+pow(p1._y+p2._y,2);
    return sqrt(result);
}
void test(){
    Point p1(1,2);
    Point p2(3,4);
    float result=Line().distance(p1,p2);
    cout<<result<<endl;
}
int main()
{
 test();
 return 0;
}

```

友元类

```C++
class Line{
public:
    float distance(const Point &p1,const Point &p2);
}
class Point{
public:
    Point(int x,int y)
    :_x(x)
    ,_y(y)
    {
        
    }
    friend class Line;
private:
    int _x;
    int _y;
}
//将当前函数声明为Point的友元
float Line::distance((const Point &p1,const Point &p2){
    float result=Pow(p1._x-p2._x,2)+Pow(p1._y-p2._y,2);
    return sqrt(result);
}
```

Line类中的任意成员函数都可以访问到Point类的私有数据成员，权限最大。

##### 友元特点：

1.友元不受类中访问权限的限制

2.友元是单向的。A是B的友元，A可以访问B的数据成员.

3.友元不具有传递性。

4.友元不能被继承，子类不能继承父类的友元。

5.友元破坏了类的封装性。

#### 2.运算符重载

**目的：**使自定义数据类型的操作和内置数据类型保持一致。

**不能重载的运算符包括：**

. 成员访问运算符

.* 成员指针访问运算符

？：三目运算符

：：作用域限定符

sizeof 长度运算符

**规则：**

<font color='red'>**1.其操作数类型必须要有自定义类型或枚举类型**</font>。

**<font color='red'>2.操作符的操作数个数是保持不变的。</font>**

**<font color='red'>3.运算符重载时，不能设置默认参数。</font>**

4.其优先级和结合性还是固定不变的。

5.逻辑与&&，逻辑或||，就不在具有短路求值特性，进入函数体之前必须完成所有函数参数的计算，不推荐重载。

**形式：**

1. <span style=color:red;background:yellow>**采用友元函数的重载形式**</span>
2. 采用普通函数的重载形式
3. <span style=color:red;background:yellow>**采用成员函数的重载形式**</span>

**对于不会修改操作数的值这种类型的操作选择友元函数形式。**

**对于修改操作数的值这种类型的操作采用成员函数形式。**

赋值=，下标[ ]，调用（），成员访问->,成员指针访问->*，必须以成员函数形式重载。

##### +运算符重载

适用于：string，复数类等

运算符重载和普通成员函数的区别和联系？

区别很小，完成的都是同一件事情，只不过使用运算符重载时，使用的是和内置数据类型一样的运算符来进行操作，给人的感觉是相对比较直观的，采用成员函数其实完全可以实现相同功能

**采用普通函数实现运算符重载**

不推荐使用此方法，这样丧失了对私有成员的保护。

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Complex{
public:
     Complex(int real,int image)
     :_real(real)
     ,_image(image)
    {

    }
     int getreal() const{
         return _real;
     }
     int getimage() const{
         return _image;
     }
     void print(){
         cout<<"real="<<_real<<" ,"<<"image="<<_image<<endl;
     }
private:
    int _real;
    int _image;
};
Complex operator+(const Complex &c1,const Complex &c2){
        int real=c1.getreal()+c2.getreal();
        int image=c1.getimage()+c2.getimage();
        Complex temp(real,image);
        return temp;
}
void test(){
    Complex c1(1,2);
    Complex c2(2,1);
    Complex c3=c1+c2;
    c3.print();

}

int main()
{
 test();
 return 0;
}

```

**采用成员函数实现运算符重载**

加法运算符的左操作数实际上就是this指针所指向的对象。

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Complex{
public:
    Complex(int real,int image)
    :_real(real)
    ,_image(image)
    {

    }
    Complex operator+(Complex &rhs){
        return Complex(_real+rhs._real,_image+rhs._image);
    }
    void print(){
        cout<<"实部:"<<_real<<" ,"<<"虚部:"<<_image<<endl;
    }
private:
    int _real;
    int _image;
};
void test(){
    Complex c1(4,3);
    Complex c2(3,4);
    Complex c3=c1+c2;
    c3.print();

}

int main()
{
 test();
 return 0;
}

```

采用友元函数实现运算符重载

```c++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Complex{
public:
     Complex(int real,int image)
     :_real(real)
     ,_image(image)
    {

    }
   friend  Complex operator+(const Complex &c1,const Complex &c2);
     void print(){
         cout<<"real="<<_real<<" ,"<<"image="<<_image<<endl;
     }
private:
    int _real;
    int _image;
};
Complex operator+(const Complex &c1,const Complex &c2){
    return Complex(c1._real+c2._real,c1._image+c2._image);

}
void test(){
    Complex c1(1,2);
    Complex c2(2,1);
    Complex c3=c1+c2;
    c3.print();

}

int main()
{
 test();
 return 0;
}

```

**运算符重载的本质是定义一个运算符重载函数，定义步骤如下：**

1.先确定这个函数的返回值类型

2.再写函数名。

3.确定函数的形参是什么，返回值是否可以加引用（连续赋值和修改原对象时需要加），是否可以加const（当参数在函数内部不被修改时）

4.根据业务需求，补充函数体。

##### +=运算符重载

```C++
//重载+=运算符
Complex & operator+=(Complex &c1,const Complex &c2){
    c1._real=c1._real+c2._real;
    c1._image=c1._image+c2._image;
    return c1;
}
```

##### ++运算符重载

```C++
//重载++访问运算符
//前置++
Complex &operator++(){
    ++_real;
    ++_image;
    return *this;
}
//后置++，先返回再++
Complex operator++(int){
    Complex temp(*this);//利用拷贝构造函数进行拷贝
    ++_real;
    ++_image;
    return temp;
}
```

1.应该使用成员函数形式。

2.返回值类型

3.函数名称 operator ++

前置++的效率更高。

##### 下标访问运算符的重载

假设重载自定义string类中的[ ]运算符

```C++
char & operator[](size_t index){//如果不加& ，那么将无法修改左操作数，即s[0]='H'会报错
    if(index>=size()||index<0){
        char nullchar='\0';
        return nullchar;
    }
    return _pstr[index];
}
```

##### <font color='red'>输出流运算符重载</font>

只能使用友元函数来进行重载。

无论给那个类对象进行重载，输出流或输入流的返回值类型都是相同的。

```C++
//如果写成成员函数，只能这样调用
s<<cout;
//s.operator<<(cout);
```

```C++
//重载自定义string类的输出运算符
ostream & operator<<(ostream os,mystring &s){
    os<<s._pstr;
    return os;
}
```

##### <font color='red'>**输入流运算符重载**</font>

```C++
//重载complex类的输入运算符
void readInt(istream &is,int &number){
    while(1){
        is>>number;
        if(is.good()){
            break;
        }else if(is.fail()){
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"请重新输入，你的输入不是一个数字"<<endl;
        }else if(is.bad()||is.eof()){
            cout<<"当前程序已结束"<<endl;
        }
    }
}
istream &operator>>(istream &is,Complex &c){
    readInt(is,c._real);
    readInt(is,c._image);
    return is;
}
```



##### <font color='red'>成员访问运算符</font>

成员访问运算符包括.和->，其中.不能重载，-->可以重载。

箭头运算符只能以成员函数的形式重载，其返回值必须是一个指针或者重载了箭头运算符的对象。

**两层结构的使用**

```C++
//两层结构
class Data{
public:
    Data()
    {
        cout<<"Data()"<<endl;
    }
    
    ~Data(){
        cout<<"~Data()"<<endl;
    }
    int getData(){
        return _data;
    }
private:
    int _data=20;
};
class MiddleLayer{
public:
    MiddleLayer(Data *data)
    :_pdata(data)
    {
        cout<<"MiddleLayer()"<<endl;
    }
    ~MiddleLayer(){
         cout<<"~MiddleLayer()"<<endl;
        if(_pdata){
            delete _pdata;
            _pdata=nullptr;
        }
    }
private:
    Data *_pdata;
};
```

```C++
void test(){
    MiddleLayer ml(new Data());//为什么只有new 没有delete 没有内存泄漏
}
```

![image-20250715194441406](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250715194441406.png)

因为此时**借助于一个栈对象的生命周期来管理当前指针的回收**。

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250715194405123.png" alt="image-20250715194405123" style="zoom:67%;" />

```C++
void test2(){
    Data * p = new Data();
    cout<<p->getData()<<endl;
    cout<<(*p).getData()<<endl;
    //delete p;
    //p = nullptr; 
}
```

![image-20250715195101786](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250715195101786.png)

如果此时不手动释放p,不会调用Data的析构函数，因为这是Data *原生指针，必须程序员手动释放管理内存空间，否则会造成内存泄漏。

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250715195659284.png" alt="image-20250715195659284" style="zoom:50%;" />

**思考：**希望实现一个这样的效果，创建MiddleLayer对象ml，让ml对象可以使用箭头运算符去调用Data类的成员函数getData

```C++
//由于getData需要用Data类型来调用，故重载函数的返回值为Data *
Data * operator->(){
    return _pdata;
}
Data & operator*(){
    return *_pdata;
}
void test3(){
    MiddleLayer ml(new Data());
    cout<<ml->getData()<<endl;//直接调用会出错，此时需要重载->运算符
    cout<<(*ml).getData()<<endl;//直接调用会出错，此时需要重载.运算符
}
```

**三层结构**

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Data{
public:
    Data()
    {
        cout<<"Data()"<<endl;
    }
    
    ~Data(){
        cout<<"~Data()"<<endl;
    }
    int getData(){
        return _data;
    }
private:
    int _data=20;
};
class MiddleLayer{
public:
    MiddleLayer(Data *data)
    :_pdata(data)
    {
        cout<<"MiddleLayer()"<<endl;
    }
    ~MiddleLayer(){
        cout<<"~MiddleLayer()"<<endl;
        if(_pdata){
            delete _pdata;
            _pdata=nullptr;
        }
    }
    Data * operator->(){
        return _pdata;
    }
    Data &operator*(){
        return *_pdata;
    }
private:
    Data *_pdata;
};
class thirdLayer{
public:
    thirdLayer(MiddleLayer *pml)
    :_pml(pml)
    {
       cout<<"thirdLayer()"<<endl;
    }
    ~thirdLayer(){
        cout<<"~thirdLayer()"<<endl;
        if(_pml){
            delete _pml;
            _pml=nullptr;
        }
    }
    MiddleLayer &operator->(){
        return *_pml;
    }
    MiddleLayer &operator*(){
        return *_pml;
    }
private:
    MiddleLayer *_pml;
};
void test(){
     thirdLayer tl(new MiddleLayer(new Data()));
     cout<<tl->getData()<<endl;
     cout<<(*(*tl)).getData()<<endl;
}
int main()
{
 test();
 return 0;
}

```

```C++
//这是一种错误的写法，ml是一个栈对象，它的生命周期由作用域管理。
//删除一个栈对象，会产生未定义行为。
MiddleLayer ml(new Data());
thirdLayer(&ml);
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250715205852808.png" alt="image-20250715205852808" style="zoom:67%;" />

创建ThirdLayer对象时注意避免这样的错误,**禁止将一个栈对象的地址传递给tl**。

**<font color='red'>应该让ThirdLayer对象管理一个堆上的MiddleLayer对象</font>**

```C++
thirdLayer tl(new MiddleLayer(new Data()));
```

无论是两层结构还是三层结构，其实都是对于Data *指针的封装。

**思考：**希望实现一个这样的效果，创建thirdLayer对象tl，让tl对象可以使用箭头运算符去调用Data类的成员函数getData()

```C++
MiddleLayer &operator->(){//thirdLayer->返回的是MiddleLayer对象
    return *pml;
}
MiddleLayer &operator.(){//thirdLayer->返回的是MiddleLayer对象
    return *pml;
}
void test(){
    thirdLayer tl(new MiddleLayer(new Data()));
    cout<<tl->getData()<<endl;//直接调用会报错，此时需重载thirdLayer类的->运算符
    //第一个operator->()是ThirdLayer的成员函数，返回的是MiddleLayer对象
	//第二个operator->()是MiddleLayer的成员函数，返回的是Data*指针
    cout << tl.operator->().operator->()->getData() << endl;
}
void test(){
    thirdLayer tl(new MiddleLayer(new Data()));
    cout<<(*(*tl)).getData()<<endl;//直接调用会报错，此时需要重载thirdLayer类的.运算符
    //等价于
    cout<<tl.operator.().operator.().getData()<<endl;
    //第一个operator.()是ThirdLayer的成员函数，返回MiddleLayer对象
    //第二个operator.()是MiddleLayer的成员函数，返回的是Data *指针。
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250715211418772.png" alt="image-20250715211418772" style="zoom:50%;" />

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250715212009145.png" alt="image-20250715212009145" style="zoom:50%;" />

箭头访问运算符和解引用运算符相当于透明层一样。

如果某个类对象的箭头访问运算符返回的结果是一个对象，那么会自动调用该对象的箭头访问运算符，形成递归的效果，直到最终得到一个指针为止。

解引用运算符没有上面的特性。

#### 可调用实体

##### **函数调用运算符重载**（了解即可）

本质上来说也是一个成员函数

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class FunctionObject{
public:
    void operator()(){
        cout << "FunctionObject operator()()" << endl;
        ++ _count;
    }

    int operator()(int x, int y){
        cout <<"operator()(int,int)" << endl;
        ++ _count;
        return x + y;
    }
    
    int _count = 0;//携带状态
};

void test(){
    FunctionObject fo;
    fo();
    fo.operator()();
    cout << fo(5,6) << endl;
    cout << fo.operator()(5,6) << endl;//本质

    cout << "fo._count:" << fo._count << endl;//记录这个函数对象被调用的次数
}

int main()
{
 test();
 return 0;
}

```

通过函数调用运算符重载可以使得对象像一个函数一样调用。

在定义 "()" 运算符的语句中，第一对小括号总是空的，因为它代表着我们定义的运算符名称，第二对小括号就是函数参数列表了，它与普通函数的参数列表完全相同。对于其他能够重载的运算符而言，操作数个数都是固定的，<font color=red>**但函数调用运算符不同，它的参数是根据需要来确定的， 并不固定**</font>。

<span style=color:red;background:yellow>**重载了函数调用运算符的类的对象称为函数对象**</span>，由于参数列表可以随意扩展 ，所以可以有很多重载形式（对应了普通函数的多种重载形式）

**函数对象相比普通函数的优点：**

函数对象可以携带状态（函数对象可以封装自己的数据成员、成员函数，具有更好的面向对象的特性）

如上，可以记录函数对象被调用的次数，而普通函数只能通过全局变量做到（全局变量不够安全）。

**函数对象与成员函数的区别：**

函数对象主要用于实现一个"可调用对象",整个类的目的就是为了执行这一个操作

成员函数是类功能的一部分,用于实现类的各种行为

##### **函数指针**

###### 成员函数指针（了解）

```C++
class FFF
{
public:
    void print(int x){
        cout << "FFF::print:" << x << endl;
    }

    void display(int x){
        cout << "FFF::display:" << x << endl;
    }
};
```

定义一个函数指针要明确指针指向的函数的返回类型、参数类型，那么<span style=color:red;background:yellow>**定义一个成员函数指针还需要确定的是这个成员函数是哪个类的成员函数（类的作用域）**</span>

与普通函数指针不一样的是，<font color=red>**成员函数指针的定义和使用都需要使用完整写法**</font>，不能使用省略写法，定义时要完整写出指针声明，使用时要完整写出解引用（解出成员函数后接受参数进行调用）。

另外，成员函数需要通过对象来调用，<font color=red>**成员函数指针也需要通过对象来调用**</font>。

```` c++
void (FFF::*p)(int) = &FFF::print;
FFF ff;
(ff.*p)(4);
````

> 类比来写，也可以使用typedef来定义这种成员函数指针类,使用这个成员函数指针类的”对象“调用FFF类的成员函数print
>
> <font color=red>**这里有一个要求 —— 成员函数指针指向的成员函数需要是FFF类的公有函数**</font>
>
> ``` c++
> //定义成员函数类型MemberFunction
> //创建成员函数指针需要确定：哪个类的成员函数、返回类型、参数信息，必须使用完整形式写法
> typedef void (FFF::*MemberFunction)(int);
> 
> void test(){
>  //定义成员函数指针
>  MemberFunction mf = &FFF::print;
>  FFF fff;
>  //通过对象调用成员函数指针
>  (fff.*mf)(15);
>  mf = &FFF::display;
>  (fff.*mf)(16);
> }
> ```
>
> 此时就出现了一个新的运算符 **".*"** —— <span style=color:red;background:yellow>**成员指针运算符的第一种形式。**</span>



> FFF类对象还可以是一个堆上的对象
>
> ``` c++
> void test2(){
>  MemberFunction mf = &FFF::print;
>  FFF * fff = new FFF();
>  //通过指针调用成员函数指针
>  (fff->*mf)(16);
>  delete fff;
> }
> ```
>
> 又引出了新的运算符 **"->*"** —— <span style=color:red;background:yellow>**成员指针运算符的第二种形式。**</span>

**成员函数指针的意义：**

1. 回调函数：<font color=red>**将成员函数指针作为参数传递给其他函数**</font>，使其他函数能够在特定条件下调用该成员函数；
2. 事件处理：将成员函数指针存储事件处理程序中，以便在特定事件发生时调用相应的成员函数；
3. 多态性：通过将成员函数指针存储在基类指针中，可以实现多态性，在运行时能够去调用相应的成员函数。

###### <font color='red'>空指针的使用</font>（五星）

```C++
void test(){
void (FFF::*p)(int) = &FFF::print;
FFF *ff=new FFF();
(ff->*p)(4);
ff = nullptr;
(ff->*p)(16);
}
```

![image-20250716162728076](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250716162728076.png)

**思考：**为什么此时ff已经为空指针了，但是不会报错而且正常输出了数据？

事实上，空指针去调用成员函数也好、成员函数指针也好，只要不涉及到访问该类数据成员，都是可以的。

#### 类型转换函数（三星）

**1.由其他类型向自定义类型转换**

```C++
//例如
Point p=1; //等价于Point p=Point(1)
string s="hello world";
```

默认可以借助于构造函数来实现，但是有一个要求，构造函数中不可以有explicit关键字。

```C++
  Point(int x)
    :_x(x)
    ,_y(0)
    {
        cout<<"Point()"<<endl;
    }
```

**2.由自定义类型向其它类型进行转换**

###### 2.1 自定义类型向内置数据类型转换

**类型转换函数的形式：**

​                                      <font color='red'>**operator 目标类型（）{ }**</font>

**类型转换函数的特征：**

1.必须是成员函数

2.没有返回值

3.没有参数

4.在函数执行体中必须要返回目标类型的变量

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Mycin{
public:
    Mycin(int good,int bad,int eof,int fail)
    :_good(good)
    ,_bad(bad)
    ,_eof(eof)
    ,_fail(fail)
    {
    }
    operator bool(){
        return _fail!=1;
    }
private:
    int _good;
    int _bad;
    int _eof;
    int _fail;
};
void test(){
     Mycin cin(0, 0, 0, 0);
     //会调用类型转换函数，转换成bool类型
     if(cin){
       cout << "cin is good" << endl;
     }else{
        cout << "cin is bad" << endl;
    }
}
int main()
{
 test();
 return 0;
}
```

###### **2.2 自定义类型向自定义类型转换**

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class CNY;
class USD{
public:
    USD(double money)
    :_money(money)
    {
    }
    operator CNY();
    void print(){
        cout<<_money<<"$"<<endl;
    }
private:
    double _money;
};
class CNY{
public:
    CNY(double money)
    :_money(money)
    {
    }
    operator USD();
    void print(){
        cout<<_money<<"￥"<<endl;
    }
private:
    double _money;
};
USD::operator CNY(){
    return CNY(_money*7.2);
}
CNY::operator USD(){
    return USD(_money/7.2);
}
void test(){
    CNY c(100);
    c.print();
    USD u=c;
    u.print();
    CNY c2=u;
    c2.print();
}

int main()
{
 test();
 return 0;
}

```

![image-20250716174007668](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250716174007668.png)

还可通过特殊形式的拷贝构造函数和赋值运算符函数来实现上述功能

```C++
class USD{
public:
    USD(double value)
    :_value(value)
    {}

    //CNY需要访问USD的私有数据成员，所以需要设置为友元
    operator CNY();

    friend class CNY;

    void print(){
        cout << "print:" << _value << endl;
    }

private:
    double _value;
};

class CNY{
public:
    CNY(double value)
    :_value(value)
    {}

    //类型转换函数
    operator USD();

    //特殊形式的构造函数
    CNY(const USD & rhs)
    :_value(rhs._value * 7.2)
    {
        cout << "CNY(const USD &)" << endl;
    }

    //赋值运算符函数
    CNY & operator=(const USD & rhs){
        _value = rhs._value * 7.2;
        cout << "operator=(const USD &)" << endl;
        return *this;
    }
    
    void print(){
        cout << "print:" << _value << endl;
    }
    
private:
    double _value;
};

USD::operator CNY(){
    return CNY(_value * 7.2);
}

CNY::operator USD(){
    return USD(_value / 7.2);
}

void test(){
    USD usd(100);
    CNY cny(100);
    cny.print();
    cny = usd;
    cny.print();
}
```

![image-20250716174526512](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250716174526512.png)

当类型转换函数，特殊形式的拷贝构造函数，赋值运算符函数同时存在时，会优先调用赋值运算符函数。

赋值运算符>拷贝构造>类型转换

#### 嵌套类（五星）

外部类：：内部类（类名作用域）

```C++
Class Line{
  public:
    Line(int x1,int y1,int x2,int y2)
    :p1(x1,y1)
    ,p2(x2,y2)
    {
        
    }
    class Point{
      public:
        Point(int x,int y)
        :_x(x)
        ,_y(y)
        {
            
        }
      private:
        int _x;
        int _y;
    };
  private:
    Point p1;
    Point p2;
};
```

Point类是定义在Line类中的内部类，无法直接创建Point对象，需要在Line类名作用域中才能创建。

```C++
Point p(1,2)//error
Line::Point p(1,2);//OK
```

**思考：**如果想要使用输出流运算符输出Line对象，应该怎么实现？

```C++
ostream &operator<<(ostream &os,const Line &rhs){
    os<<rhs.p1<<"-------------------->"<<rhs.p2;
    return os;
}
```

此时输出运算符需要处理一个Point对象，因此还需要为Point类写一个输出运算符重载函数,由于需要访问Line类中的私有数据成员，因此需要将该函数设置为Line的友元函数。下面同理

```C++
ostream &operator<<(ostream &os,const Line::Point &rhs){
    os<<"("<<rhs._x<<","<<rhs._y<<")";
    return os;
}
```

```C++
#include <iostream>
using std::cout;
using std::endl;
//讨论：外部类和内部类之间访问权限上面的关系
class Outer{
public:
    class Inner{
    public:
        void inner_func(Outer outer){
            //内部类可以直接访问外部类的静态数据成员
            cout << _out_a << endl;
            //内部类可以通过类名作用域限定符的方式访问外部类的静态
            //数据成员
            cout << Outer::_out_a << endl;
            //内部类可以通过对象访问私有数据成员
            cout << outer._out_b << endl;
        }
        friend class Outer;

    private:
        int _a=20;
        static int _b;
    };
public:
    void outer_func(Inner inner){
       //cout << _b << endl;//error
        cout << Inner::_b << endl;
        cout << inner._a << endl;
    }
private:
    static int _out_a;
    int _out_b;
    //外部类中可以创建出内部类对象
    Inner inner;
};
int Outer::_out_a = 0;

void test(){
    //外部应用程序无创建
    //Inner inner;//error
    Outer::Inner inner2;
}

int main()
{
    test();
    return 0;
}
```

**内部类与外部类的访问权限**

内部类可以**直接访问**外部类的**静态数据成员**

内部类可以通过**类名作用域限定符**的方式访问外部类的**静态数据成员**。

内部类可以通过**对象**访问**外部类的私有数据成员。**

**内部类访问外部类有便利性，相当于内部类已经设置为了外部类的友元。**

外部类不可以直接访问内部类的私有的静态数据成员。

外部类也不可以通过类名作用域限定的方式去访问内部类的私有数据成员。

通过对象去访问内部类的私有数据成员也是不可以的。

**外部类如果希望访问内部类的私有数据成员，依然需要设置为友元才可以 设置为友元后依然还需要用类名作用域限定或对象去访问。**

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250717222220578.png" alt="image-20250717222220578" style="zoom:50%;" />

如果内部类是位于外部类的私有区域定义的，那么在外部类中可以创建出内部类的对象，而在外部应用程序中不可以，这是唯一的一个优势。

------



#### <font color='red'>**单例对象的自动释放**（五星）</font>

##### **1.使用另外一个栈对象的生命周期来管理资源。**

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Singleton{
public:
    static Singleton *getinstance(){
        if(instance==nullptr){
            instance=new Singleton();
        }
        cout<<instance<<endl;
        return instance;
    }
    void print(){
        cout<<"hello c++"<<endl;
    }
    friend class Autorelease;
private:
    //构造函数私有化，析构函数私有化
    Singleton(){}
    ~Singleton(){}
    //删除拷贝构造函数，赋值运算符函数
    Singleton(const Singleton &rhs)=delete;
    Singleton &operator=(const Singleton &rhs)=delete;
    //在静态区创建一个指针，指向对象。
    static Singleton *instance;
};
Singleton * Singleton::instance=nullptr;
class Autorelease{
public:
    ~Autorelease(){
        if(Singleton::instance){
            delete Singleton::instance;
            Singleton::instance=nullptr;
        }
    }
};
void test(){
    Autorelease a;
    Singleton *p=Singleton::getinstance();
    p->print();
    Singleton *q=Singleton::getinstance();
    q->print();
}

int main()
{
 test();
 return 0;
}

```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250719170530246.png" alt="image-20250719170530246" style="zoom:50%;" />

```C++
 Autorelease a;
 Autorelease a1;//double free
 Singleton *p=Singleton::getinstance();
 Singleton *q=Singleton::getinstance();
```

```C++
class Autorelease{
public:
    Autorelease(Singleton *s)
    :_s(s)
    {}
    ~Autorelease(){
        if(_s){
            delete _s;
            _s=nullptr;
        }
    }
private:
    Singleton *_s;
};
void test(){
    Autorelease a(Singleton::getinstance());
}
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250719170908084.png" alt="image-20250719170908084" style="zoom:50%;" />

缺点：如果将单例返回的指针变量同时交给两个栈对象进行托管，那么依然会有**double free**的问题。如果主动调用栈对象的析构函数也会出现同样的问题。

##### **2.嵌套类+静态对象**

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Singleton{
public:
    static Singleton *getinstacne(){
        if(instance==nullptr){
            cout<<"getinstacne()"<<endl;
            instance=new Singleton();
        }
        cout<<instance<<endl;
        return instance;
    }
    class Autorelease{
    public:
        Autorelease(){
            cout<<"Autorelease()"<<endl;
        }
        ~Autorelease(){
            cout<<"~Autorelease()"<<endl;
            if(instance){
                delete instance;
                instance=nullptr;
            }
        }
    };
    void print(){
        cout<<"helloworld"<<endl;
    }
private:
    Singleton(){cout<<"Singleton()"<<endl;}
    ~Singleton(){cout<<"~Singleton()"<<endl;}
    Singleton(const Singleton &rhs)=delete;
    Singleton &operator=(const Singleton &rhs)=delete;
    static Singleton *instance;
    static Autorelease ar;
};
Singleton *Singleton::instance=nullptr;
Singleton::Autorelease Singleton::ar;
void test(){
    Singleton *p=Singleton::getinstacne();
    p->print();
}

int main()
{
 test();
 return 0;
}

```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250719194831651.png" alt="image-20250719194831651" style="zoom:50%;" />

**执行过程：**

1. 程序启动时，静态区的 `instance` 被初始化为 `nullptr`，随后 `ar` 对象被构造
2. 首次调用 `getInstance()` 时，在堆上创建 `Singleton` 实例并将其地址赋给 `instance`
3. 程序结束时，ar对象会调用Autorelease的析构函数，在析构函数中执行delete instance,又会调用Singleton的析构函数，释放 `instance` 指向的堆内存。
4. 静态区的内存空间被系统回收

此时只需正常使用单例即可，不需要去考虑delete操作。

##### **3.atexit+destory函数**

利用atexit函数来注册程序正常终止时要被调用的函数。

```c++
int atexit(void (*function)(void));
```

- **参数**：指向无参数、无返回值的函数指针，它接受一个 **静态函数指针**（或全局函数）作为参数
- **返回值**：0 表示成功，非 0 表示失败
- **特性**：可注册多个回调，按 后进先出（LIFO 顺序执行

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Singleton{
public:
    static Singleton *getinstacne(){
        if(instance==nullptr){
            cout<<"getinstacne()"<<endl;
            atexit(destory);
            instance=new Singleton();
        }
        cout<<instance<<endl;
        return instance;
    }
    void print(){
        cout<<"helloworld"<<endl;
    }
private:
    Singleton(){cout<<"Singleton()"<<endl;}
    ~Singleton(){cout<<"~Singleton()"<<endl;}
    Singleton(const Singleton &rhs)=delete;
    Singleton &operator=(const Singleton &rhs)=delete;
    static void destory(){
        cout<<"destory()"<<endl;
        if(instance){
            delete instance;
            instance=nullptr;
        }
    }
    static Singleton *instance;
};
Singleton *Singleton::instance=nullptr;
void test(){
    Singleton *p=Singleton::getinstacne();
    p->print();
}
int main()
{
 test();
 return 0;
}

```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250719201248269.png" alt="image-20250719201248269" style="zoom:50%;" />

以上三种方案，其实在单线程的情况下都没有问题，但是如果目前处于多线程的情况下都是有问题的。

------

多线程的代码风格

**1.懒汉模式lazy**

上述的单例对象就是属于懒汉模式，真正需要使用的时候才会去创建该单例对象。有线程安全问题。

**2.饿汉模式eager**

会立刻创建出一个对象，叫做饿汉模式。基本没有线程安全问题。

会提前创建出来对象，可能大多数时候并不需要该对象，提前创建，比较浪费空间。

```C++
//对于_pInstance的初始化有两种方式

//饱汉式（懒汉式）—— 懒加载，不使用到该对象，就不会创建
Singleton* Singleton::_pInstance = nullptr; 

//饿汉式 —— 最开始就创建（即使不使用这个单例对象）
Singleton* Singleton::_pInstance = getInstance();
```



##### **4.pthread_once机制**

可以保证在多线程的情况下只有一个线程执行。

```C++
int pthread_once(pthread_once_t *once_control, void (*init_routine) (void));
```

**参数：**

`once_control`：是一个类型为 `pthread_once_t` 的变量，用于控制初始化函数是否被执行，这个变量需要初始化为 `PTHREAD_ONCE_INIT`。

`init_routine`：是一个指向无参数、无返回值函数的指针，该函数是在多线程环境下只需要执行一次的初始化代码。

```C++
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class Singleton{
public:
    static Singleton *getinstacne(){
        if(instance==nullptr){
            cout<<"getinstacne()"<<endl;
            pthread_once(&once,Init);
        }
        cout<<instance<<endl;
        return instance;
    }
    void print(){
        cout<<"helloworld"<<endl;
    }
private:
    Singleton(){cout<<"Singleton()"<<endl;}
    ~Singleton(){cout<<"~Singleton()"<<endl;}
    Singleton(const Singleton &rhs)=delete;
    Singleton &operator=(const Singleton &rhs)=delete;
    static void Init(){
        instance=new Singleton();
        atexit(destory);
    }
    static void destory(){
        cout<<"destory()"<<endl;
        if(instance){
            delete instance;
            instance=nullptr;
        }
    }
    static Singleton *instance;
    static pthread_once_t once;
};
Singleton *Singleton::instance=nullptr;
pthread_once_t Singleton::once=PTHREAD_ONCE_INIT;
void test(){
    Singleton *p=Singleton::getinstacne();
    p->print();
}

int main()
{
 test();
 return 0;
}
```

<font color=red>**注意：**</font>

(1)如果手动调用init创建对象，没有通过getInstance创建对象，实际上绕开了pthread_once的控制，必然造成内存泄漏问题 —— <span style=color:red;background:yellow>**需要将init私有**</span>

(2)如果手动调用了destroy函数，之后再使用getInstance来尝试创建对象，因为pthread_once的控制效果，不会再执行init函数，所以无法再创建出单例对象。所以不允许手动调用destroy函数。同时因为会使用atexit注册destroy函数实现资源回收，所以也不能将destroy删掉，应该<span style=color:red;background:yellow>**将destroy私有**</span>，避免在类外手动调用。

------



#### <font color='red'>string原理</font>

##### 发展历史

##### **1.深拷贝阶段**

深拷贝是指在复制对象时，不仅复制对象本身，还复制其指向的动态分配资源（如堆内存）。对于`std::string`，深拷贝会创建一个新的字符串对象，并复制原字符串的所有字符到新的内存区域。

**特点**：

- **内存独立性**：原字符串和复制后的字符串使用不同的内存空间，修改其中一个不会影响另一个。

- **性能开销**：需要分配新内存并复制数据，时间复杂度为 O (n)。

```C++
int main() {
    std::string original = "Hello";
    std::string copy = original; // 深拷贝：复制数据到新内存
    copy[0] = 'J'; // 修改copy不影响original
    // original: "Hello", copy: "Jello"
    return 0;
}
```

##### **2.写时复制阶段Cow**

大多数情况下，执行的是浅拷贝，只有当前真正需要修改数据时才会使用深拷贝。

当复制`std::string`时，**仅复制指针**，原字符串和复制后的字符串共享同一块内存。直到其中一个字符串被修改时，才会真正分配新内存并复制数据。

**特点**：

- **共享内存**：复制操作仅复制指针，时间复杂度为 O (1)。
- **延迟复制**：首次修改时触发深拷贝，确保数据独立性。
- **线程安全问题**：需要额外的引用计数锁，可能影响多线程性能。

**思考：**默认执行浅拷贝，也就是多个string对象指向同一个堆空间，那么何时进行堆空间的回收。

最后一个对象被销毁的时候。可以使用引用计数来记录当前string的引用次数。当引用计数为0时，回收堆空间。

<font color='red'>**思考：**</font><font color='red'>**引用计数放在什么位置？**</font>

**1.如果将引用计数设置为普通数据成员即栈区。**

```C++
class String{

public:
    String(const char * pstr);
    //拷贝构造函数:浅拷贝、引用计数加+1
    String(const String & rhs)
    :_pstr(rhs._pstr)
    ,_refcount(rhs._refcount)
    {
        _refcount++;
        //两个字符串的引用计数应该是一样的
        /* rhs._refcount++; error,因为const修饰 */
    }
private:
    char * _pstr;
    int _refcount;
};
void test(){
    string s1="hello";
    string s2=s1;
}
```

由于此时拷贝构造函数中string 被const修饰无法改变数据成员。导致s1和s2的引用计数不一致。因此无法将引用计数放置在栈区。

**2.将引用计数放置在静态区**

静态区的变量在程序生命周期内唯一存在，所有对象共享同一实例。若引用计数存储在静态区，**所有对象将共用同一个计数器**，导致计数混乱。

```C++
string s1="hello";
string s2=s1;
string s3="world";
```

此时s1和s2的引用计数应该都为2，s3的引用计数为1。如果放置在静态区的话，那么引用计数就是3，与实际不符。

**3.将引用计数放置在堆区**

可行，当放置在堆区是相同的字符串，其指针指向存放引用计数的堆空间，不同的字符串之间的引用计数互不干扰。达到预期目标。

可进一步优化，将引用计数和字符串的内存存放在一起。合并存储只需一次`new`和`delete`操作，减少内存分配器的调用次数，降低系统开销。

由于不知道字符串内容的长度，因此将引用计数存放在字符串内容的前面可以方便访问。

<font color='red'>**写时复制的实现**</font>

```C++
#include <string.h>
#include <iostream>
#include <ostream>
using namespace std;
class CowString{
public:
    CowString()
    :_pstr(new char[1+4]()+4)
    {
     cout<<"CowString()"<<endl;
     *(int *)(_pstr-4)=1;
    }

    CowString(const char *str)
    :_pstr(new char[strlen(str)+1+4]()+4)
    {
        strcpy(_pstr,str);
        cout<<"Co_pstring(const char *str)"<<endl;
        *(int *)(_pstr-4)=1;
    }

    //s3(s1)
    CowString(const CowString &rhs)
    :_pstr(rhs._pstr)
    {
        cout<<"CowString(const CowString &rhs)"<<endl;
        ++*(int *)(_pstr-4);
    }

    //s3=s1;
    //左操作数-1，如果=0，则释放堆空间
    //右操作数+1
    //深拷贝
    //返回this指针
    CowString &operator=(const CowString &rhs){
        cout<<"CowString &operator=()"<<endl;
        if(this!=&rhs){
            if(--*(int *)(_pstr-4)==0){
                delete [] (_pstr-4);
            }
            _pstr=rhs._pstr;
            ++*(int *)(rhs._pstr-4);
        }
        return *this;
    }

    ~CowString(){
        cout<<"~CowString()"<<endl;
        if(*(int *)(_pstr-4)==0){
            delete [] (_pstr-4);
        }
    }

    int size() const{
      return strlen(_pstr);
    }

    const char * c_str() const{
        return _pstr;
    }

    int refcount() const{
        return *(int *)(_pstr-4);
    }
    //如果此时引用计数为1，可以直接返回
    //如果此时>1，先创建一个临时指针，申请堆空间 引用计数为1，原计数-1
    //如果index大于string的长度则直接返回nullptr
    //
    char &operator[](const int index){
        if(index>=size()){
             static char nullchar='\0';
            return nullchar;
        }
        if(*(int *)(_pstr-4)>1){
            cout<<"char operater[]"<<endl;
            char *temp=new char[strlen(_pstr)+1+4]()+4;
            strcpy(temp,_pstr);
            --*(int *)(_pstr-4);
            _pstr=temp;
            *(int *)(_pstr-4)=1;
        }
        return _pstr[index];
    }
    friend ostream &operator<<(ostream &os,const CowString &rhs);
private:
    char *_pstr;
};
ostream &operator<<(ostream &os,const CowString &rhs){

    os<<rhs._pstr;
    return os;
}

```

但是此时[ ]访问运算符还存在一定的问题

```c++
Cowstring s1="hello";
Cowstring s2=s1;
Cowstring s3="world";
cout<<s1.refcount()<<endl;//2
cout<<s3.refcount()<<endl;//1
cout<<s1[0]<<endl;
cout<<s1.refcount()<<endl;//1
```

当执行下标运算符时，会出现问题，因为此时分不清是读操作还是写操作，只要执行了[ ]运算符，都会分配一个新空间来存储当前的内容。

如何解决上面的问题？

创建一个CowString类的内部类，让CowString的operator[]函数返回是这个新类型的对象，然后在这个新类型中对<<和=进行重载，当只是读操作时直接输出即可，当是写操作时调用这个新类型的赋值运算符函数，进行修改。

```C++
#include <string.h>
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;
using std::cin;
class CowString{
public:
    CowString()
    :_pstr(new char[1+4]()+4)
    {
        cout<<"CowString()"<<endl;
        *(int *)(_pstr-4)=1;
    }

    CowString(const char *str)
    :_pstr(new char[strlen(_pstr)+1+4]()+4)
    {
        cout<<"CowString(char *str)"<<endl;
        strcpy(_pstr,str);
        *(int *)(_pstr-4)=1;
    }

    //CowString c1=c2;
    CowString(const CowString &rhs)
    :_pstr(rhs._pstr)
    {
        _pstr=rhs._pstr;
        ++*(int *)(_pstr-4);
        cout<<"CowString(cosnt CowString)"<<endl;
    }

    //c1=c2;
    //自赋值判断
    //左操作数-1 ，如果计数=0，清空左操作数的堆空间
    //改变指向
    //右操作数+1
    //返回this指针
    CowString &operator=(const CowString &rhs)
    {
        cout<<"CowString &operator=(const)"<<endl;
        if(this!=&rhs){
            if(--*(int *)(_pstr-4)==0){
                delete [] _pstr;
            }
            _pstr=rhs._pstr;
            ++*(int *)(_pstr-4);
        }
        return *this;
    }

    int size() const{
        return strlen(_pstr);
    }
    char * c_str() const{
        return _pstr;
    }
    int refcount() const{
        return *(int *)(_pstr-4);
    }
    ~CowString(){
        if(--*(int *)(_pstr-4)==0){
            delete [] (_pstr-4);
        }
    }
    class CharPoxy{
    public:
        CharPoxy(CowString &s,const int index)
        :_s(s)
        ,_index(index)
        {
            cout<<"CharPoxy(const CowString)"<<endl;
        }
        //s3[0]='H'
        char &operator=(const char &rhs){
            cout<<"operator=(char)"<<endl;
            if(_s.refcount()>1){
                char *temp=new char[_s.size()+1+4]()+4;
                strcpy(temp,_s._pstr);
                --*(int *)(_s._pstr-4);
                _s._pstr=temp;
                *(int *)(_s._pstr-4)=1;
            }
            _s._pstr[_index]=rhs;
            return _s._pstr[_index];

        }
        //如果只读的话直接输出
       friend ostream &operator<<(ostream &os,const CharPoxy &c);

    private:
        CowString &_s;
        int _index;
    };

    CharPoxy operator[](size_t index){
        static CowString s;
        if(index>=size()){
            return CharPoxy(s,0);
        }
        return CharPoxy(*this,index);
    }
   friend ostream &operator<<(ostream &os,CowString &s);
   friend ostream &operator<<(ostream &os,const CharPoxy &c);

private:
    char *_pstr;
};
ostream &operator<<(ostream &os,CowString &s){
    os<<s._pstr;
    return os;
}
ostream &operator<<(ostream &os,const CowString::CharPoxy &c){
    cout<<"operator(CharPoxy)";
    os<<c._s._pstr[c._index];
    return os;
}
void test(){
    CowString s1="hello";
    CowString s2=s1;
    cout<<s1.refcount()<<endl;//2
    cout<<s1[0]<<endl;
    cout<<s1.refcount()<<endl;//2
    s1[0]='H';
    cout<<s1.refcount()<<endl;//1
    cout<<s2.refcount()<<endl;//1
    cout<<s1<<endl;
}
int main()
{
 test();
 return 0;
}

```

##### **3.短字符串优化SSO阶段**

当字符串的字符数小于等于15时，  buffer直接存放整个字符串(**直接存放在栈区**)；

当字符串的字符数大于15时，  buffer 存放的就是一个指针，指向堆空间的区域。

这样做的好处是，当字符串较小时，直接拷贝字符串，放在 string内部，不用获取堆空间，开销小。

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250719213732930.png" alt="image-20250719213732930" style="zoom:50%;" />

```C++
#include <iostream>
#include <string.h>
using namespace std;
class String {
public:
    String(const char * pstr)
    :_size(strlen(pstr))
    {
        if(strlen(pstr)<=15){
            cout<<"String() size<=15"<<endl;
            strcpy(_buffer._local,pstr);
        }else{
            cout<<"String() size>15"<<endl;
            _buffer._pointer=new char[_size+1];
            strcpy(_buffer._pointer,pstr);
        }
    }
    ~String(){
        if(_size>15){
                cout<<"~String() size>15"<<endl;
                delete [] _buffer._pointer;
        }
    }
    String(const String &rhs)
    :_size(rhs._size)
    {
        if(_size<=15){
            strcpy(_buffer._local,rhs._buffer._local);
        }else{
            _buffer._pointer=new char[rhs._size+1]();
            strcpy(_buffer._pointer,rhs._buffer._pointer);
        }
    }

    //左操作数<15,右操作数<15
    //左操作数<15,右操作数>15
    //左操作数>15,右操作数<15
    //左操作数>15,右操作数>15
    String &operator=(const String &rhs){
        if(this!=&rhs){
            if(_size<=15){
                memset(_buffer._local,0,strlen(_buffer._local));
            }else{
                delete _buffer._pointer;
            }
            if(rhs._size<=15){
                strcpy(_buffer._local,rhs._buffer._local);
            }else{
                _buffer._pointer=new char[rhs._size+1]();
                strcpy(_buffer._pointer,rhs._buffer._pointer);
            }            
        }
        _size=rhs._size;
        return *this;
    }
    char & operator[](size_t idx){
        if(idx>=_size){
            static char nullchar='\0';
            return nullchar;
        }
        if(_size>15){
            cout<<"size>15"<<endl;
            return _buffer._pointer[idx];
        }else{
            cout<<"size<=15"<<endl;
            return _buffer._local[idx];
        }
    }


    friend
    ostream & operator<<(ostream & os,const String & rhs);
private:
	union Buffer{
		char * _pointer;
		char _local[16];
	};
	
	size_t _size;
    Buffer _buffer;
};
ostream & operator<<(ostream & os,const String & rhs){
    if(rhs._size>15){
        cout<<"operator << size>15"<<endl;
        os<<rhs._buffer._pointer;
        return os;
    }else{
        cout<<"operator << size<=15"<<endl;
        os<<rhs._buffer._local;
        return os;
    }
}
void test(){
    String str1("hello");
    cout<<str1<<endl;
    String str2("hello,world!!!!!");
    cout<<str2<<endl;
}

```

