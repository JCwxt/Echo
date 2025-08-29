# C++

#### **1.c与c++的区别**

C++和C语言的头文件最明显的特征是没有后缀名,C++头文件默认为于/user/include/c++/11

c++标准库里面的所有组件，功能都位于std命名空间中。

<<表示的是一个函数，实际表示operator<<

#### **2.命名空间**

命名空间又称为名字空间，是程序员命名的内存区域，程序员根据需要指定一些有名字的空间域，把一些全局实体分别存放到各个命名空间中，从而与其他全局实体分隔开。

在声明一个命名空间时，大括号内不仅可以存放变量，还可以存放以下类型：

变量、常量、函数、结构体、引用、类、对象、模板、命名空间等，它们都称为**实体**

主要是为了解决名称的冲突问题

命名空间的使用方式：

**作用域限定符**，优点：冲突产生的概率非常小，缺点：编写麻烦，如果代码中频繁使用，非常繁琐。

每次要使用某个命名空间中的实体时，都直接加上<span style=color:red;background:yellow>**作用域限定符::**</span>

```C++
std::cout<<"hello world!"<<std::endl;
```

**using编译指令**，优点：将命名空间的所有实体引入，缺点：除了将需要的实体引入进来，还会引入其它很多未知的实体，当对命名空间中的其它实体不熟悉时，容易产生冲突。<font color='red'>**using编译指令尽量写在局部作用域。**</font>

```C++
#include <iostream>
using namespace std; //using编译指令

int main(int argc, char * argv[]){
 cout << "hello,world" << endl;
 return 0;
}
```

**using 声明机制**，只引入自己需要的实体，不容易产生冲突。在同一作用域内用using声明的不同的命名空间的实体，不能是同名的，否则会发生冲突。

```C++
#include<iostream>
using std::cout;
using std::endl;
int main(int argc, char * argv[]){
 cout << "hello,world" << endl;
 return 0;
}
```

**命名空间的相互调用**

命名空间的嵌套使用，命名空间中还可以进一步存放命名空间。

```C++
namespace wd
{
int num = 100;

void func(){
    cout << "func" << endl;
}

namespace cpp
{
int num = 200;

void func(){
    cout << "cpp::func" << endl;
}
}//end of namespace cpp

}//end of namespace wd

//方式一，使用作用域限定精确访问实体
void test0(){
    cout << wd::cpp::num << endl;
    wd::cpp::func();
}

//方式二，using编译指令一次性引入cpp的实体
void test1(){
    using namespace wd::cpp;
    cout << num << endl;
    func();
}

//方式三，using声明语句
void test2(){
    using wd::cpp::num;
    using wd::cpp::func;
    cout << num << endl;
    func();
}
```

**全局命名空间和匿名命名空间**

全局命名空间:全局命名空间是C++程序中默认的顶层命名空间,其中的名称没有域限定,直接使用名称即可访问。它的作用域范围是整个程序。在所有函数外部定义的名字自动属于全局命名空间。

匿名命名空间:匿名命名空间是一个没有名字的命名空间，它用于封装不希望暴露给外部的实体，如函数、变量和类等。定义的实体只在当前文件中可见，不会被其他文件访问到，从而避免了与其他文件中相同名称的变量或函数发生冲突。

全局命名空间访问方式：1.直接访问，2.::来访问

匿名命名空间访问方式：1.直接访问，2::来访问，匿名空间实体不能被外部程序访问，不能跨文件访问。

#### **Const**

被const修饰的变量会变为一个常量，不可以被修改。

修饰内置数据类型

```C++
const int num=10;
```

修饰指针数据类型

```C++
int number1 = 10;
int number2 = 20;

const int * p1 = &number1;//指向常量的指针
int const *p1=&number1;//指向常量的指针
*p1 = 100;//error 通过p1指针无法修改其所指内容的值
p1 = &numbers;//ok 可以改变p1指针的指向
```

**总结：const在*左边，即为指向常量的指针，不能通过指针改变其指向的值，但是可以改变这个指针的指向。**

```C++
int * const p3 = &number1;//常量指针
*p3 = 100;//ok 通过p3指针可以修改其所指内容的值
p3 = &number2;//error 不可以改变p1指针的指向
```

**总结：const在*右边，即为常量指针，不能改变这个指针的指向，但是可以通过指针改变其指向的值。**

双重const限定,既不可以修改指向，也不可以修改指向的内容。

```c++
int num=20;
int num2=30;
const int *const p=&num;
p=&num2;//error
*p=30//error
```

<font color='red'>**const常量和宏定义常量的区别**</font>

