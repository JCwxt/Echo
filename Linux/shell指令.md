# Linux

#### XShell常用快捷键

1. 方向键上下，表示查看指令的历史记录

2. Ctrl + A，表示将光标移动到最左端

3. Ctrl+ E，表示将光标移动到最右端

4. Ctrl + U，表示删除光标前的所有输入

5. Ctrl + K，表示删除光标后的所有输入

6. Ctrl +L，即刻情况当前会话窗口的所有内容，相当于输入指令`clear`

7. **Tab，自动补全命令或文件名等。**

8. 进入某个进程执行界面后：
   1. **Ctrl + C：中断当前进程。**
   
   2. **Ctrl + D：在输入时发送EOF。**

#### Linux内部结构

**内核**：负责硬件调控，内存管理，进程和线程的管理调度，通信，以及非同进程之间如何共享数据（OS的核心）。

**系统调用**：操作系统内核的实现者不希望使用者可以直接干预内核的运行，而定义的一套函数即系统调用函数。使用者可以在外层调用系统调用函数来间接通知逻辑自洽正在运行的内核做某些事情。

**Shell指令：**本质是一些写好了可以直接运行的程序，通过调用命令的方式，调用程序做某些事情。

**库：**某些人或某些组织为了解决Linux中的某些问题而编写的代码，编译成程序包后。使用者通过下载或引用这些程序包，来直接调用这些函数。

![image-20250613140407314](C:\Users\34078\AppData\Roaming\Typora\typora-user-images\image-20250613140407314.png)



#### Shell命令

**关机和重启命令**

关机和重启命令，都需要管理员权限。因此，要么以root用户登录，要么在指令前加上sudo。

```shell
sudo shutdown               #广播关机消息给所有用户，并于一分钟后关机。
sudo shutdown now           #立刻关机
sudo shutdown -r now        #立刻重启
```

**查询和创建sudoer用户**

```shell
grep sudo /etc/group        #查询sudo组的用户，该组用户就是sudoer

sudo adduser test sudo      #将test用户添加为sudoer
sudo whoami     #显示当前正在执行该命令的用户的用户名，如果当前用户是sudoer，会输出root
sudo deluser test sudo      #将test用户移除sudo组
```

**激活root用户**

```shell

sudo passwd root
```

**查看所有用户**

```shell
sudo cat /etc/passwd         #cat指令用于将文件打印出来
```

**查看当前工作目录**

```shell
pwd
```

**cd改变当前工作目录**

```shell
$ cd                # 什么都不输入，切换到用户家目录
$ cd /usr/lib       # 切换到/usr/lib目录
$ cd /              # 切换到 / 目录
$ cd ~              # 切换到用户家目录
$ cd .              # 切换到当前工作目录(不切换)
$ cd ..             # 切换到父目录，上级目录
$ cd -              # 切换到上一次目录
```

**mkdir创建新目录**

```shell
$ mkdir dir                         #在当前工作目录下创建一个新文件夹dir
$ mkdir dir1 dir2 dir3              #在当前工作目录下创建一个新文件夹dir1、dir2以及dir3
$ mkdir -p a/b/c                    #允许创建多级目录a/b/c，即便上级目录不存在
```

**rmidr删除空目录**

```shell
$ rmdir dir                         #删除空目录dir
$ rmdir dir1 dir2 dir3              #删除空目录dir1、dir2以及dir3
$ rmdir -p a/b/c                    #递归的删除目录a/b/c
```

**ls 查看目录/文件的内容信息**

```shell
$ man ls
    ls - list directory contents
格式：
    ls [选项] [FILE]...
    #如果不添加任何选项、目录/文件名的话，默认展示当前工作目录的内容
    #如果输入目录名，会展示该目录下的内容
    #如果输入文件名，会展示该文件的相关信息
    #[FILE]...意味着可以输入多个文件/目录名，展示多个内容，但基本不会这么用

常用选项：
    -a, --all
        #显示所有的内容，包括以.开头的文件和目录，也就是Linux系统下的隐藏文件
    -i, --inode
        #显示文件的inode编号(inode是物理文件系统中文件的唯一标识)。
    -l
        #以长格式的形式显示目录中的内容
    -h, --human-readable
        #一般和-l选项一起使用，以人类可读的方式显示文件的大小。
        #默认以字节展示文件大小, 添加该选型后会自动换算成kb, Mb等
```

**cp复制文件或目录**

```shell
$ man cp
    cp - copy files and directories
    #可以同时复制多个文件/目录
格式：
    cp [选项] SOURCE DEST 
    #将一个目录复制到另一个目录下或者将源文件复制到目的文件中，这里DEST可以是文件也可以是目录
    cp [选项] SOURCE... DEST 
    #将多个文件或者目录复制到目标目录下，此时DEST只能是目录
常用选项：
    -n, --no-clobber
        #若在复制的过程中发现文件已存在，则不会覆盖。不添加该选项，默认会覆盖已存在文件
    -i, --interactive
        #若在复制的过程中发现文件已存在，则会询问用户是否覆盖，选择权力交给用户。
        #输入y/Y表示覆盖，其它任意字符表示不覆盖
    -R, -r, --recursive
        #当SOURCE是一个目录时，添加该选项，用于递归复制目录下所有的内容，即包括所有子目录和文件。
        #复制目录时，应该总是添加上该选项
```

**rm 删除文件和目录**

```shell
$ man rm
    rm - remove files or directories
格式：
    rm [选项] FILE...
    #可以用于删除多个文件或目录
常用选项：
    -f, --force
        #忽略不存在的文件，永远不提示
    -i     
        #在每次删除前，都询问用户是否删除
    -r, -R, --recursive
        #递归删除目录
```

