### Qt

### Qt基本概念

#### 1.QtCreator的几种常见模式

欢迎模式、编辑模式（写代码的模式）

设计模式（界面设计需要使用的模式）

调试模式（调试代码的模式）

帮助模式（帮助手册，用于查找类、类中函数使用的模式）

#### 2.Qt的三个基类

QMainWindow：表示主窗口类，它里面会自带菜单栏、工具栏、状态栏、中心部件等元素。

QWidget：表示最朴素的没有任何额外内容的窗口类。

QDialog：表示对话框类，它里面会自带一个中心部件，一般用来实现简单的提示信息和用户输入。

#### 3.Qt的项目结构

项目文件.pro文件，是qmake工具的输入文件，用于描述项目的结构，依赖关系，和构建过程。

Headers文件夹存放了所有的头文件

Sources文件夹存放所有的实现文件

Froms界面文件存放所有的界面文件

特别的，qmake是Qt提供的一个跨平台的构建工具，在构建项目时，IDE会根据.pro 文件和所在的操作系统生成相应的构建脚本，如Makefile或 Visual Studio项目文件，这样用户就可以进行项目的实际编译和链接。.pro 文件是qmake工具的输入文件，用于描述项目的结构、依赖关系以及构建过程，这个文件包含了源代码文件、头文件、资源文件、库文件等各种构建所需的元素，以及构建选项和配置。

#### 4.Qt的模块

在Qt5中将模块分为3个部分：**Qt Essentials(Qt基本模块)**、**Qt Add-Ons(Qt扩展模块**)、**Qt Tools(Qt开发工具)** 。其中基本模块是核心模块，定义了适用于所有平台的基础功能，在Qt5中，它们将保持源代码和二进制兼容，其中，基本模块中的QtCore模块是基础，所有其他的Qt模块都要依赖于这个模块。

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250812193840058.png" alt="image-20250812193840058" style="zoom:67%;" />

**Q_OBJECT**是Qt的内置宏，使用该宏的目的是为了后续可以使用qt自己的语法。特别的，使用该宏后，就可以使用元对象系统。

在一个Qt程序中QApplication只能创建一个对象。

### 元对象系统

#### 1.元对象的基本概念

元对象指能够操纵，创建，描述或执行其它对象的对象，被元对象描述的对象称为基对象。

#### 2.元对象系统的基本概念

元对象系统是Qt框架在c++基础上扩展的一套运行时动态特性机制。

核心是通过预编译（moc工具）生成额外的元信息代码，使得原本静态的C++类具备动态能力。

元对象系统具备以下功能：

- 运行时查询类名、方法、属性（反射）；
- 支持信号（signal）与槽（slot）的跨对象通信；
- 动态添加、修改属性（Q_PROPERTY）。

#### 3.设计元对象系统的目的

1.可以进行对象之间的通信

2.弥补c++语法本身对运行时支持的缺陷

3.框架需求

#### 4.元对象系统的三大组成部分

1.自定义的类或库中的类要直接或者间接的继承QObject。

2.在头文件中还要使用宏Q_OBJECT。

3.使用元对象编译器moc。

只有继承QObject类且在类定义中使用Q_OBJECTl宏的类才可以使用Qt的元对象系统。因为Qt的元对象系统工作依赖其三大核心组件继承QObject类，在头文件中使用宏Q_OBJECT，使用元对象编译器moc。

#### 5.元对象编译器

元对象编译器，也就是MOC,作用就是将带有Q_OBJECT宏的头文件进行处理，会产生两个文件`moc_*.cpp` 与 `moc_*.o`文件。再将新的cpp文件以及老的cpp文件一起编译链接，最终生成可执行程序，**特别注意：moc生成的cpp文件会与项目中的其它cpp文件一起编译链接。**

![image-20250812195500006](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250812195500006.png)

### 信号与槽机制（重要）

#### 1.信号与槽

##### 1.基本原理

![image-20250812195815288](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250812195815288.png)

##### 2.作用

就是为了在Qt之间让对象之间进行通信。

##### 3.连接信号与槽的函数connect

