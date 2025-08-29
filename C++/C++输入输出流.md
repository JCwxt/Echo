# 3.C++输入输出流

#### 3.1常用流的分类：

##### **标准I/O：**

1.istream:通用输入流

2.ostream:通用输出流

3.iostream:通用输入输出流

##### **文件I/O：**

1.ifstream:文件输入流

2.ofstream:文件输出流​

3.fstream：文件输入输出流

##### **串I/O:**

1.istringstream:字符串输入流

2.ostringstream：字符串输出流

3.stringstresm：字符串输入输出流

#### 3.2流的四种状态

##### badbit:

系统级错误，通常情况下一旦badbit被置位，流就无法再使用了

##### failbit:

可恢复的错误，例如期望读取一个int数值，却读取了一个字符串等错误，这种问题可以修改，流还可以继续使用。

##### eofbit:

到达流结尾的位置，流在正常输入输出的情况下结束，会被置为eofbit状态。

##### goodbit:

有效状态，流在有效状态下，才能正常使用，**如果badbit,failbit,efobit任何一个被置位，则流无法正常使用**。

```C++
bool good() const      //流是goodbit状态，返回true，否则返回false
bool bad() const       //流是badbit状态，返回true，否则返回false
bool fail() const      //流是failbit状态，返回true，否则返回false
bool eof() const       //流是eofbit状态，返回true，否则返回false
```

#### 标准I/O

标准输入流：从键盘录入，读取到内存中,std::cin，全局输入流对象。

标准输出流：从内存显示到显示器终端，std::cout。

流提取符>>从流中提取数据时通常跳过输入流中的空格，tab键，换行符等空白字符，只有在输入完数据再按回车键，该行数据才会被送入键盘缓冲区，形成输入流，提取运算符<<才能从中提取数据。

cin和cout全部定义在头文件iostream中。

clear():恢复流的状态

ignore():清空缓冲区

```C++
cin.clear();//恢复流状态
cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//清空缓冲区
```



#### 为什么要引入缓冲机制？

一方面主要为了去减少频繁读取的次数，另一方面也是为了去协调各个组件之间的速率差异。

从硬盘中读取数据，一次性会读取很多，并不是只会读取我们所需要的这部分数据，可能要比我们需要的数据还要多。

因为硬盘的读取速度是比较慢的，如果频繁的读取，那么整个操作的速度就会比较慢。

**缓冲区的分类**

全缓冲：

行缓冲：

不带缓冲：cerr错误输出，不需要缓冲，发送错误，直接

刷新缓冲区：

1.如果程序正常结束，缓冲区会刷新。

```C++
void test(){
    for(int i = 0; i < 1025; ++i){
        cout << 'a';
    }
}
```

2.缓冲区满，会导致立刻刷新缓冲区的数据。

```C++
void test(){
    for(int i=0;i<1025;i++){
        cout<<'a';
    }
    sleep(4);
}
//先输出1024个a(缓冲区大小为1024),休眠4秒后，输出最后一个a,因为程序结束了
```

3.换行立刻刷新缓冲区。

```C++
void test{
    //加了endl 先输出五个a,再休眠5秒
    //不加，先休眠5秒，再输出5个a
    for(int i=0;i<5;i++){
        cout<<'a'<<endl;
    }
    sleep(5);
}
```

endl等价于刷新缓冲区+换行

cerr没有缓冲区

cout有缓冲区

#### 文件I/O

文件输入流:  从外存文件流入内存的数据。

文件输出流：从内存流向外存文件。

每一个文件流都有一个内缓冲区与之对应。

文件流的构造函数

```C++
ifstream();
explicit ifstream(const char* filename, openmode mode = ios_base::in);//操作的文件的名称;文件的打开模式，读取模式
explicit ifstream(const string & filename, openmode mode = ios_base::in);

ofstream();
explicit ofstream(const char* filename, openmode mode = ios_base::out);//操作的文件的名称;文件的打开模式，写入模式
explicit ofstream(const string & filename, openmode mode = ios_base::out);

fstream();
explicit fstream(const char* filename, openmode mode = ios_base::in|out);
explicit fstream(const string & filename, openmode mode = ios_base::in|out);
```

