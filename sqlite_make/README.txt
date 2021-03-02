# 编译加速
版本：
sqlite-src-3310100的包

原始场景：
tclsh装在mingw上而不是msys上
bld文件夹是在原来电脑拷过来的，../configure是在msys2上的
新电脑是通过右键启动，右键快捷设的是D:\msys64\msys2_shell.cmd -mingw64 -here
所以新电脑上右键的话进入的是mingw，是有tclsh的，而原来bld中的配置却是msys2
但如果新电脑重新建一个文件夹../configure，那么是mingw64的配置将会有诸多问题
所以要把右键改为D:\msys64\msys2_shell.cmd -msys2 -here，这样打开的就是msys2
但是编译的时候会找不懂tclsh，这里我不打算把mingw的环境变量加进来，这样可能会乱掉，因为我已经编过tclsh了，所以可以../configure完把
TCLSH_CMD = tclsh  改成
TCLSH_CMD = /d/tcl8.7a1/bld/tclsh

之前编译testfixture.exe慢的原因是直接从.c文件一步到位生成exe，中间并没有经过.o文件，所以哪怕只改了一行代码也要重新全部编译，所以很慢

现在的整体流程是：
mkdir bld
cd bld
../configure
把这个Makefile和test目录拷贝到bld替换生成的Makefile
注意第一行的TOP路径仍然用原来Makefile的

源码可能也有点小改动，下面括号里是原来写的，仅作参考
（
test_quota.c test_fs.c:
#define SQLITE_OS_WIN 0
#define SQLITE_OS_UNIX 1

函数没定义的，注释掉相关编译选项或直接在代码里屏蔽掉 zipfile.c有错，编译加-lz

SQLITE_ENABLE_DESERIALIZE全都注释掉，无论代码还是Makefile

大概修改方法如上，可能不同机器上有些差异，但思路都差不多，另外如果出现下面这样的错误

'_P_WAIT' undeclared (first use in this function); did you mean '__VALIST'?

   rval = _spawnv (_P_WAIT, lt_argv_zero, (const char * const *) newargz);

把bld文件夹下libtool文件中的build_libtool_libs=yes改为build_libtool_libs=no
这个改动将不会生成动态库，也可以
把libtool的# include <process.h>移到#include <stdio.h>前面
)

接下来先
make -j24 testfixture.exe
不知道为什么一定要经过这一步，否则会报错，可能顺序上有些依赖吧
然后再
make -j24 tcltest.exe
就不会报错了。

研究这个的主要目的是，因为要调试sqlite的testfixture.exe代码，并跑tcl测试脚本，
需要大量重新编译，原先编一次需要1分半，现在只需10多秒