1. <font color=red>**发生的时机不同**</font>：C语言中的宏定义发生时机在预处理时，做字符串的替换，如果出现了bug，则需要到运行阶段才可以发现；而const常量是在编译时（const常量本质还是一个变量，只是用const关键字限定之后，赋予只读属性，使用时依然是以变量的形式去使用）

2. <font color=red>**类型和安全检查不同**</font>：宏定义没有类型，不做任何类型检查；**const常量有具体的类型**，在编译期会执行类型检查。在使用中，应尽量以const替换宏定义常量，可以减小犯错误的概率。

#### **指针数组和数组指针**

```C++
//数组指针，是一个指向数组的指针
//指针数组，存储指针的数组
int arr[5]={1,2,3,4,5}
&arr//对数组去地址和直接打印数组的名称得到的内容一样
cout<<arr+1<<endl;//增加4字节到下一个元素
cout<<&arr+1<<endl;//增加20字节，跳过整个数组。
int (*p1)[5]=&arr;//这是一个指针，指向了包含5个int元素的数组
int a=10,b=20,c=30,d=40,e=50;
int *p2[5]={&a,&b,&c,&d,&e};//指针数组，是一个数组，里面存储了五个指针
```

#### 函数指针和指针函数

```c++
//函数指针：是一个指向函数的指针
int add(int a,int b){
    return a+b;
}
void test(){
    //可以对函数取地址操作，可以定义一个指针指向这个函数
    cout<<(void *)&add<<endl;
    //函数指针的定义
    //返回类型 指针变量名称（函数的参数列表）=指向的函数名称
    int (*p)(int,int)=add;
    //以下两种方式等价
    cout<<add(1,2)<<endl;
    cout<<p(1,2)<<endl;
}
//指针函数：返回值为指针的函数
int num=30;
int *func(){
    return &num;
}

```

#### **函数指针的使用**

```c++
#include <iostream>
using std::cout;
using std::endl;
//函数指针的使用
//实现一个简易的计算器的功能，实现加减乘除的运算
//在C++中，如果使用char *的话，强烈建议大家加上const修饰
//const char * pstr = "hello,world";
int add(int a, int b){
    return a + b;
}
int sub(int a, int b){
    return a - b;
}
int multiply(int a, int b){
    return a * b;
}
int divide(int a, int b){
    return a / b;
}
//const char * 利用==符号判断是否和后面的常量值相等
//strcmp
int calc(int leftNumber, const char * operation, int rightNumber){
    //定义一个函数指针，根据不同的情形，让这个指针
    //去指向不同的函数
    int (*pFunc)(int,int);
    if(operation == "+"){
        pFunc = &add;
    }else if(operation == "-"){
        pFunc = &sub;
    }else if(operation == "*"){
        pFunc = &multiply;
    }else if(operation == "/"){
        pFunc = &divide;
    }
    return pFunc(leftNumber, rightNumber);
}


void test(){
    cout << calc(10, "+", 20) << endl;
    cout << calc(10, "-", 20) << endl;
    cout << calc(10, "*", 20) << endl;
    cout << calc(20, "/", 10) << endl;
}

int main()
{
    test();
    return 0;
}


```

在c++中，如果使用char *，记得加上const修饰。

#### **c++代码中的头文件引用顺序**

1.自己定义的头文件写在最顶端

2.c语言的头文件其次

3.c++标准库的头文件随后

4.第三方库的头文件最后

#### <font color='red'>**申请/回收堆空间**</font>

free和malloc函数

new和delete表达式

```c++
void test(){
    //使用new也不需要进行初始化操作
    int *pInt=new int();
    *pInt=20;
    delete pInt;
}
void test1(){
    int array=new int[5]();
    for(int i=0;i<5;i++){
        array[i]=i;
    }
    //需添加一个[]，不然无法回收全部空间
    delete [] array;
}
```

**区别：**

1.malloc/free是库函数，new/delete是表达式。

2.malloc的返回值是void *类型使用的时候需要强转；new的返回值就是我们需要的类型

3.malloc需要提供申请堆空间大小的参数，new不需要提供大小。

4.malloc申请的空间是未初始化的空间，new申请的空间是初始化的空间，默认是当前数据类型的0值，也可以设置一个希望的值。

#### **<font color='red'>引用</font>**

引用是一个已定义变量的别名。

```C++
//定义方法 类型 &ref=变量
int num=10;
//注意此时&表示引用
//如何区分&什么时候是取地址，什么时候是引用
//如果&前面有数据类型（强转除外）那么就表示引用
int & ref=num;
```

引用必须绑定到某个特定的变量，一经绑定无法再次绑定，对于引用的操作修改会直接影响到变量的本体。

声明引用的同时，必须初始化，否则会编译报错。

##### **<font color='red'>引用和指针的区别与联系</font>**

**联系：**