##### 文件输入流对象的创建

文件流输入流的信息传输方向：文件------->文件输入流对象的缓冲区------->程序中的数据结构。

1.使用无参构造函数创建ifstream对象，再使用open函数将这个文件输入流对象与文件绑定。若文件不存在，则文件输入流进入failbit状态。

2.使用有参构造函数，在创建时就将流对象与文件绑定，后续操作这个流对象就可以对文件进行相应操作。

##### 文件输入流的使用

1.使用>>将缓冲区里面的数据写入到某个变量，默认情况下，分隔符是空格，换行符，制表符等，把一个个单词写入到某个变量中。

```tex
//hello.txt
hello java
hello c++
hello c
```



```C++
#include <iostream>
#include <fstream>
#include <string.h>
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::string;
using std::cerr;
void test(){
   ifstream ifs("hello.txt");
   if(!ifs.good()){
       cerr<<"this file is not found"<<endl;
       return;
   }
   string word;
   //将文件输入流缓冲区里面的数据写入word
   while(ifs>>word){
       cout<<word<<endl;
   }
}

int main()
{
 test();
 return 0;
}

```

![image-20250711141342762](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250711141342762.png)

2.使用string头文件所提供的getline的方法，每一次读取一行数据。 getline的返回值是istream对象，依然可以将getline放置在while语句中，依然会进行隐式类型转化。

```C++
void test2(){
    ifstream ifs("hello.txt");
    if(!ifs.good()){
        cerr<<"this file is not found"<<endl;
        return;
    }
    string line;
    while(getline(ifs,line)){
        cout<<line<<endl;
    }
}
```

![image-20250711142207308](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250711142207308.png)

3.read将读取的数据放入一个字符数组中，其中第一个参数表示的是文件输入流的数据读取到字符数组中，第二个参数表示的是读取多少个字符。

```C++
void test3(){
    ifstream ifs("hello.txt");
    if(!ifs){
        cout<<"the file is not found"<<endl;
    }
    //将游标移动到文件末尾
    ifs.seekg(0,std::ios::end);
    int len=ifs.tellg();
    cout<<len<<endl;
    ifs.seekg(0,std::ios::beg);
    char *buf=new char[len+1]();
    //将文件读入buf
    ifs.read(buf,len);
    cout<<buf<<endl;
    

}
```

![image-20250711174641223](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250711174641223.png)

**seekg():**设置游标位置。从文件中读取内容是存在一个文件游标，读取时，从文件游标的位置开始读取。

**调用seekg时有两种方式：**

1.绝对位置：可以直接传入参数，游标将从参数位置开始读取，例如设为0，从文件起始处开始读取。

2.相对位置：传入偏移量和基准点。第一个参数：相对基准点需要向前偏移则传入负数，不偏移则传入0，需要向后偏移则传入正数。

第二个参数格式有：std::ios::beg 流的开始

​                                   std::ios::end 流的结尾

​                                    std::ios::cur 流位置指示器的当前位置。

**tellg():**获取游标的位置。

```c++
//读取一个文本文件中指定下标区域之间的全部数据，并将数据写入到一个字符串中
//read+seekg+tellg
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::cerr;
void test(){
    cout<<"请输入起始位置和结束位置:"<<endl;
    int start=0,end=0;
    cin>>start>>end;
    ifstream ifs("hello.txt");
    if(!ifs){
        cerr<<"the file is not found"<<endl;
    }
    ifs.seekg(0,std::ios::end);
    if(start>end||end>ifs.tellg()){
        cerr<<"postion is error"<<endl;
    } 

    ifs.seekg(start);
    int len=end-start;
    char *buf=new char [len+1]();
    ifs.read(buf,len);
    cout<<buf<<endl;
}

int main()
{
 test();
 return 0;
}

```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250711174752883.png" alt="image-20250711174752883" style="zoom: 67%;" />

![image-20250711174805657](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250711174805657.png)

##### 文件输出流

流向：从位于内存中的数据流向位于外部存储设备的文件中。

作用：将流对象保存的内容传输给文件。