```C++
//字符串形参
[static] QMetaObject::Connection QObject::connect(
const QObject *sender
, const char *signal, const QObject *receiver
, const char *method
, Qt::ConnectionType type = Qt::AutoConnection);

// 没有接收者的版本
[static] QMetaObject::Connection QObject::connect(
const QObject *sender
, PointerToMemberFunction signal
, Functor functor);

// 函数指针形参
[static] QMetaObject::Connection QObject::connect(
const QObject *sender
, PointerToMemberFunction signal
, const QObject *receiver
, PointerToMemberFunction method
, Qt::ConnectionType type);
```

##### 4.标准信号与槽

```C++
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::close);
}
//信号的发送者：ui->pushButton，通过ui找到的pushButton对象
//发送的信号：按钮中的信号clicked，该函数是标准的信号；
//信号的接受者：this指针指向的是Widget对象，也就是信号的接受者；
//槽函数：是QWidget中的槽函数，关闭窗口;
```

对于ui界面的方式来使用标准信号与槽的时候，可以在部件或者控件上右键，选择“Go to slot”，然后选择对应的信号，就可以在相应的头文件中声明槽函数，并且在实现文件中实现槽函数，那么后续只需要在槽函数中实现具体的代码逻辑就可以了，并且这种方式是可以不要显示调用connect去连接信号与槽，就会自动连接。此时这个槽函数的命名方式就是 "on + _ + 信号发送者的名字 + _ + 信号的名字"

#### 2.自定义信号与槽

##### 信号的触发

信号与槽连接之后，为了让信号执行，所以需要使用emit进行触发信号，当然信号触发的关键字emit可以省略。

对于标准的信号与槽，只需要连接即可，不需要显示调用emit触发信号。

##### 自定义信号的条件

自定义的类需要直接或者间接继承自QObject基类

在自定义类的头文件中需要包含宏Q_OBJEC宏。

##### 自定义信号的规则

自定义信号的关键字是signals，然后后面加上":"，后面再声明信号的函数，在signals的前面不需要加上public/protected/private，因为signals默认就是public.

信号只需要声明，并不需要实现。

信号的返回结果一般是void，信号函数是可以进行传参的。

##### 自定义槽函数的条件

自定义的类需要直接或者间接继承自QObject基类

在自定义类的头文件中需要包含宏Q_OBJEC宏。

##### 自定义槽函数的规则

槽函数的关键字是slots，然后后面需要加上”：“,但是槽函数与信号不一样，可以使用public/protected/private进行修饰。

特别的，对于Qt5以上的版本，此处的slots关键字可以直接省略。

槽函数不仅要有声明，还必须要有实现。

槽函数的返回结果一般也是void，但是特别需要注意，槽函数的参数是需要受到信号的参数的影响。因为信号与槽一旦连接之后，信号中的参数是会传递给槽函数的，所以槽函数的参数个数往往都是小于等于信号的参数个数。

#### 3.信号与槽连接使用的传递方式

##### 1.Qt4的写法

在Qt4中信号的指定必须使用宏SIGNAL和槽指定必须使用宏SLOT，这两个宏能把括号中的内容转换为与形参相对应的 const char*形式。在指定函数时，只能指定函数参数的类型，不能有参数名，也不能指定函数的返回类型。比如SLOT(func(int x))，是错误的，因为指定了参数名x，正确形式为SLOT(func(int))

```C++
//Qt4中的写法，该写法会将SIGNAL/SLOT中传递进来的当做字符串
//进行处理，其实，传递任何不存在的都可以让编译通过，但是在运行
//的时候，才能知道有没有出现问题，所以这种写法没有类型检测，
//是不安全，不建议使用    
QObject::connect(&tch,SIGNAL(treat()),&stu,SLOT(eat()));
tch.treat();
QObject::connect(&tch,SIGNAL(t222()),&stu,SLOT(eat333()));//即使t222不存在，也可以编译通过
```

##### 2.**Qt5的写法（推荐）**

```C++
connect(m_ptc, &Teacher::treat, m_pst, &Student::eat);
```

使用的是成员函数指针的写法，特别的如果信号与槽有重载版本的时候，需要加以调整，方式有三种。