1.引用和指针都有地址的概念，都可以间接的访问变量。指针指向某块内存，存储的是内存的地址。引用则是某块内存的别名。二者都可以间接去操作变量的本体。

2.引用的本质还是指针，可以视为一个操作受限的指针。

**区别：**

1.引用是一个别名，而指针是一个实体。

2.引用只能初始化一次，后面不可以改变，而指针可以变。

3.引用使用时无需解引用，而指针使用时需要解引用。

4.sizeof引用得到的是所指向的变量大小，而sizoef指针得到的是指针的大小。

5.指针和引用的自增运算含义不同。



##### **引用的使用场景**

**<font color='red'>引用作为函数的参数</font>**

```c++
//作为函数的参数
//此时传递的是这个数值
void swap(int a,int b){//值传递，发生数值复制
    int temp=a;
    a=b;
    b=temp;
}
void swap2(int *pa,int *pb){//地址传递，发生地址值的复制
    int temp=*pa;
    *pa=*pb;
    *pb=temp;
}
//swap里面的形参地址值和实参地址一样
//可以修改原有操作数
void seap3(int & a,int & b){//引用传递，不发生复制
    int temp=a;
    a=b;
    b=temp;
}
void test(){
    int x=10,y=20;
    swap(x,y);
    cout<<x<<y<<endl;//x=10,y=20
    swap2(x,y);
    cout<<x<<y<<endl;//x=20,y=10
    swap3(x,y);
    cout<<x<<y<<endl;//x=20,y=10
}
```

##### 参数的传递

**值传递：**值传递时，会在内存空间给形参开辟内存空间，将实参的值复制给形参，形参只是实参的副本。当函数传递的是类对象时，复制会产生不必要的开销。

**引用传递：**其效果和指针传递相同。其不需要开辟内存空间给形参使用，函数调用时形参会被当做实参变量或别名来使用，实际上对形参的操作就是对实参的操作。

**指针传递：**使用指针传递时，仍然需要给形参指针开辟内存空间，但是由于指针的灵活性，使用时可能会产生一些问题。

如果不希望函数体中通过引用改变传入的变量，那么可以使用<span style=color:red;background:yellow>**常引用作为函数参数**</span>

------

**引用作为函数的返回值**

要求：当以引用作为函数的返回值时，<span style=color:red;background:yellow>**返回的变量其生命周期一定是要大于函数的生命周期**</span>的，即当函数执行完毕时，返回的变量还存在。

目的： 避免复制，节省开销

```c++
//作为函数的返回值
int func(){
    int a=10;
    //在没有使用引用的情况下，return结果时，会有一次拷贝复制的过程
    return a;
}
void test(){
    int b=func();
    cout<<b<<endl;
    //在c++中称为右值，可以理解为临时对象，临时变量，不可以进行取地址操作
    cout<<&func()<<endl;//error
    
}
```

**<font color='red'>注意事项：</font>**

1.**不要返回局部变量的引用**，因为局部变量会在函数返回后被销毁，被返回的引用就成为了"无所指"的引用，程序会进入未知状态。

```c++
int & test(){
    int num=10;
    return &num;
}
```

2.**不要轻易返回一个堆空间的引用**，容易造成内存泄漏。

```C++
int & func(){
    int array=new int[5]();
    return array;
}
```

如果函数返回的是一个堆空间变量的引用，那么这个函数调用一次就会new一次，非常容易造成内存泄露。所以谨慎使用这种写法，并且要有完善的回收机制。

#### **函数重载**

函数重载：可以定义出一系列具有相同名称的函数。

在c语言中，要求在同一个作用域内不可以定义名称相同的函数。在c++中可以定义名称相同的函数。

**函数重载的条件**：函数的参数个数，参数类型，参数顺序任意一个不同即可。返回值不同不是函数重载的条件。

```C++
int add(double a,double b);
int add(double a,double b,double c);
int add(int a,int b);
double add(int a,int b);//error
```

函数重载中函数的返回值不是区分的标志，函数的参数列表是函数重载区分的标志。

函数的参数个数，参数类型，参数顺序的组合。

**函数重载的原理**：其实就是名称改编

#### **默认参数**

缺省参数，默认填充的数值，参数匹配从左往右。

**默认参数的声明**

```c++
//默认参数的设置一般会在函数声明和定义分开的情况中去设置
//声明
int add(int a,int b);
int add2(int a,int b);
//定义
int add(int a,int b){
    return a+b;
}
int add2(int a=0,int b=0){
    return a+b;
}
void test(){
    cout<<add(1,4)<<endl;//5
   //如果默认参数设置在定义中 函数调用时，只看到函数的声明，没有看到定义
    cout<<add()<<endl;//error
}
```

**默认参数设置顺序**