1.借助构造函数创建一个ofstream对象

2.借助于有参构造函数直接创建一个和文件进行关联的ofsteam对象

如果ofstream绑定的文件不在，会创建一个文件。

##### 文件输出流的使用

1.使用<<运算符，将变量中的数据读取到文件输出流的缓冲区中，后续会将该缓冲区的数据写入文件。

```C++
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::cin;
using std::ofstream;
void test(){

    ofstream ofs("data.txt");
    ofs<<"hello world"<<endl;
    ofs<<"hello world"<<endl;
}

int main()
{
 test();
 return 0;
}

```

![image-20250711192948836](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250711192948836.png)

如果此时多次执行该函数，只会写入两行hello word，因为这种创建方式会使打开模式默认为std::ios::out，<font color=red>**每次都会清空文件的内容**</font>。

文件模式一共有六种，它们分别是:

<font color=red>**in **</font>: 输入，文件将允许做读操作；如果文件不存在，打开失败

<font color=red>**out**</font> : 输出，文件将允许做写操作；如果文件不存在，则直接创建一个

<font color=red>**app**</font> : 追加，写入将始终发生在文件的末尾,强制所有写入都发生在文件末尾

<font color=red>**ate**</font> : 末尾，立即定位到文件的末尾，但是后续可以自由移动指针到其他位置进行读写

trunc : 截断，如果打开的文件存在，其内容将被丢弃，其大小被截断为零

binary : 二进制，读取或写入文件的数据为二进制形式

2.使用write

```C++
void test2(){
    ofstream ofs("write.txt",std::ios::app);
    char str1[20]="hhhhhhhh";
    ofs.write(str1,strlen(str1));

    string str2=" world";
    //需将c++字符串转化成c风格字符串
    ofs.write(str2.c_str(),str2.size());
    ofs.close();
}
```

![](C:\Users\34078\Pictures\Screenshots\屏幕截图 2025-07-11 194036.png)

##### 文件输入输出流

```C++
//使用键盘的录入功能，录入5个数字，并且存入文件中，随后读取文件的数据，将之前录入的数据显示出来。
#include <iostream>
#include <fstream>
using std::cout;
using std::fstream;
using std::endl;
using std::cin;
using std::cerr;
void test(){
    fstream fs("fs.txt");
    if(!fs){
        cerr<<"the file is not found"<<endl;
        return ;
    }
    int num;
    for(int i=0;i<5;i++){
        cin>>num;
        fs<<num<<" ";
    }
    fs.seekg(0);//如果此时没有将游标移回文件的开始处，会输出5 5 5 5 5
    for(int i=0;i<5;i++){
        fs>>num;
        cout<<num<<" ";
    }
}

int main()
{
 test();
 return 0;
}

```

![image-20250711195249823](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250711195249823.png)

#### 字符串I/O

主要用于格式转化。

##### 字符串输入流

将字符串进行分割处理，默认的分隔符是空格，换行符，制表符。

创建字符串输入流对象时传入c++字符串，字符串的内容就被保存在了输入流对象的缓冲区中。之后可以通过输入流运算符将字符串内容输出给不同的变量，起到了字符串分隔的作用。



```C++
#include <iostream>
#include <string.h>
#include <sstream>
using std::cout;
using std::istringstream;
using std::endl;
using std::cin;
using std::string;
void test(){
    string str="123 456 789 10";
    //创建对象
    istringstream iss(str);
    int num;
    while(iss >>num){
        cout<<num<<endl;
    }
}

int main()
{
 test();
 return 0;
}

```

![image-20250711200445484](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250711200445484.png)

##### 字符串输出流

主要使用场景，将其它各种数据类型转化成字符串类型。

```C++
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::cin;
using std::ostringstream;
void test(){
    int num = 123;
    double num2 = 456;
    ostringstream oss;
    //把所有的内容都传给了字符串输出流对象
    oss << "num = " << num << " , num2 = " << num2 << endl;
    cout << oss.str() << endl;
}
int main()
{
 test();
 return 0;
}

```

![image-20250711200801447](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250711200801447.png)

```C++

```

