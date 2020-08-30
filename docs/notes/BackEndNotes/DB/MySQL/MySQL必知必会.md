# MySQL必知必会

## 简介

《MySQL必知必会》的学习笔记和总结。

[书籍链接](https://book.douban.com/subject/3354490/)
[电子书提取码: 待更新](.)

## 了解SQL

### 数据库基础

#### 什么是数据库

> **数据库（database）：保存有组织的数据的容器（通常是一个文
件或一组文件）。**

确切地说，数据库软件应称为DBMS（数据库管理系统）。数据库是通过DBMS创建和操纵的容器。数据库可以是保存在硬设备上的文件，但也可以不是。

#### 表

> **表（table）：某种特定类型数据的结构化清单。**

表名的唯一性取决于多个因素，如数据库名和表名等的结合。这表示，虽然在相同数据库中不能两次使用相同的表名，但在不同的数据库中却可以使用相同的表名。

表具有一些特性，这些特性定义了数据在表中如何存储，描述表的这些特性就是所谓的模式，模式可以用来描述数据库中特定的表以及整个数据库（和其中表的关系）。

> **模式（schema）：关于数据库和表的布局及特性的信息。**

#### 列和数据类型

> **列（column）：表中的一个字段。所有表都是由一个或多个列组成的。**

> **数据类型（datatype）：所容许的数据的类型。每个表列都有相应的数据类型，它限制（或容许）该列中存储的数据。**

#### 行

> **行（row）：表中的一个记录。**

行（row）有时也称为数据库记录（record）。

#### 主键

> **主键（primary key）：一列（或一组列），其值能够唯一区分表中每个行。**

应该尽量应保证他们创建的每个表具有一个主键，以便于以后的数据操纵和管理。

表中的任何列都可以作为主键，只要它满足以下条件：

* 任意两列都不具有相同的主键值；
* 每个列都必须具有一个主键值（主键列不允许NULL值）。

除了以上的条件，使用主键几个比较好的习惯：

* 不更新主键列中的值；
* 不重用主键列的值；
* 不在主键列中使用可能会更改的值。
  
当然还有一种重要的键，即**外键**，后面会介绍到。

### 什么是SQL

SQL是一种专门用来与数据库通信的语言。设计SQL的目的是很好地完成一项任务，即提供一种从数据库中读写数据的简单有效的方法。

SQL有如下的优点：

* SQL不是某个特定数据库供应商专有的语言。几乎所有重要的DBMS都支持SQL，所以，学习此语言使你几乎能与所有数据库打交道。
* SQL简单易学。它的语句全都是由描述性很强的英语单词组成，而且这些单词的数目不多。
* SQL尽管看上去很简单，但它实际上是一种强有力的语言，灵活使用其语言元素，可以进行非常复杂和高级的数据库操作。

值得注意的是，不要认为所有的SQL语法是完全可移植的。

## MySQL简介

### 什么是MySQL

MySQL是一种DBMS（数据库管理系统），即它是一种数据库软件。

### MySQL版本

TODO: 待更新。

## 使用MySQL

### 选择数据库

```sql
# 创建数据库
create database learnDB;
# 使用数据库
use learnDB
```

### 了解数据库和表

```sql
show databases;
```

返回可用数据库的一个列表。包含在这个列表中的可能是MySQL内部使用的数据库。

```sql
show tables;
```

返回当前选择的数据库内可用表的列表。

```sql
show columns from table;
```

要求给出一个表名，它对每个字段返回一行，行中包含字段名、数据类型、是否允许NULL、键信息、默认值以及其他信息。

```sql
describe table;
```

它是`show columns from table;`的一种快捷形式。

**自动增量**：某些表列需要唯一值。在每个行添加到表中时，MySQL可以自动地为每个行分配下一个可用编号，不用在添加一行时手动分配唯一值（这样做必须记住最后一次使用的值）。这个功能就是所谓的自动增量。

**其他`show`语句**：

* `show status;` 用于显示广泛的服务器状态信息。
* `show create database;` 和 `show create table;` 分别用来显示创建特定数据库或表。
* `show grants;` 用来显示授予用户（所有用户或者特定用户）的安全权限。
* `show errors;` 和 `show warnings;` 用来显示服务器错误或警告信息。

## 检索数据

### select语句

为了使用SELECT检索表数据，必须至少给出两条信息——想选择什么，以及从什么地方选择。

### 检索单个列

```sql
select prod_name
from products;
```

从products表中检索一个名为prod_name的列。

### 检索多个列

```sql
select prod_id, prod_name, prod_price 
from products;
```

从products表中检索一个名为prod_id、prod_name、prod_price的列。

### 检索所有列

`select * from products;` 使用通配符有一个大优点。由于不明确指定列名（因为星号检索每个列），所以能检索出名字未知的列。

### 检索不同的行

`select distinct vend_id from products;` 只返回不同（唯一）的vend_id行，如果使用DISTINCT关键字，它必须直接放在列名的前面。

**注意**：不能部分使用DISTINCT。DISTINCT关键字应用于所有列而不仅是前置它的列。如果给出 `SELECT DISTINCT vend_id, prod_price`，除非指定的两个列都不同，否则所有行都将被检索出来。

### 限制结果

`select distinct vend_id, prod_price from products limit 5;` LIMIT 5指示MySQL返回不多于5行。

`select prod_name from products limit 4 offset 3;` 意为从行3开始取4行，等效于 `select prod_name from products limit 3, 4;`

### 使用完全限定的表名

`select products.prod_name from products limit 4 offset 3;`

## 排序检索数据

### 排序数据

其实，检索出的数据并不是以纯粹的随机顺序显示的。如果不明确控制的话，不能（也不应该）依赖该排序顺序。关系数据库设计理论认为，如果不明确规定排序顺序，则不应该假定检索出的数据的顺序有意义。

> **子句（clause）：SQL语句由子句构成，有些子句是必需的，而有的是可选的。一个子句通常由一个关键字和所提供的数据组成。**

`select prod_name from products order by prod_name;` 指示MySQL对prod_name列以字母顺序排序数据。

### 按多个列排序

`select prod_id, prod_price, prod_name from products order by prod_price, prod_name;` 检索3个列，并按其中两个列对结果进行排序——首先按价格，然后再按名称排序。

### 指定排序方向

数据排序默认为升序排序，为了进行降序排序，必须指定DESC关键字。

`select prod_id, prod_price, prod_name from products order by prod_price desc`; 按价格以降序排序产品。

**注意**：DESC关键字只应用到直接位于其前面的列名。如果想在多个列上进行降序排序，必须对每个列指定DESC关键字。

**注意**：在给出ORDER BY子句时，应该保证它位于FROM子句之后。如果使用LIMIT，它必须位于ORDER BY之后。使用子句的次序不对将产生错误消息。

## 过滤数据

### 使用WHERE子句

只检索所需数据需要指定搜索条件（search criteria），搜索条件也称为过滤条件（filter condition）。WHERE子句在表名（FROM子句）之后给出。

`select prod_id, prod_price, prod_name from products where prod_price = 2.50;` 从products表中检索两个列，但不返回所有行，只返回prod_price值为2.50的行，

**注意**：在同时使用ORDER BY和WHERE子句时，应该让ORDER BY位于WHERE之后，否则将会产生错误。

### WHERE子句操作符

MySQL支持的所有条件操作符：

| 操作符 | 解释 |
| :--- | :--- |
| `=` | 等于 |
| `<>` | 不等于 |
| `!=` | 不等于 |
| `<` | 小于 |
| `<=` | 小于等于 |
| `>` | 大于 |
| `>=` | 大于等于 |
| `BETWEEN` | 在指定的两个值之间 |

`select prod_id, prod_price, prod_name from products where prod_price between 5 and 10;` 它检索价格在5美元和10美元之间的所有产品。BETWEEN匹配范围中所有的值，包括指定的开始值和结束值。

### 空值检查

> **NULL 无值（no value）：它与字段包含0、空字符串或仅仅包含空格不同。**

SELECT语句有一个特殊的WHERE子句，可用来检查具有NULL值的列。这个WHERE子句就是IS NULL子句。

`select cust_id from customers where cust_email is null;`

**注意**：在通过过滤选择出不具有特定值的行时，你可能希望返回具有NULL值的行。但是，不行。因为未知具有特殊的含义，数据库不知道它们是否匹配，所以在匹配过滤
或不匹配过滤时不返回它们。因此，**在过滤数据时，一定要验证返回数据中确实给出了被过滤列具有NULL的行。**

## 数据过滤

### 组合WHERE子句

为了进行更强的过滤控制，MySQL允许给出多个WHERE子句。这些子句可以两种方式使用：以AND子句的方式或OR子句的方式使用。

> **操作符（operator）：用来联结或改变WHERE子句中的子句的关键字。也称为逻辑操作符（logical operator）。**

> **AND：用在WHERE子句中的关键字，用来指示检索满足所有给定条件的行。**

`select vend_id, prod_price from products where vend_id = 1003 and prod_price <= 10;` 此SQL语句检索由供应商1003制造且价格小于等于10美元的所有产品的名称和价格。

> **OR：WHERE子句中使用的关键字，用来表示检索匹配任一给定条件的行。**

`select vend_id, prod_price from products where vend_id = 1002 or vend_id = 1003;` 此SQL语句检索由任一个指定供应商制造的所有产品的产品名和价格。

**注意**：任何时候使用具有AND和OR操作符的WHERE子句，都应该使用圆括号明确地分组操作符。不要过分依赖默认计算次序，即使它确实是你想要的东西也是如此。使用圆括号没有什么坏处，它能消除歧义。

### IN操作符

IN操作符用来指定条件范围，范围中的每个条件都可以进行匹配。IN取合法值的由逗号分隔的清单，全都括在圆括号中。

> **IN：WHERE子句中用来指定要匹配值的清单的关键字，功能与OR相当。**

`select prod_name, prod_price from products where vend_id in (1002, 1003) order by prod_name;` 检索供应商1002和1003制造的所有产品。

为什么要使用IN操作符？它有如下优点：

* 在使用长的合法选项清单时，IN操作符的语法更清楚且更直观。
* 在使用IN时，计算的次序更容易管理（因为使用的操作符更少）。
* IN操作符一般比OR操作符清单执行更快。
* IN的最大优点是可以包含其他SELECT语句，使得能够更动态地建
立WHERE子句。

### NOT操作符

WHERE子句中的NOT操作符有且只有一个功能，那就是否定它之后所跟的任何条件。

> **NOT：WHERE子句中用来否定后跟条件的关键字。**

`select prod_name, prod_price from products where vend_id not in (1002, 1003) order by prod_name;` 检索供应商1002和1003之外制造的所有产品。

MySQL支持使用NOT对IN、BETWEEN和EXISTS子句取反，这与多数其他DBMS允许使用NOT对各种条件取反有很大的差别。

## 用通配符进行过滤

### LIKE操作符

> **通配符（wildcard）：用来匹配值的一部分的特殊字符。它本身实际是SQL的WHERE子句中有特殊含义的字符**

> **搜索模式（search pattern）：由字面值、通配符或两者组合构成的搜索条件。**

为在搜索子句中使用通配符，必须使用LIKE操作符。LIKE指示MySQL，后跟的搜索模式利用通配符匹配而不是直接相等匹配进行比较。

操作符何时不是操作符？答案是在它作为谓词（predicate）时。**从技术上说，LIKE是谓词而不是操作符。**

#### 百分号通配符

在搜索串中，%表示任何字符出现任意次数。

`select prod_id, prod_name from products where prod_name like 'jet%';` 将检索任
意以jet起头的prod_name。

**注意**：%代表搜索模式中给定位置的0个、1个或多个字符。

尾空格可能会干扰通配符匹配。解决这个问题的一个简单的办法是在搜索模式最后附加一个%。一个更好的办法是使用函数去掉首尾空格。

虽然似乎%通配符可以匹配任何东西，但有一个**例外**，即NULL。即使是WHERE prod_name LIKE '%'也不能匹配用值NULL作为产品名的行。

#### 下划线通配符

下划线只匹配单个字符而不是多个字符。

`select prod_id, prod_name from products where prod_name like '_ ton anvil';`

### 使用通配符的技巧

通配符搜索的处理一般要比前面讨论的其他搜索所花时间更长。

一些使用通配符要记住的技巧：

* 不要过度使用通配符。如果其他操作符能达到相同的目的，应该使用其他操作符。
* 在确实需要使用通配符时，除非绝对有必要，否则不要把它们用在搜索模式的开始处。把通配符置于搜索模式的开始处，搜索起来是最慢的。
* 仔细注意通配符的位置。如果放错地方，可能不会返回想要的数据。

## 用正则表达式进行搜索

正则表达式是用来匹配文本的特殊的串（字符集合）。所有种类的程序设计语言、文本编辑器、操作系统等都支持正则表达式。

### 使用MySQL正则表达式

MySQL仅支持多数正则表达式实现的一个很小的子集。

#### 基本字符匹配

`select prod_name from products where prod_name regexp '1000' order by prod_name;` 检索列prod_name包含文本1000的所有行。

`select prod_name from products where prod_name regexp '.000' order by prod_name;` `.`是正则表达式语言中一个特殊的字符。它表示匹配任意一个字符，因此，1000和2000等都匹配且返回。

LIKE和REGEXP的一个**重要差别**：

```sql
select prod_name
from products
where prod_name like '1000'
order by prod_name;

select prod_name
from products
where prod_name regexp '1000'
order by prod_name;
```

执行上述两条语句，会发现第一条语句不返回数据，而第二条语句返回一行。为什么？
因为LIKE匹配整个列。如果被匹配的文本在列值中出现，LIKE将不会找到它，相应的行也不被返回（**除非使用通配符**）。而REGEXP在列值内进行匹配，如果被匹配的文本在列值中出现，REGEXP将会找到它，相应的行将被返回。

要让REGEXP用来匹配整个列值（从而起与LIKE相同的作用），使用`^`和`$定位符（anchor）`即可。

MySQL中的正则表达式匹配（自版本3.23.4后）不区分大小写，即大写和小写都匹配）。为区分大小写，可使用`BINARY`关键字。

#### 进行OR匹配

`select prod_name from products where prod_name regexp '1000|2000' order by prod_name;` `|`为正则表达式的OR操作符。它表示匹配其中之一，因此1000和2000都匹配并返回。

使用|从功能上类似于在SELECT语句中使用OR语句，多个OR条件可并入单个正则表达式。

#### 匹配几个字符之一

`select prod_name from products where prod_name regexp '[123] Ton' order by prod_name;` `[123]`定义一组字符，它的意思是匹配1或2或3，因此，1 ton和2 ton都匹配且返回（没有3 ton）。

#### 匹配范围

`select prod_name from products where prod_name regexp '[1-5] Ton' order by prod_name;` `[1-5]`定义了一个范围，这个表达式意思是匹配1到5，因此返回3个匹配行。

#### 匹配特殊字符

为了匹配特殊字符，必须用`\\`为前导。`\\-`表示查找`-`，`\\.`表示查找`.`。

#### 匹配字符类

为更方便工作，可以使用预定义的字符集，称为字符类。

| 字符类 | 说明 |
| :--- | :--- |
| `[:alnum:]` | 任意字母和数字（同`[a-zA-Z0-9]`） |
| `[:alpha:]` | 任意字符（同`[a-zA-Z]`） |
| `[:blank:]` | 空格和制表（同`[\\t]`） |
| `[:cntrl:]` | ASCII控制字符（ASCII 0到31和127） |
| `[:digit:]` | 任意数字（同`[0-9]`） |
| `[:graph:]` | 与`[:print:]`相同，但不包括空格 |
| `[:lower:]` | 任意小写字母（同`[a-z]`） |
| `[:print:]` | 任意可打印字符 |
| `[:punct:]` | 既不在`[:alnum:]`又不在`[:cntrl:]`中的任意字符 |
| `[:space:]` | 包括空格在内的任意空白字符（同`[\\f\\n\\r\\t\\v]`） |
| `[:upper:]` | 任意大写字母（同`[A-Z]`） |
| `[:xdigit:]` | 任意十六进制数字（同`[a-fA-F0-9]`） |

#### 匹配多个实例

匹配多个实例可以用正则表达式重复元字符来完成。

正则表达式重复元字符：

| 元字符 | 说明 |
| :--- | :--- |
| `*` | 0个或多个匹配 |
| `+` | 1个或多个匹配(等价于`{1,}`) |
| `?` | 0个或1个匹配(等价于`{0, 1}`) |
| `{n}` | 指定数目的匹配 |
| `{n,}` | 不少于指定数目的匹配 |
| `{n,m}` | 匹配数目的范围（m不超过255 |

```sql
select prod_name
from products
where prod_name regexp '\\([0-9] sticks?\\)'
order by prod_name;

# 输出
+----------------+
| prod_name      |
+----------------+
| TNT (1 stick)  |
| TNT (5 sticks) |
+----------------+
```

```sql
select prod_name
from products
where prod_name regexp '[[:digit:]]{4}'
order by prod_name;

# 输出：匹配连在一起的任意4位数字。
+--------------+
| prod_name    |
+--------------+
| JetPack 1000 |
| JetPack 2000 |
+--------------+
```

#### 定位符

为了匹配特定位置的文本，需要使用定位符。

| 定位元字符 | 说明 |
| :--- | :--- |
| `^` | 文本的开始 |
| `$` | 文本的结尾 |
| `[[:<:]]` | 词的开始 |
| `[[:>:]]` | 词的结尾 |

```sql
select prod_name
from products
where prod_name regexp '^[0-9\\.]'
order by prod_name;

# 输出
+--------------+
| prod_name    |
+--------------+
| .5 ton anvil |
| 1 ton anvil  |
| 2 ton anvil  |
+--------------+
```

**`^`的双重用途**：

* 在集合中（用`[`和`]`定义），用它来否定该集合。
* 否则，用来指串的开始处。

LIKE和REGEXP的不同在于，**LIKE匹配整个串而REGEXP匹配子串**。利用定位符，**通过用`^`开始每个表达式，用`$`结束每个表达式**，可以使REGEXP的作用与LIKE一样。

## 创建计算字段

在有的情况下，存储在表中的数据都不是应用程序所需要的。我们需要直接从数据库中检索出转换、计算或格式化过的数据；而不是检索出数据，然后再在客户机应用程序或报告程序中重新格式化。

计算字段并不实际存在于数据库表中。计算字段是运行时在SELECT语句内创建的。

> **字段（field）：基本上与列（column）的意思相同，经常互换使用，不过数据库列一般称为列，而术语字段通常用在计算字段的连接上。**

### 拼接字段

> **拼接（concatenate）：将值联结到一起构成单个值。**

在MySQL的SELECT语句中，可使用Concat()函数来拼接两个列。

**注意**：多数DBMS使用+或||来实现拼接，MySQL则使用Concat()函数来实现。当把SQL语句转换成MySQL语句时一定要把这个区别铭记在心。

```sql
select concat(vend_name, '(', vend_country, ')')
from vendors
order by vend_name;

# 输出
+-------------------------------------------+
| concat(vend_name, '(', vend_country, ')') |
+-------------------------------------------+
| ACME(USA)                                 |
| Anvils R Us(USA)                          |
| Furball Inc.(USA)                         |
| Jet Set(England)                          |
| Jouets Et Ours(France)                    |
| LT Supplies(USA)                          |
+-------------------------------------------+
```

别名（alias）是一个字段或值的替换名。别名用AS关键字赋予。

```sql
select concat(vend_name, '(', vend_country, ')') as vend_title
from vendors
order by vend_name;

# 输出
+------------------------+
| vend_title             |
+------------------------+
| ACME(USA)              |
| Anvils R Us(USA)       |
| Furball Inc.(USA)      |
| Jet Set(England)       |
| Jouets Et Ours(France) |
| LT Supplies(USA)       |
+------------------------+
```

### 执行算术计算

计算字段的另一常见用途是对检索出的数据进行算术计算。

```sql
# 检索订单号20005中的所有物品：
select prod_id, quantity, item_price
from orderitems
where order_num = 20005;

# 输出
+---------+----------+------------+
| prod_id | quantity | item_price |
+---------+----------+------------+
| ANV01   |       10 |       5.99 |
| ANV02   |        3 |       9.99 |
| TNT2    |        5 |      10.00 |
| FB      |        1 |      10.00 |
+---------+----------+------------+

# 下汇总物品的价格（单价乘以订购数量）
select prod_id, quantity, item_price, quantity*item_price as expanded_price
from orderitems
where order_num = 20005;

# 输出

+---------+----------+------------+----------------+
| prod_id | quantity | item_price | expanded_price |
+---------+----------+------------+----------------+
| ANV01   |       10 |       5.99 |          59.90 |
| ANV02   |        3 |       9.99 |          29.97 |
| TNT2    |        5 |      10.00 |          50.00 |
| FB      |        1 |      10.00 |          10.00 |
+---------+----------+------------+----------------+
```

## 使用数据处理函数

## 汇总数据

## 分组数据

## 使用子查询

## 连结表

## 创建高级联结

## 组合查询

## 全文本搜索

## 插入数据

## 更新和删除数据

## 创建和操纵表

## 使用视图

## 使用存储过程

## 使用游标

## 使用触发器

## 管理事物处理

## 全球化和本地化

## 安全管理

## 数据库维护

## 改善性能