##### 3.Qt5解决重载版本

```C++
    void (Student::*pstu1)()=&Student::eat;
    void (Teacher::*pth1)()=&Teacher::treat;
    QObject::connect(&tch,pth1,&stu,pstu1);
    tch.treat();

    void (Student::*pstu2)(QString)=&Student::eat;
    void (Teacher::*pth2)(QString)=&Teacher::treat;
    QObject::connect(&tch,pth2,&stu,pstu2);
    tch.treat("早晚稻");
```

这种方式可以解决重载版本，但是使用起来非常的麻烦，所以可以使用c++11或者c++14的方式。

##### 4.c++11解决重载版本

```c++
QObject::connect(&tch,QOverload<>::of(&Teacher::treat),
                 &stu,QOverload<>::of(&Student::eat));
tch.treat();
QObject::connect(&tch,QOverload<QString>::of(&Teacher::treat),
                 &stu,QOverload<QString>::of(&Student::eat));
tch.treat("早晚稻");
```

##### 5.c++14解决重载版本

```C++
QObject::connect(&tch,qOverload<>(&Teacher::treat),
                 &stu,qOverload<>(&Student::eat));
tch.treat();
QObject::connect(&tch,qOverload<QString>(&Teacher::treat),
                 &stu,qOverload<QString>(&Student::eat));
tch.treat("早晚稻");
```

注意，因为Qt5。14.2默认支持c++1,所以如果使用c++14语法，需要修改文件。

##### 6.lambda表达式的方式

```C++
QObject::connect(&tch,QOverload<>::of(&Teacher::treat),[](){
        qDebug()<<"大米先生"<<endl;
});
tch.treat();
QObject::connect(&tch,qOverload<QString>(&Teacher::treat),[](QString food){
        qDebug()<<food<<endl;
});
tch.treat("早晚稻");
```

#### 4.信号与槽的关系

槽的参数类型需要与信号参数类型相对应。

如果信号的参数个数多余槽的参数个数，则多余的参数将被忽略。

一个信号可以与多个槽关联，多个信号也可以与一个槽关联。

如果信号连接到另一个信号，则当第一个信号发射时，会立即发射第二个信号。

如果一个信号关联到多个槽时，则发射信号时，槽函数按照关联的顺序依次执行。

#### 5.信号与槽的优缺点

信号和槽的关键特征

- 松耦合：发送者和接收者相互独立，无需直接依赖；
- 灵活性：支持一对多、多对一的信号与槽关联；
- 类型安全：编译期进行严格的类型检查，确保参数匹配。
- 线程安全：根据连接方式（Qt::AutoConnection/QueuedConnection）自动决定是否跨线程调用槽；

信号与槽机制能增强对象之间通信的灵活性，但是也会损失一些性能，原因：

- 多线程的时候，信号可能需要排队等待；
- 编组/解组传递的参数；
- 安全的遍历所有的关联；
- 需要定位接收信号的对象。

一般来说，发射与某些槽连接的信号，大约比直接调用接收者要<span style=color:red;background:yellow;font-size:20px>慢十倍</span>，而且这是非虚函数调用的情况。

### 对象树

##### 1.基本概念

在Qt 中，对对象的管理，使用的是树形结构，也就是对象树。QObject以对象树的形式组织起来，当为一个对象创建子对象时，子对象会自动添加到父对象的children()列表中。父对象拥有子对象的所有权，父对象可以在自己的析构函数中删除其子对象。也可以使用findChild()或findChildren()通过名称和类型查询子对象。

注意：这里是指类的对象而不是类。父子关系是Qt特有的，与类的继承关系无关。传递的参数与parent有关（基类、派生类），这是对于继承体系来说的，与parent无关。

**<font color='red'>需要特别注意一点，在Qt中对象之间的父子关系不是C++中的继承关系，而是Qt中对象之间的关系。</font>**

##### **2.作用：**

在Qt中，经常使用指针，那么也会经常使用堆空间，那么为了将堆空间进行更换的回收，所以Qt中有一个概念，叫做对象树，作用就是为了回收堆空间，解决内存泄漏。

##### **3.结构：**

