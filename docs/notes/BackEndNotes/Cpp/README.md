# 简介

这是后端开发系列的 **编程语言C++** 部分，主要包含对《C++ Primer》、《Effective C++》 、《More Effective C++》、《Effective STL》、《深度探索 C++ 对象模型》、《STL 源码剖析》等经典书籍的阅读笔记和习题解答。[点我查看其他部分](https://github.com/parzulpan/BackEndNotes)

## C++ Primer

[书籍链接](https://book.douban.com/subject/25708312/)
[电子书提取码: i44n](https://pan.baidu.com/s/16sImD0ySSVEdYD10RtR5Kg)

### 目录

[查看详细](./C++Primer.md)

* 第〇部分 开始
  * [第一章：开始](./C++Primer/ch01/ch01.md)
* 第I部分 C++基础
  * [第二章：变量和基本类型](./C++Primer/ch02/ch02.md)
  * [第三章：字符串、向量和数组](./C++Primer/ch03/ch03.md)
  * [第四章：表达式](./C++Primer/ch04/ch04.md)
  * [第五章：语句](./C++Primer/ch05/ch05.md)
  * [第六章：函数](./C++Primer/ch06/ch06.md)
  * [第七章：类](./C++Primer/ch07/ch07.md)
* 第II部分 C++标准库
  * [第八章：IO库](./C++Primer/ch08/ch08.md)
  * [第九章：顺序容器](./C++Primer/ch09/ch09.md)
  * [第十章：泛型算法](./C++Primer/ch10/ch10.md)
  * [第十一章：关联容器](./C++Primer/ch11/ch11.md)
  * [第十二章：动态内存](./C++Primer/ch12/ch12.md)
* 第III部分 类设计者的工具
  * [第十三章：拷贝控制](./C++Primer/ch13/ch13.md)
  * [第十四章：重载与类型转换](./C++Primer/ch14/ch14.md)
  * [第十五章：面向对象程序设计](./C++Primer/ch15/ch15.md)
  * [第十六章：模版与泛型编程](./C++Primer/ch16/ch16.md)
* 第IV部分 高级主题
  * [第十七章：标准库与特殊设施](./C++Primer/ch17/ch17.md)
  * [第十八章：用于大型程序的工具](./C++Primer/ch18/ch18.md)
  * [第十九章：特殊工具与技术](./C++Primer/ch19/ch19.md)

## Effective C++

[书籍链接](https://book.douban.com/subject/1842426/)
[电子书提取码: dnb3](https://pan.baidu.com/s/1YjuldGrfkmpc6bNzcFRe-w)

### 目录

[查看详细](./EffectiveC++.md)

* [第一章 让自己习惯C++](./EffectiveC++/ch01/ch01.md)
  * 条款01：视`C++`为一个语言联邦
  * 条款02：尽量以`const，enum，inline`替换`#define`
  * 条款03：尽可能使用`const`
  * 条款04：确定对象被使用前以先被初始化
* [第二章 构造/析构/赋值运算](./EffectiveC++/ch02/ch02.md)
  * 条款05：了解`C++`默默编写并调用哪些函数
  * 条款06：若不想使用编译器自动生成的函数，就该明确拒绝
  * 条款07：为多态基类声明`virtual`析构函数
  * 条款08：别让异常逃离析构函数
  * 条款09：绝不在构造和析构过程中调用`virtual`函数
  * 条款10：在`operator=`返回一个`reference to *this`
  * 条款11：在`operator=`中处理"自我赋值"
  * 条款12：复制对象时勿忘其每一个成分
* [第三章 资源管理](./EffectiveC++/ch03/ch03.md)
  * 条款13：以对象管理资源
  * 条款14：在资源管理类中小心`copying`行为
  * 条款15：在资源管理类中提供对原始资源的访问
  * 条款16：成对使用`new`和`delete`时要采取相同形式
  * 条款17：以独立语句将`newed`对象置入智能指针
* [第四章 设计与声明](./EffectiveC++/ch04/ch04.md)
  * 条款18：让接口容易被正确使用，不易被误用
  * 条款19：设计`class`犹如`type`
  * 条款20：宁以`pass-by-reference-to-const`替换`pass-by-value`
  * 条款21：必须返回对象时，别妄想返回其`reference`
  * 条款22：将成员变量声明为`private`
  * 条款23：宁以`non-member、non-friend`替换`member`函数
  * 条款24：如所有参数皆需类型转换，请为此采用`non-member`函数
  * 条款25：考虑写出一个不抛异常的`swap`函数
* [第五章 实现](./EffectiveC++/ch05/ch05.md)
  * 条款26：尽可能延后变量定义式的出现时间
  * 条款27：尽量少做转型动作
  * 条款28：避免返回handles指向对象内部成分
  * 条款29：为”异常安全“而努力是值得的
  * 条款30：透彻了解inlining的里里外外
  * 条款31：将文件间的编译关系降至最低
* [第六章 继承与面向对象设计](./EffectiveC++/ch06/ch06.md)
  * 条款32：确定你的`public`继承塑模出`is-a`关系
  * 条款33：避免遮掩继承而来的名称
  * 条款34：区分接口继承和实现继承
  * 条款35：考虑`virtual`函数以外的其他选择
  * 条款36：绝不重新定义继承而来的`non-virtual`函数
  * 条款37：绝不重新定义继承而来的缺省参数值
  * 条款38：通过复合塑模出`has-a`或“根据某物实现出”
  * 条款39：明智而审慎地使用`private`继承
  * 条款40：明智而审慎地使用多重继承
* [第七章 模板与泛型编程](./EffectiveC++/ch07/ch07.md)
  * 条款41：了解隐式接口和编译期多态
  * 条款42：了解`typename`的双重意义
  * 条款43：学习处理模板化基类内的名称
  * 条款44：将与参数无关的代码抽离`templates`
  * 条款45：运用成员函数模板接受所有兼容类型
  * 条款46：需要类型转换时请为模板定义非成员函数
  * 条款47：请使用`traits classes`表现类型信息
  * 条款48：认识`template`元编程
* [第八章 定制new和delete](./EffectiveC++/ch08/ch08.md)
  * 条款49：了解`new-hander`的行为
  * 条款50：了解`new`和`delete`的合理替换机制
  * 条款51：编写`new`和`delete`时需固守常规
  * 条款52：写了`placement new`也要写`placement delete`
* [杂项讨论](./EffectiveC++/ch09/ch09.md)
  * 条款53：不要轻忽编译器的警告
  * 条款54：让自己熟悉包括TR1在内的标准程序库
  * 条款55：让自己熟悉Boost

## More Effective C++

[书籍链接](https://book.douban.com/subject/1241385/)
[电子书](.)

## Effective STL

[书籍链接](https://book.douban.com/subject/1792179/)
[电子书](.)

## 深度探索 C++ 对象模型

[书籍链接](https://book.douban.com/subject/1091086/)
[电子书](.)

## STL 源码剖析

[书籍链接](https://book.douban.com/subject/1110934/)
[电子书](.)

## 参考致谢

待更新...