默认参数的设置顺序严格从右往左定义，如果某个形参设置了默认值，那么该形参右边的参数都需要设置默认值。

设置了默认参数之后，可以形成一系列的重载函数，所以设置了默认参数之后，那么函数重载需要特别留意防止冲突。

函数的参数匹配是从左往右进行匹配的。

#### **inline函数**

减少函数调用的开销，如果使用宏定义非常容易出错，且难以调试。

inline的使用，只需在我们定义的函数之前加上inline关键字，会在编译时进行展开，执行代码的替换操作。

inline只是一个建议，并不是强制性的，最终建议是否执行取决于编译器。如果有效，就会在编译时展开，本质是字符串的替换，不会增加开销，而且有类型检查，较为安全。

**适用场景：**适用于那些函数体短小，且需频繁使用的函数，如果函数体内容太长，且有循环不建议使用内联函数。

**inline VS 宏函数**

宏函数：只是字符串的替换，没有函数的开销，适用于比较短小的代码，但是没有类型检查机制，存在安全隐患，容易出错。

inline函数：本质也是字符串的替换，开销也比较小，但是又类型检查机制，较为安全，但不适用于函数体内容过长的函数和具有循环的函数体。

**注意事项：**

1.如果要把内联函数声明在头文件中，那么内联函数的定义也必须在头文件中，否则会出错。如果头文件中只有声明没有定义，会被认为没有定义替换规则。因为编译器在调用内联展开函数的代码时，必须能够找到inline函数的定义才能够将函数替换为函数代码。

<font color='red'>谨慎使用内联函数</font>

#### **异常处理**

try-catch 语法块

```c++
try {
//语句块
} catch(异常类型) {
//具体的异常处理...
} ...
catch(异常类型) {
//具体的异常处理...
}
```

 try-catch语句块的catch可以有多个，至少要有一个，否则会报错。

- 执行 try 块中的语句，如果执行的过程中没有异常拋出，那么执行完后就执行最后一个 catch块后面的语句，所有 catch 块中的语句都不会被执行；
- 如果 try 块执行的过程中拋出了异常，那么拋出异常后立即跳转到第一个“异常类型”和拋出的异常类型匹配的 catch 块中执行（称作异常被该 catch 块“捕获”），执行完后再跳转到最后一个catch 块后面继续执行。

注意：<font color=red>**catch的是类型，不是具体信息**</font>。

#### **<font color='red'>内存布局</font>**

从高地址到低地址分为五个区域：栈区，堆区，全局/静态区，文字常量区，程序代码区。

**栈区：**存放了栈变量，栈对象，局部变量，函数的参数等

**堆区：**存放malloc/new等操作申请的空间

**全局/静态区：**读写数据段，存放全局变量，静态变量

**文字常量区：**文字常量和全局的常量。使用cout输出char *指针时，默认情况下显示的是字符串的内容，并不是显示的地址值，如果希望显示的是地址值，则需要强转为void *类型。

**程序代码区：**只读段，存放函数的二进制代码。

<font color='red'>注意：局部变量标注const修饰，不会存储在全局常量区。</font>

![image-20250705143156711](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250705143156711.png)

#### <font color='red'>**字符串**</font>

**c风格字符串**

字符数组：

```C++
void test(){
    //字符数组
    char str[6]="hello";
    char str2[6]={'h','e','l','l','o'};
    char str3[]="hello";
    cout<<str<<" "<<str2<<" "<<str3
<<endl;
    //字符数组：可以修改字符串的值，不可以修改指向
    str[0]='H';//right
    cout<<str<<endl;
    str2="World";//error,因为数组名称代表的是数组首元素的地址，如果指向了一个新的元素，那么现在的中国数组就无法指向了，后续操作系统也无法进行回收。
}
```

字符指针：指针指向堆区，指针指向常量区

```C++
//指针指向常量区
void test2(){
    char *pstr="hello";
    pstr[0]='H';//error 不可以修改字符串的值，因为hello位于文字常量区
    pstr="world";//可以变更指向
    cout<<pstr<<endl;
}
```

```C++
//指针指向堆区
void test3(){
    char *str=new char[5+1]();
    strcpy(str,"hello");
    cout<<str<<endl;
    str[0]='H';//可以修改字符串的值
    str=new char[15]();//可以改变，但是会导致内存泄漏
    strcpy(str,"hello world");
    cout<<str<<endl;
    
    delete [] str;
    str=nullptr;
}
```

**求解字符串长度**

```c++
void test(){
    char str[6]="hello";
    const char *pstr="hello";
    cout<<sizeof(str)<<endl;//6
    cout<<sizeof(pstr)<<endl;//8
    cout<<strlen(str)<<endl;//5
    cout<<strlen(str)<<endl;//5
}
```

**string类**