在Qt中，最基础和核心的类是QObject。QObject内部有一个名为children的QObjectList列表，用于保存所有子对象，还有一个指针parent，用来指向父对象。当自身析构时，会先将自己从父对象的列表中删除，并析构所有的子对象。

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250813160413932.png" alt="image-20250813160413932" style="zoom: 50%;" />

##### 4.使用：

```C++
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //如果不指定obj的父对象，就需要显示调用删除操作或者将obj设定为栈对象，
    //但是设置了obj的父对象为parent后，就可以使用对象树删除obj指向的对象  
    MyObject parent;
    MyObject *obj=new MyObject(&parent);
    Widget w;
    w.show();
    return a.exec();
}
```

### 属性系统

#### 基本概念

一种运行时动态扩展对象属性的机制，允许在不修改类定义的前提下，访问，添加，修改对象属性，目的在于简化对象属性的管理和访问。

#### 动态属性

可以在运行的时候，动态的给对象设置属性，添加属性以及获取属性。

在Qt中，数据成员与属性没有关系，不要将二者画等号。

```C++
//获取或访问属性
QVariant QObjtect::property(const char *name) const;

//添加或者修改属性
bool QObjtect::setProperty(const char *name, const QVariant &value);
```

```C++
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    MyObject *obj=new MyObject(&w);
    obj->setProperty("name","zhiyin");
    obj->setProperty("age",18);
    qDebug()<<obj->property("name").toString();
    qDebug()<<obj->property("age").toInt();
    return a.exec();
}
```

#### 显示声明属性

由于基于元对象系统，该类必须继承自QObject类，还应使用Q_OBJECT 宏，然后使用QObject::Q_PROPERTY宏声明属性，语法如下  

```C++
Q_PROPERTY(type name
           (READ getFunction [WRITE setFunction] |
            MEMBER memberName [(READ getFunction | WRITE setFunction)])
           [RESET resetFunction]
           [NOTIFY notifySignal]
           [REVISION int ]
           [DESIGNABLE bool]
           [SCRIPTABLE bool]
           [STORED bool]
           [USER bool]
           [CONSTANT]
           [FINAL])
```

##### **属性操作**

```C++
//MyObject.h

#include <QObject>

class MyObject : public QObject
{
    Q_OBJECT
    //显示声明属性
    Q_PROPERTY(QString name READ getName WRITE setName RESET resetName NOTIFY nameChanged)
public:
    explicit MyObject(QObject *parent = nullptr);
    Q_INVOKABLE QString getName() const;
    Q_INVOKABLE void setName(const QString &name);
    Q_INVOKABLE void resetName();

signals:
    void nameChanged(const QString &name);
    void func(const QString &name);
private:
    QString m_name;
};
```

```C++
//MyObject.cpp
#include "myobject.h"

MyObject::MyObject(QObject *parent) : QObject(parent)
{

}

QString MyObject::getName() const
{
    return m_name;
}

void MyObject::setName(const QString &name)
{
    if(m_name!=name){
        m_name=name;
        emit nameChanged(name);
    }

}

void MyObject::resetName()
{
    m_name="unsetName";
}

```



```C++
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    MyObject *obj=new MyObject(&w);    
    obj->setName("zhiyin");
    qDebug()<<"m_name="<<obj->getName();//zhiyin
    QObject::connect(obj,&MyObject::nameChanged,[](const QString &name){
        qDebug()<<"从lambda中的信号传递过来的值"<<name;
    });

    obj->setProperty("name","chicken");
    qDebug()<<"m_name="<<obj->getName();//chicken
    qDebug()<<"m_name="<<obj->property("name").toString();//chicken

    obj->setName("hello");
    qDebug()<<"m_name="<<obj->getName();//hello
    qDebug()<<"m_name="<<obj->property("name").toString();//hello

    obj->resetName();
    qDebug()<<"m_name="<<obj->getName();//unsetName
    qDebug()<<"m_name="<<obj->property("name").toString();//unsetName
    return a.exec();
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250813171948012.png" alt="image-20250813171948012" style="zoom: 67%;" />

```C++
    obj->setProperty("name","chicken");
    qDebug()<<"m_name="<<obj->getName();//chicken
    qDebug()<<"m_name="<<obj->property("name").toString();//chicken
