## 2.1
A:w命令首先展示了系统中登录用户数量，以及平均登录时间
并且提供了登录用户的login name，tty name, remote host， lgoin time, idle time, JCPU, PCPU信息
login name，tty name, remote host， lgoin time, idle time来自utmp文件。JCPU, PCPU来自cpu计数器，JCPU表示终端使用所有线程的cpu时间，PCPU表示当前线程使用cpu时间。
## 2.2
A:系统崩溃后，utmp文件里面的内容会消失。
## 2.4
A:
## 2.5
A:使用fflush函数可以将缓冲区数据强制写入硬盘，不用等待系统在合适时机写入
## 2.7
A:一般有四部分比较有用，首先是NAME节主要是概述功能，然后是SYNOPSIS部分介绍命令结构，然后是DESCRIPTION是详细介绍，最后是COMMAND-LINE OPTION对命令的参数进行介绍。
## 2.8
A:
## 2.9
A:如果从文件末尾以后100个字节开始读，目前显示读不到内容，开始写会真的写入，并在中间用'\0'填充，产生空洞文件，逻辑上会占用大小，实际是否占用磁盘空间由系统决定。