```

```c++
Q_PROPERTY(QString name READ getName WRITE setName ...)
```

这相当于告诉 Qt 元对象系统：**“当外部通过 `setProperty("name", ...)` 操作属性时，要调用 `setName` 函数来修改这个属性”** 。

换句话说，`setProperty` 并不是直接修改 `m_name`，而是借助元对象系统，找到 `Q_PROPERTY` 中配置的 `WRITE` 函数（也就是 `setName`），再通过调用 `setName` 来完成赋值。

### 运行时类型信息

#### 1.基本概念

在qt的元对象系统中，运行时类型信息提供了一种在程序运行时动态查询和操作类类型，属性，方法等元数据的能力。

#### 2.两个关键概念

<span style=color:red;background:yellow;font-size:20px>内省</span>是面向对象编程语言的一种特性，它允许在运行时查询对象的信息。Qt中的内省是指在运行时动态获取对象的结构信息（如类名、属性、方法、信号槽等）。这种能力使得能够检查对象的类型，从而实现多态性。在Qt中，可以通过QObject::metaObject() 方法获取对象的元对象，然后利用元对象可以获取到对象的属性、方法和信号等信息。 

```C++
const QMetaObject *QObject::metaObject() const;
```

<span style=color:red;background:yellow;font-size:20px>反射</span>也是面向对象编程语言的一种特性，允许程序在运行时查询和修操作对象的类型、属性、方法等信息。由此可见反射是更高级的自省。通过反射，开发者可以动态地访问和修改对象的状态，而不需要在编译时确定这些信息。

Qt使用了一系列的类来实现反射机制，这些类对对象的各个方面进行了描述，其中QMetaObject类描述了QObject 及其派生类对象的所有元信息，该类是Qt元对象系统的核心类，通过该类的成员函数可以获取 QObject 及其派生类对象的所有元信息，因此可以说QMetaObject类的对象是 Qt 中的元对象。

**注意：要调用QMetaObject 类中的成员函数需要使用QMetaObject类型的对象。**

#### 3.**使用Qt反射机制的条件**

- 需要继承自QObject类或其派生类，并需要在类之中加入Q_OBJECT宏；
- 注册成员函数：若希望普通成员函数能够被反射，需要在函数声明之前加入QObject::Q_INVOKABLE宏；
- 注册成员变量：若希望成员变量能被反射，需要使用Q_PROPERTY宏；
- 注册枚举变量：若希望枚举能被反射，需要使用Q_ENUM或者Q_FLAGS宏。

#### 4.Qt反射机制实现原理

- Q_OBJECT宏展开之后有一个虚拟成员函数meteObject()，该函数会返回一个指向QMetaObject类型的指针，其原型为

```C++
const QMetaObject *QObject::metaObject() const;
```

因为启动了元对象系统的类都包含 Q_OBJECT 宏，所以这些类都有含有 metaObject()虚拟成员函数，通过该函数返回的指针调用QMetaObject 类中的成员函数，便可查询到 QObject 及其派生类对象的各种信息。

#### 5.反射的使用

```C++
    //获取obj的类型名字，属性，方法    
    MyObject myobj;
    //获取元对象指针
    const QMetaObject *pmetaObj=myobj.metaObject();
    //获取元对象类名
    qDebug()<<"obj对象类的名字"<<pmetaObj->className()<<endl;
    
    //通过元对象获取基对象myobj中的属性
    for(int i=0;i<pmetaObj->propertyCount();++i){
        QMetaProperty pro=pmetaObj->property(i);
        qDebug()<<"属性的名字:"<<pro.name()<<"属性的类型:"<<pro.typeName();
    }
    qDebug()<<endl;
    //通过元对象获取基对象myobj中的方法
    for(int i=0;i<pmetaObj->methodCount();++i){
        QMetaMethod mthd=pmetaObj->method(i);
        qDebug()<<"方法的名字:"<<mthd.methodSignature();
    }
```

<img src="C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250813173226594.png" alt="image-20250813173226594" style="zoom:67%;" />