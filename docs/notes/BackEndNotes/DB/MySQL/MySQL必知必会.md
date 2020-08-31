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

```sql
select *
from products;
```

使用通配符有一个大优点。由于不明确指定列名（因为星号检索每个列），所以能检索出名字未知的列。

### 检索不同的行

```sql
select distinct vend_id
from products;
```

只返回不同（唯一）的vend_id行，如果使用DISTINCT关键字，它必须直接放在列名的前面。

**注意**：不能部分使用DISTINCT。DISTINCT关键字应用于所有列而不仅是前置它的列。如果给出 `SELECT DISTINCT vend_id, prod_price`，除非指定的两个列都不同，否则所有行都将被检索出来。

### 限制结果

```sql
select distinct vend_id, prod_price
from products
limit 5;
```

LIMIT 5指示MySQL返回不多于5行。

```sql
select prod_name
from products
limit 4 offset 3;
```

意为从行3开始取4行，等效于 `select prod_name from products limit 3, 4;`

### 使用完全限定的表名

```sql
select products.prod_name
from products
limit 4 offset 3;
```

## 排序检索数据

### 排序数据

其实，检索出的数据并不是以纯粹的随机顺序显示的。如果不明确控制的话，不能（也不应该）依赖该排序顺序。关系数据库设计理论认为，如果不明确规定排序顺序，则不应该假定检索出的数据的顺序有意义。

> **子句（clause）：SQL语句由子句构成，有些子句是必需的，而有的是可选的。一个子句通常由一个关键字和所提供的数据组成。**

```sql
select prod_name
from products
order by prod_name;
```

指示MySQL对prod_name列以字母顺序排序数据。

### 按多个列排序

```sql
select prod_id, prod_price, prod_name
from products
order by prod_price, prod_name;
```

检索3个列，并按其中两个列对结果进行排序——首先按价格，然后再按名称排序。

### 指定排序方向

数据排序默认为升序排序，为了进行降序排序，必须指定DESC关键字。

```sql
select prod_id, prod_price, prod_name
from products
order by prod_price desc;
```

按价格以降序排序产品。

**注意**：DESC关键字只应用到直接位于其前面的列名。如果想在多个列上进行降序排序，必须对每个列指定DESC关键字。

**注意**：在给出ORDER BY子句时，应该保证它位于FROM子句之后。如果使用LIMIT，它必须位于ORDER BY之后。使用子句的次序不对将产生错误消息。

## 过滤数据

### 使用WHERE子句

只检索所需数据需要指定搜索条件（search criteria），搜索条件也称为过滤条件（filter condition）。WHERE子句在表名（FROM子句）之后给出。

```sql
select prod_id, prod_price, prod_name
from products
where prod_price = 2.50;
```

从products表中检索两个列，但不返回所有行，只返回prod_price值为2.50的行，

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

```sql
select prod_id, prod_price, prod_name
from products
where prod_price between 5 and 10;
```

它检索价格在5美元和10美元之间的所有产品。BETWEEN匹配范围中所有的值，包括指定的开始值和结束值。

### 空值检查

> **NULL 无值（no value）：它与字段包含0、空字符串或仅仅包含空格不同。**

SELECT语句有一个特殊的WHERE子句，可用来检查具有NULL值的列。这个WHERE子句就是IS NULL子句。

```sql
select cust_id
from customers
where cust_email is null;
```

**注意**：在通过过滤选择出不具有特定值的行时，你可能希望返回具有NULL值的行。但是，不行。因为未知具有特殊的含义，数据库不知道它们是否匹配，所以在匹配过滤
或不匹配过滤时不返回它们。因此，**在过滤数据时，一定要验证返回数据中确实给出了被过滤列具有NULL的行。**

## 数据过滤

### 组合WHERE子句

为了进行更强的过滤控制，MySQL允许给出多个WHERE子句。这些子句可以两种方式使用：以AND子句的方式或OR子句的方式使用。

> **操作符（operator）：用来联结或改变WHERE子句中的子句的关键字。也称为逻辑操作符（logical operator）。**

> **AND：用在WHERE子句中的关键字，用来指示检索满足所有给定条件的行。**

```sql
select vend_id, prod_price
from products
where vend_id = 1003 and prod_price <= 10;
```

此SQL语句检索由供应商1003制造且价格小于等于10美元的所有产品的名称和价格。

> **OR：WHERE子句中使用的关键字，用来表示检索匹配任一给定条件的行。**

```sql
select vend_id, prod_price
from products where vend_id = 1002 or vend_id = 1003;
```

此SQL语句检索由任一个指定供应商制造的所有产品的产品名和价格。

**注意**：任何时候使用具有AND和OR操作符的WHERE子句，都应该使用圆括号明确地分组操作符。不要过分依赖默认计算次序，即使它确实是你想要的东西也是如此。使用圆括号没有什么坏处，它能消除歧义。

### IN操作符

IN操作符用来指定条件范围，范围中的每个条件都可以进行匹配。IN取合法值的由逗号分隔的清单，全都括在圆括号中。

> **IN：WHERE子句中用来指定要匹配值的清单的关键字，功能与OR相当。**

```sql
select prod_name, prod_price
from products
where vend_id in (1002, 1003) order by prod_name;
```

检索供应商1002和1003制造的所有产品。

为什么要使用IN操作符？它有如下优点：

* 在使用长的合法选项清单时，IN操作符的语法更清楚且更直观。
* 在使用IN时，计算的次序更容易管理（因为使用的操作符更少）。
* IN操作符一般比OR操作符清单执行更快。
* IN的最大优点是可以包含其他SELECT语句，使得能够更动态地建
立WHERE子句。

### NOT操作符

WHERE子句中的NOT操作符有且只有一个功能，那就是否定它之后所跟的任何条件。

> **NOT：WHERE子句中用来否定后跟条件的关键字。**

```sql
select prod_name, prod_price
from products
where vend_id not in (1002, 1003) order by prod_name;
```

检索供应商1002和1003之外制造的所有产品。

MySQL支持使用NOT对IN、BETWEEN和EXISTS子句取反，这与多数其他DBMS允许使用NOT对各种条件取反有很大的差别。

## 用通配符进行过滤

### LIKE操作符

> **通配符（wildcard）：用来匹配值的一部分的特殊字符。它本身实际是SQL的WHERE子句中有特殊含义的字符**

> **搜索模式（search pattern）：由字面值、通配符或两者组合构成的搜索条件。**

为在搜索子句中使用通配符，必须使用LIKE操作符。LIKE指示MySQL，后跟的搜索模式利用通配符匹配而不是直接相等匹配进行比较。

操作符何时不是操作符？答案是在它作为谓词（predicate）时。**从技术上说，LIKE是谓词而不是操作符。**

#### 百分号通配符

在搜索串中，%表示任何字符出现任意次数。

```sql
select prod_id, prod_name
from products
where prod_name like 'jet%';
```

将检索任意以jet起头的prod_name。

**注意**：%代表搜索模式中给定位置的0个、1个或多个字符。

尾空格可能会干扰通配符匹配。解决这个问题的一个简单的办法是在搜索模式最后附加一个%。一个更好的办法是使用函数去掉首尾空格。

虽然似乎%通配符可以匹配任何东西，但有一个**例外**，即NULL。即使是WHERE prod_name LIKE '%'也不能匹配用值NULL作为产品名的行。

#### 下划线通配符

下划线只匹配单个字符而不是多个字符。

```sql
select prod_id, prod_name
from products
where prod_name like '_ ton anvil';
```

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

```sql
select prod_name
from products
where prod_name regexp '1000' order by prod_name;
```

检索列prod_name包含文本1000的所有行。

```sql
select prod_name
from products
where prod_name regexp '.000' order by prod_name;
```

`.`是正则表达式语言中一个特殊的字符。它表示匹配任意一个字符，因此，1000和2000等都匹配且返回。

LIKE和REGEXP的一个**重要差别**：

```sql
select prod_name
from products
where prod_name like '1000'
order by prod_name;

select prod_name
from products
where prod_name regexp '1000' order by prod_name;
```

执行上述两条语句，会发现第一条语句不返回数据，而第二条语句返回一行。为什么？
因为LIKE匹配整个列。如果被匹配的文本在列值中出现，LIKE将不会找到它，相应的行也不被返回（**除非使用通配符**）。而REGEXP在列值内进行匹配，如果被匹配的文本在列值中出现，REGEXP将会找到它，相应的行将被返回。

要让REGEXP用来匹配整个列值（从而起与LIKE相同的作用），使用`^`和`$定位符（anchor）`即可。

MySQL中的正则表达式匹配（自版本3.23.4后）不区分大小写，即大写和小写都匹配）。为区分大小写，可使用`BINARY`关键字。

#### 进行OR匹配

```sql
select prod_name
from products
where prod_name regexp '1000|2000' order by prod_name;
```

`|`为正则表达式的OR操作符。它表示匹配其中之一，因此1000和2000都匹配并返回。

使用|从功能上类似于在SELECT语句中使用OR语句，多个OR条件可并入单个正则表达式。

#### 匹配几个字符之一

```sql
select prod_name
from products
where prod_name regexp '[123] Ton' order by prod_name;
```

`[123]`定义一组字符，它的意思是匹配1或2或3，因此，1 ton和2 ton都匹配且返回（没有3 ton）。

#### 匹配范围

```sql
select prod_name
from products
where prod_name regexp '[1-5] Ton' order by prod_name;
```

`[1-5]`定义了一个范围，这个表达式意思是匹配1到5，因此返回3个匹配行。

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

### 函数

SQL支持利用函数来处理数据，函数一般是在数据上执行的，它给数据的转换和处理提供了方便。

由于函数的可移植性不是那么强，如果决定使用函数，应该确保做好代码注释，以便以后能确切知道其含义。

### 使用函数

大多数SQL实现支持以下类型的函数：

* 用于处理文本串（如删除或填充值，转换值为大写或小写）的文本函数。
* 用于在数值数据上进行算术操作（如返回绝对值，进行代数运算）的数值函数。
* 用于处理日期和时间值并从这些值中提取特定成分（例如，返回两个日期之差，检查日期有效性等）的日期和时间函数。
* 返回DBMS正使用的特殊信息（如返回用户登录信息，检查版本细节）的系统函数。

#### 文本处理函数

```sql
select vend_name, upper(vend_name) as vend_name_upcase
from vendors
order by vend_name;

# 输出
+----------------+------------------+
| vend_name      | vend_name_upcase |
+----------------+------------------+
| ACME           | ACME             |
| Anvils R Us    | ANVILS R US      |
| Furball Inc.   | FURBALL INC.     |
| Jet Set        | JET SET          |
| Jouets Et Ours | JOUETS ET OURS   |
| LT Supplies    | LT SUPPLIES      |
+----------------+------------------+
```

`Upper()`将文本转换为大写，因此本例子中每个供应商都列出两次，第一次为vendors表中存储的值，第二次作为列vend_name_upcase转换为大写。

常用的文本处理函数：

| 函数 | 解释 |
| :--- | :--- |
| `left()` | 返回串左边的字符 |
| `length()` | 返回串的长度 |
| `locate()` | 找出串的一个子串 |
| `lower()` | 将串转换为小写 |
| `upper()` | 将串转换为大写 |
| `ltrim()` | 去掉串左边的空格 |
| `rtrim()` | 去掉串右边的空格 |
| `soundex()` | 返回串的`soundex`值 |
| `substring()` | 返回子串的字符 |

soundex是一个将任何文本串转换为描述其语音表示的字母数字模式的算法。

```sql
# customers表中有一个顾客Coyote Inc.，其联系名为Y.Lee。
# 但如果这是输入错误，此联系名实际应该是Y.Lie，怎么办？
select cust_name, cust_contact
from customers
where cust_contact = 'Y. Lie';

# 输出：显然，按正确的联系名搜索不会返回数据
```

```sql
# 使用Soundex()函数进行搜索，它匹配所有发音类似于Y.Lie的联系名
select cust_name, cust_contact
from customers
where soundex(cust_contact) = soundex('Y. Lie');

# 输出
+-------------+--------------+
| cust_name   | cust_contact |
+-------------+--------------+
| Coyote Inc. | Y Lee        |
+-------------+--------------+
```

#### 日期和时间处理函数

日期和时间采用相应的数据类型和特殊的格式存储，以便能快速和有效地排序或过滤，并且节省物理存储空间。

常用的日期和时间处理函数：

| 函数 | 解释 |
| :--- | :--- |
| `AddDate()` | 增加一个日期（天、周等） |
| `AddTime()` | 增加一个时间（时、分等） |
| `CurDate()` | 返回当前日期 |
| `CurTime()` | 返回当前时间 |
| `Date()` | 返回日期时间的日期部分 |
| `DateDiff()` | 计算两个日期之差 |
| `Date_Add()` | 高度灵活的日期运算函数 |
| `Date_Format()` | 返回一个格式化的日期或时间串 |
| `Day()` | 返回一个日期的天数部分 |
| `DayOfWeek()` | 对于一个日期，返回对应的星期几 |
| `Hour()` | 返回一个时间的小时部分 |
| `Minute()` | 返回一个时间的分钟部分 |
| `Month()` | 返回一个日期的月份部分 |
| `Now()` | 返回当前日期和时间 |
| `Second()` | 返回一个时间的秒部分 |
| `Time()` | 返回一个日期时间的时间部分 |
| `Year()` | 返回一个日期的年份部分 |

值得注意的是，。无论你什么时候指定一个日期，不管是插入或更新表值还是用WHERE子句进行过滤，日期必须为格式`yyyy-mm-dd`。

```sql
select cust_id, order_num, order_date
from orders
where order_date = '2005-09-01';

# 输出
+---------+-----------+---------------------+
| cust_id | order_num | order_date          |
+---------+-----------+---------------------+
|   10001 |     20005 | 2005-09-01 00:00:00 |
+---------+-----------+---------------------+
```

使用WHERE order_date = '2005-09-01'可靠吗？order_date的数据类型为datetime。这种类型存储日期及时间值。样例表中的值全都具有时间值00:00:00，但实际中很可能并不总是这样。

解决办法是指示MySQL仅将给出的日期与列中的日期部分进行比较，而不是将给出的日期与整个列值进行比较。

```sql
select cust_id, order_num, order_date
from orders
where date(order_date) = '2005-09-01';
```

```sql
# 范围比较
select cust_id, order_num, order_date
from orders
where year(order_date) = 2005 and month(order_date) = 9;

# 输出：2005年9月的所有数据
+---------+-----------+---------------------+
| cust_id | order_num | order_date          |
+---------+-----------+---------------------+
|   10001 |     20005 | 2005-09-01 00:00:00 |
|   10003 |     20006 | 2005-09-12 00:00:00 |
|   10004 |     20007 | 2005-09-30 00:00:00 |
+---------+-----------+---------------------+
```

#### 数值处理函数

数值处理函数仅处理数值数据。这些函数一般主要用于代数、三角或几何运算。

常用的数值处理函数：

| 函数 | 解释 |
| :--- | :--- |
| `Abs()` | 返回一个数的绝对值 |
| `Cos()` | 返回一个角度的余弦 |
| `Exp()` | 返回一个数的指数值 |
| `Mod()` | 返回除操作的余数 |
| `Pi()` | 返回圆周率 |
| `Rand()` | 返回一个随机数 |
| `Sin()` | 返回一个角度的正弦 |
| `Sqrt()` | 返回一个数的平方根 |
| `Tan()` | 返回一个角度的正切 |

## 汇总数据

### 聚集函数

经常需要汇总数据而不用把它们实际检索出来，为此MySQL提供了专门的函数。使用这些函数，MySQL查询可用于检索数据，以便分析和报表生成。

这种类型的检索例子有以下几种：

* 确定表中行数（或者满足某个条件或包含某个特定值的行数）。
* 获得表中行组的和。
* 找出表列（或所有行或某些特定的行）的最大值、最小值和平均
值。

> **聚集函数(aggergate function)：运行在行组上，计算和返回单个值的函数。**

SQL聚集函数：

| 函数 | 解释 |
| :--- | :--- |
| `AVG()` | 返回某列的平均值 |
| `COUNT()` | 返回某列的行数 |
| `MAX()` | 返回某列的最大值 |
| `MIN()` | 返回某列的最小值 |
| `SUM()` | 返回某列值之和 |

#### AVG()函数

AVG()通过对表中行数计数并计算特定列值之和，求得该列的平均值。AVG()可用来返回所有列的平均值，也可以用来返回特定列或行的平均值。

```sql
# 返回products表中所有产品的平均价格
select avg(prod_price) as avg_price
from products;

# 输出
+-----------+
| avg_price |
+-----------+
| 16.133571 |
+-----------+
```

```sql
# 返回products表中1003产品的平均价格
select avg(prod_price) as avg_price
from products
where vend_id = 1003;

# 输出
+-----------+
| avg_price |
+-----------+
| 13.212857 |
+-----------+
```

**注意**：AVG()只能用来确定特定数值列的平均值，而且列名必须作为函数参数给出。为了获得多个列的平均值，必须使用多个AVG()函数。AVG()函数忽略列值为NULL的行。

#### COUNT()函数

COUNT()函数进行计数。可利用COUNT()确定表中行的数目或符合特定条件的行的数目。

COUNT()函数有两种使用方式：

* 使用COUNT(*)对表中行的数目进行计数，不管表列中包含的是空值（NULL）还是非空值。
* 使用COUNT(column)对特定列中具有值的行进行计数，忽略NULL值。

```sql
# 返回customers表中客户的总数
select count(*) as num_cust
from customers;

# 输出
+----------+
| num_cust |
+----------+
|        5 |
+----------+
```

```sql
select count(cust_email) as num_cust
from customers;

# 输出: NULL被忽略
+----------+
| num_cust |
+----------+
|        3 |
+----------+
```

#### MAX()、MIN()函数

MAX()、MIN()分别返回指定列中的最大值和最小值，它们都要求指定列名。

```sql
# 返回products表中最贵的物品的价格
select max(prod_price) as max_price
from products;

# 输出
+-----------+
| max_price |
+-----------+
|     55.00 |
+-----------+
```

```sql
# 返回products表中最便宜的物品的价格
select min(prod_price) as min_price
from products;

# 输出
+-----------+
| min_price |
+-----------+
|      2.50 |
+-----------+
```

#### SUM()函数

SUM()用来返回指定列值的和。

```sql
# 返回所有quantity值之和
select sum(quantity) as items_ordered
from orderitems
where order_num = 20005;

# 输出
+---------------+
| items_ordered |
+---------------+
|            19 |
+---------------+
```

```sql
# 返回所有item_price*quantity值之和
select sum(item_price*quantity) as total_price
from orderitems
where order_num = 20005;

# 输出
+-------------+
| total_price |
+-------------+
|      149.87 |
+-------------+
```

### 聚焦不同值

* 对所有行执行计算，指定ALL参数或者不给参数(因为ALL是默认行为)。
* 只包含不同的值，指定DISTINCT参数。

```sql
select avg(distinct prod_price) as avg_price
from products
where vend_id = 1003;

# 输出
+-----------+
| avg_price |
+-----------+
| 15.998000 |
+-----------+
```

### 组合聚焦函数

但实际上SELECT语句可根据需要包含多个聚集函数。

```sql
select count(*) as num_items, min(prod_price) as price_min, max(prod_price) as price_max, avg(prod_price) as price_avg
from products;

# 输出
+-----------+-----------+-----------+-----------+
| num_items | price_min | price_max | price_avg |
+-----------+-----------+-----------+-----------+
|        14 |      2.50 |     55.00 | 16.133571 |
+-----------+-----------+-----------+-----------+
```

## 分组数据

### 数据分组

分组允许把数据分为多个逻辑组，以便能对每个组进行聚集计算。

### 创建分组

```sql
# 一个例子来理解分组
select vend_id, count(*) as num_prods
from products
group by vend_id;

# 输出
+---------+-----------+
| vend_id | num_prods |
+---------+-----------+
|    1001 |         3 |
|    1002 |         2 |
|    1003 |         7 |
|    1005 |         2 |
+---------+-----------+
```

GROUP BY子句指示MySQL按vend_id排序并分组数据。这导致对每个vend_id而不是整个表计算num_prods一次。

在具体使用GROUP BY子句前，需要知道一些重要的规定：

* GROUP BY子句可以包含任意数目的列。这使得能对分组进行嵌套，为数据分组提供更细致的控制。
* 如果在GROUP BY子句中嵌套了分组，数据将在最后规定的分组上进行汇总。换句话说，在建立分组时，指定的所有列都一起计算（所以不能从个别的列取回数据）。
* GROUP BY子句中列出的每个列都必须是检索列或有效的表达式（但不能是聚集函数）。如果在SELECT中使用表达式，则必须在GROUP BY子句中指定相同的表达式。不能使用别名。
* 除聚集计算语句外，SELECT语句中的每个列都必须在GROUP BY子句中给出。
* 如果分组列中具有NULL值，则NULL将作为一个分组返回。如果列中有多行NULL值，它们将分为一组。
* GROUP BY子句必须出现在WHERE子句之后，ORDER BY子句之前。

使用WITH ROLLUP关键字，可以得到每个分组以及每个分组汇总级别（针对每个分组）的值。

```sql
select vend_id, count(*) as num_prods
from products
group by vend_id with rollup;

# 输出
+---------+-----------+
| vend_id | num_prods |
+---------+-----------+
|    1001 |         3 |
|    1002 |         2 |
|    1003 |         7 |
|    1005 |         2 |
|    NULL |        14 |
+---------+-----------+
```

### 过滤分组

HAVING非常类似于WHERE。事实上，目前为止所学过的所有类型的WHERE子句都可以用HAVING来替代。**唯一的差别是WHERE过滤行，而HAVING过滤分组。**

有关WHERE的所有这些技术和选项都适用于HAVING。它们的句法是相同的，只是关键字有差别。**WHERE在数据分组前进行过滤，HAVING在数据分组后进行过滤。** 这是一个重要的区别，WHERE排除的行不包括在分组中。这可能会改变计算值，从而影响HAVING子句中基于这些值过滤掉的分组。

```sql
# 返回有三个以上的
select vend_id, count(*) as num_prods
from products
group by vend_id
having count(*) >= 3;

# 输出
+---------+-----------+
| vend_id | num_prods |
+---------+-----------+
|    1001 |         3 |
|    1003 |         7 |
+---------+-----------+
```

```sql
# 列出具有2个（含）以上、价格为10（含）以上的产品的供应商
select vend_id, count(*) as num_prods
from products
where prod_price >= 10
group by vend_id
having count(*) >= 2;

# 输出
+---------+-----------+
| vend_id | num_prods |
+---------+-----------+
|    1003 |         4 |
|    1005 |         2 |
+---------+-----------+
```

### 分组和排序

GROUP BY与ORDER BY的差别：

| GROUP BY | ORDER BY |
| :--- | :--- |
| 排序产生的输出 | 分组行。但输出可能不是分组的顺序 |
| 任意列都可以使用（甚至非选择的列也可以使用） | 只可能使用选择列或表达式列，而且必须使用每个选择列表达式 |
| 不一定需要 | 如果与聚集函数一起使用列（或表达式），则必须使用 |

一般在使用GROUP BY子句时，应该也给出ORDER BY子句。这是保证数据正确排序的唯一方法。千万不要仅依赖GROUP BY排序数据。

```sql
# 检索总计订单价格大于等于50的订单的订单号和总计订单价格
select order_num, sum(quantity*item_price) as ordertotal
from orderitems
group by order_num
having sum(quantity*item_price) >= 50;

# 输出
+-----------+------------+
| order_num | ordertotal |
+-----------+------------+
|     20005 |     149.87 |
|     20006 |      55.00 |
|     20007 |    1000.00 |
|     20008 |     125.00 |
+-----------+------------+
```

```sql
# 为按总计订单价格排序输出，需要添加ORDER BY子句
select order_num, sum(quantity*item_price) as ordertotal
from orderitems
group by order_num
having sum(quantity*item_price) >= 50
order by ordertotal;

# 输出
+-----------+------------+
| order_num | ordertotal |
+-----------+------------+
|     20006 |      55.00 |
|     20008 |     125.00 |
|     20005 |     149.87 |
|     20007 |    1000.00 |
+-----------+------------+
```

### SELECT子句顺序

SELECT子句及其顺序：

| 子句 | 解释 | 是否必须使用 |
| :--- | :--- | :--- |
| `SELECT` | :要返回的列或表达式 | 是 |
| `FROM` | :从中检索数据的表 | 仅在从表选择数据时使用 |
| `WHERE` | :行级过滤 | 否 |
| `GROUP BY` | :分组说明 | 仅在按组计算聚集时使用 |
| `HAVING` | :组级过滤 | 否 |
| `ORDER BY` | :输出排序顺序 | 否 |
| `LIMIT` | :要检索的行数 | 否 |

## 使用子查询

### 子查询

> **查询（query）：任何SQL语句都是查询。但此术语一般指SELECT语句。**

SQL还允许创建子查询（subquery），即嵌套在其他查询中的查询。

### 利用子查询进行过滤

假如需要列出订购物品TNT2的所有客户，应该怎样检索？

```sql
# 第一步：检索包含物品TNT2的所有订单的编号。
select order_num
from orderitems
where prod_id = 'TNT2';

# 输出
+-----------+
| order_num |
+-----------+
|     20005 |
|     20007 |
+-----------+
```

```sql
# 第二步：检索具有前一步骤列出的订单编号的所有客户的ID。
select cust_id
from orders
where order_num in (20005, 20007);

# 输出
+---------+
| cust_id |
+---------+
|   10001 |
|   10004 |
+---------+
```

```sql
# 第三步：检索前一步骤返回的所有客户ID的客户信息。
select cust_name, cust_contact
from customers
where cust_id in (10001, 10004);

# 输出
+----------------+--------------+
| cust_name      | cust_contact |
+----------------+--------------+
| Coyote Inc.    | Y Lee        |
| Yosemite Place | Y Sam        |
+----------------+--------------+
```

```sql
# 将上面的三步进行合并
select cust_name, cust_contact
from customers
where cust_id in (select cust_id
                  from orders
                  where order_num in (select order_num
                                      from orderitems
                                      where prod_id = 'TNT2'));

# 输出
+----------------+--------------+
| cust_name      | cust_contact |
+----------------+--------------+
| Coyote Inc.    | Y Lee        |
| Yosemite Place | Y Sam        |
+----------------+--------------+
```

对于能嵌套的子查询的数目没有限制，不过在实际使用时由于性能的限制，不能嵌套太多的子查询。使用子查询并不总是执行这种类型的数据检索的最有效的方法。

### 作为计算字段使用子查询

使用子查询的另一方法是创建计算字段。

```sql
# 如需要显示customers表中每个客户的订单总数。
# 第一步：从customers表中检索客户列表。
# 第二步：对于检索出的每个客户，统计其在orders表中的订单数目。

select cust_name,
       cust_state,
       (select count(*)
        from orders
        where orders.cust_id = customers.cust_id) as orders
from customers
order by cust_name;

# 输出
+----------------+------------+--------+
| cust_name      | cust_state | orders |
+----------------+------------+--------+
| Coyote Inc.    | MI         |      2 |
| E Fudd         | IL         |      1 |
| Mouse House    | OH         |      0 |
| Wascals        | IN         |      1 |
| Yosemite Place | AZ         |      1 |
+----------------+------------+--------+
```

> **相关子查询（correlated subquery）：涉及外部查询的子查询。**

## 联结表

### 联结

SQL最强大的功能之一就是能在数据检索查询的执行中联结（join）表。

#### 关系表

关系表的设计就是要保证把信息分解成多个表，一类数据一个表。各表通过某些常用的值（即关系设计中的关系（relational））互相关联。

> **外键（foreign key）：外键为某个表中的一列，它包含另一个表的主键值，定义了两个表之间的关系。**

关系数据可以有效地存储和方便地处理。因此，关系数据库的可伸缩性远比非关系数据库要好。

> **可伸缩性（scale）：能够适应不断增加的工作量而不失败。设计良好的数据库或应用程序称之为可伸缩性好（scale well）。**

#### 为什么要使用联结

如果数据存储在多个表中，怎样用单条SELECT语句检索出数据？

答案是使用联结。简单地说，联结是一种机制，用来在一条SELECT语句中关联表，因此称之为联结。使用特殊的语法，可以联结多个表返回一组输出，联结在运行时关联表中正确的行。

维护引用完整性，它是通过在表的定义中指定主键和外键来实现的。这个后面会细讲！

### 创建联结

```sql
# 创建联结
select vend_name, prod_name, prod_price
from vendors, products
where vendors.vend_id = products.vend_id
order by vend_name, prod_name;

# 输出
+-------------+----------------+------------+
| vend_name   | prod_name      | prod_price |
+-------------+----------------+------------+
| ACME        | Bird seed      |      10.00 |
| ACME        | Carrots        |       2.50 |
| ACME        | Detonator      |      13.00 |
| ACME        | Safe           |      50.00 |
| ACME        | Sling          |       4.49 |
| ACME        | TNT (1 stick)  |       2.50 |
| ACME        | TNT (5 sticks) |      10.00 |
| Anvils R Us | .5 ton anvil   |       5.99 |
| Anvils R Us | 1 ton anvil    |       9.99 |
| Anvils R Us | 2 ton anvil    |      14.99 |
| Jet Set     | JetPack 1000   |      35.00 |
| Jet Set     | JetPack 2000   |      55.00 |
| LT Supplies | Fuses          |       3.42 |
| LT Supplies | Oil can        |       8.99 |
+-------------+----------------+------------+
```

**注意**：在引用的列可能出现二义性时，必须使用完全限定列名（用一个点分隔的表名和列名）。如果引用一个没有用表名限制的具有二义性的列名，MySQL将返回错误。

#### WHERE子句的重要性

在一条SELECT语句中联结几个表时，相应的关系是在运行中构造的。在数据库表的定义中不存在能指示MySQL如何对表进行联结的东西。你必须自己做这件事情。

没有WHERE子句，第一个表中的每个行将与第二个表中的每个行配对，而不管它们逻辑上是否可以配在一起。

> **笛卡儿积（cartesian product）：由没有联结条件的表关系返回的结果为笛卡儿积。检索出的行的数目将是第一个表中的行数乘以第二个表中的行数。**

**注意**：应该保证所有联结都有WHERE子句，否则MySQL将返回比想要的数据多得多的数据。同理，应该保证WHERE子句的正确性。不正确的过滤条件将导致MySQL返回不正确的数据。

#### 内部联结

目前为止所用的联结称为**等值联结（equijoin）**，它基于两个表之间的相等测试。这种联结也称为**内部联结**。

```sql
# 同WHERE子句联结
select vend_name, prod_name, prod_price
from vendors inner join products on vendors.vend_id = products.vend_id
order by vend_name, prod_name;

# 输出
| vend_name   | prod_name      | prod_price |
+-------------+----------------+------------+
| ACME        | Bird seed      |      10.00 |
| ACME        | Carrots        |       2.50 |
| ACME        | Detonator      |      13.00 |
| ACME        | Safe           |      50.00 |
| ACME        | Sling          |       4.49 |
| ACME        | TNT (1 stick)  |       2.50 |
| ACME        | TNT (5 sticks) |      10.00 |
| Anvils R Us | .5 ton anvil   |       5.99 |
| Anvils R Us | 1 ton anvil    |       9.99 |
| Anvils R Us | 2 ton anvil    |      14.99 |
| Jet Set     | JetPack 1000   |      35.00 |
| Jet Set     | JetPack 2000   |      55.00 |
| LT Supplies | Fuses          |       3.42 |
| LT Supplies | Oil can        |       8.99 |
+-------------+----------------+------------+
```

ANSI SQL规范首选INNER JOIN语法。此外，尽管使用WHERE子句定义联结的确比较简单，但是使用明确的联结语法能够确保不会忘记联结条件，有时候这样做也能影响
性能。

#### 联结多个表

```sql
# 显示编号为20005的订单中的物品
select prod_name, vend_name, prod_price, quantity
from orderitems, products, vendors
where products.vend_id = vendors.vend_id and orderitems.prod_id = products.prod_id and order_num = 20005;

# 输出
+----------------+-------------+------------+----------+
| prod_name      | vend_name   | prod_price | quantity |
+----------------+-------------+------------+----------+
| .5 ton anvil   | Anvils R Us |       5.99 |       10 |
| 1 ton anvil    | Anvils R Us |       9.99 |        3 |
| TNT (5 sticks) | ACME        |      10.00 |        5 |
| Bird seed      | ACME        |      10.00 |        1 |
+----------------+-------------+------------+----------+
```

值得一提的是，MySQL在运行时关联指定的每个表以处理联结。这种处理可能是非常耗费资源的，因此应该仔细，不要联结不必要的表。联结的表越多，性能下降越厉害。

```sql
# 重写子查询例子：返回订购产品TNT2的客户列表
select cust_name, cust_contact
from customers
where cust_id in (select cust_id
                  from orders
                  where order_num in (select order_num
                                      from orderitems
                                      where prod_id = 'TNT2'));

# 等价于
select cust_name, cust_contact
from customers, orders, orderitems
where customers.cust_id = orders.cust_id and orderitems.order_num = orders.order_num and orderitems.prod_id = 'TNT2';

# 输出
+----------------+--------------+
| cust_name      | cust_contact |
+----------------+--------------+
| Coyote Inc.    | Y Lee        |
| Yosemite Place | Y Sam        |
+----------------+--------------+
```

## 创建高级联结

### 使用表别名

别名除了用于列名和计算字段外，SQL还允许给表名起别名。这样做有两个主要理由：

* 缩短SQL语句。
* 允许在单条SELECT语句中多次使用相同的表。

```sql
select cust_name, cust_contact
from customers as c, orders as o, orderitems as oi
where c.cust_id = o.cust_id and oi.order_num = o.order_num and oi.prod_id = 'TNT2';

# 输出
+----------------+--------------+
| cust_name      | cust_contact |
+----------------+--------------+
| Coyote Inc.    | Y Lee        |
| Yosemite Place | Y Sam        |
+----------------+--------------+
```

### 使用不同类型的联结

#### 自联结

```sql
# 求首先找到生产ID为DTNTR的物品的供应商，然后找出这个供应商生产的其他物品
# 方法1：使用子查询
select prod_id, prod_name
from products
where vend_id = (select vend_id
                 from products
                 where prod_id = 'DTNTR');

# 方法2：使用自联结
select p1.prod_id, p1.prod_name
from products as p1, products as p2
where p1.vend_id = p2.vend_id and p2.prod_id = 'DTNTR';

# 输出
+---------+----------------+
| DTNTR   | Detonator      |
| FB      | Bird seed      |
| FC      | Carrots        |
| SAFE    | Safe           |
| SLING   | Sling          |
| TNT1    | TNT (1 stick)  |
| TNT2    | TNT (5 sticks) |
+---------+----------------+
```

自联结通常作为外部语句用来替代从相同表中检索数据时使用的子查询语句。虽然最终的结果是相同的，但有时候处理联结远比处理子查询快得多。

#### 自然联结

自然联结是这样一种联结，其中你只能选择那些唯一的列。这一般是通过对表使用通配符（SELECT *），对所有其他表的列使用明确的子集来完成的。

事实上，迄今为止我们建立的每个内部联结都是自然联结，很可能我们永远都不会用到不是自然联结的内部联结。

#### 外部联结

联结包含了那些在相关表中没有关联行的行。这种类型的联结称为外部联结。

```sql
# 检索所有客户及其订单
select customers.cust_id, orders.order_num
from customers inner join orders on customers.cust_id = orders.cust_id;

# 输出
+---------+-----------+
| cust_id | order_num |
+---------+-----------+
|   10001 |     20005 |
|   10001 |     20009 |
|   10003 |     20006 |
|   10004 |     20007 |
|   10005 |     20008 |
+---------+-----------+

# 为了检索所有客户，包括那些没有订单的客户，使用外部联结
select customers.cust_id, orders.order_num
from customers left outer join orders on customers.cust_id = orders.cust_id;

# 输出
+---------+-----------+
| cust_id | order_num |
+---------+-----------+
|   10001 |     20005 |
|   10001 |     20009 |
|   10002 |      NULL |
|   10003 |     20006 |
|   10004 |     20007 |
|   10005 |     20008 |
+---------+-----------+
```

与内部联结关联两个表中的行不同的是，外部联结还包括没有关联行的行。在使用OUTER JOIN语法时，必须使用RIGHT或LEFT关键字指定包括其所有行的表（RIGHT指出的是OUTER JOIN右边的表，而LEFT指出的是OUTER JOIN左边的表）。

**注意**：MySQL不支持简化字符*=和=*的使用，这两种操作符在其他DBMS中是很流行的。

存在两种基本的外部联结形式：左外部联结和右外部联结。**它们之间的唯一差别是所关联的表的顺序不同**。换句话说，左外部联结可通过颠倒FROM或WHERE子句中表的顺序转换为右外部联结。因此，两种类型的外部联结可互换使用，而究竟使用哪一种纯粹是根据方便而定。

### 使用带聚集函数的联结

```sql
# 要检索所有客户及每个客户所下的订单数
select customers.cust_name,
       customers.cust_id,
       count(orders.order_num) as num_ord
from customers inner join orders on customers.cust_id = orders.cust_id
group by customers.cust_id;

# 输出
+----------------+---------+---------+
| cust_name      | cust_id | num_ord |
+----------------+---------+---------+
| Coyote Inc.    |   10001 |       2 |
| Wascals        |   10003 |       1 |
| Yosemite Place |   10004 |       1 |
| E Fudd         |   10005 |       1 |
+----------------+---------+---------+

# 包含那些没有任何下订单的客户
select customers.cust_name,
       customers.cust_id,
       count(orders.order_num) as num_ord
from customers left outer join orders on customers.cust_id = orders.cust_id
group by customers.cust_id;

# 输出
+----------------+---------+---------+
| cust_name      | cust_id | num_ord |
+----------------+---------+---------+
| Coyote Inc.    |   10001 |       2 |
| Mouse House    |   10002 |       0 |
| Wascals        |   10003 |       1 |
| Yosemite Place |   10004 |       1 |
| E Fudd         |   10005 |       1 |
+----------------+---------+---------+
```

### 使用联结和联结条件

关于联结及其使用的某些要点：

* 注意所使用的联结类型。一般我们使用内部联结，但使用外部联结也是有效的。
* 保证使用正确的联结条件，否则将返回不正确的数据。
* 应该总是提供联结条件，否则会得出笛卡儿积。
* 在一个联结中可以包含多个表，甚至对于每个联结可以采用不同的联结类型。虽然这样做是合法的，一般也很有用，但应该在一起测试它们前，分别测试每个联结。这将使故障排除更为简单。

## 组合查询

多数SQL查询都只包含从一个或多个表中返回数据的单条SELECT语句。MySQL也允许执行多个查询（多条SELECT语句），并将结果作为单个查询结果集返回。这些组合查询通常称为并（union）或复合查询（compound query）。

需要使用组合查询的情况：

* 在单个查询中从不同的表返回类似结构的数据。
* 对单个表执行多个查询，按单个查询返回数据。

任何具有多个WHERE子句的SELECT语句都可以作为一个组合查询给出。

### 创建组合查询

可用UNION操作符来组合数条SQL查询。利用UNION，可给出多条SELECT语句，将它们的结果组合成单个结果集。

#### 使用UNION

```sql
# 检索价格不高于5的所有物品
select vend_id, prod_id, prod_price
from products
where prod_price <= 5;

# 输出
+---------+---------+------------+
| vend_id | prod_id | prod_price |
+---------+---------+------------+
|    1003 | FC      |       2.50 |
|    1002 | FU1     |       3.42 |
|    1003 | SLING   |       4.49 |
|    1003 | TNT1    |       2.50 |
+---------+---------+------------+

# 找出供应商1001和1002生产的所有物品
select vend_id, prod_id, prod_price
from products
where vend_id in (1001, 1002);

# 输出
+---------+---------+------------+
| vend_id | prod_id | prod_price |
+---------+---------+------------+
|    1001 | ANV01   |       5.99 |
|    1001 | ANV02   |       9.99 |
|    1001 | ANV03   |      14.99 |
|    1002 | FU1     |       3.42 |
|    1002 | OL1     |       8.99 |
+---------+---------+------------+

# 组合这两条语句
select vend_id, prod_id, prod_price
from products
where prod_price <= 5
union
select vend_id, prod_id, prod_price
from products
where vend_id in (1001, 1002);

# 输出
+---------+---------+------------+
| vend_id | prod_id | prod_price |
+---------+---------+------------+
|    1003 | FC      |       2.50 |
|    1002 | FU1     |       3.42 |
|    1003 | SLING   |       4.49 |
|    1003 | TNT1    |       2.50 |
|    1001 | ANV01   |       5.99 |
|    1001 | ANV02   |       9.99 |
|    1001 | ANV03   |      14.99 |
|    1002 | OL1     |       8.99 |
+---------+---------+------------+
```

#### UNION规则

使用组合查询则需要注意：

* UNION必须由两条或两条以上的SELECT语句组成，语句之间用关键字UNION分隔（因此，如果组合4条SELECT语句，将要使用3个UNION关键字）。
* UNION中的每个查询必须包含相同的列、表达式或聚集函数（不过各个列不需要以相同的次序列出）。
* 列数据类型必须兼容：类型不必完全相同，但必须是DBMS可以隐含地转换的类型（例如，不同的数值类型或不同的日期类型）。

#### 包含或取消重复的行

UNION从查询结果集中自动去除了重复的行（换句话说，它的行为与单条SELECT语句中使用多个WHERE子句条件一样）。这是UNION的默认行为，但是如果需要，可以改变它。事实上，如果想返回所有匹配行，可使用UNION ALL而不是UNION。

```sql
select vend_id, prod_id, prod_price
from products
where prod_price <= 5
union all
select vend_id, prod_id, prod_price
from products
where vend_id in (1001, 1002);

# 输出
+---------+---------+------------+
| vend_id | prod_id | prod_price |
+---------+---------+------------+
|    1003 | FC      |       2.50 |
|    1002 | FU1     |       3.42 |
|    1003 | SLING   |       4.49 |
|    1003 | TNT1    |       2.50 |
|    1001 | ANV01   |       5.99 |
|    1001 | ANV02   |       9.99 |
|    1001 | ANV03   |      14.99 |
|    1002 | FU1     |       3.42 |
|    1002 | OL1     |       8.99 |
+---------+---------+------------+
```

UNION几乎总是完成与多个WHERE条件相同的工作。UNION ALL为UNION的一种形式，它完成WHERE子句完成不了的工作。如果确实需要每个条件的匹配行全部出现（包括重复行），则必须使用UNION ALL而不是WHERE。

#### 对组合查询结果排序

SELECT语句的输出用ORDER BY子句排序。在用UNION组合查询时，**只能使用一条ORDER BY子句，它必须出现在最后一条SELECT语句之后。**

```sql
select vend_id, prod_id, prod_price
from products
where prod_price <= 5
union all
select vend_id, prod_id, prod_price
from products
where vend_id in (1001, 1002)
order by vend_id, prod_price;

# 输出
+---------+---------+------------+
| vend_id | prod_id | prod_price |
+---------+---------+------------+
|    1001 | ANV01   |       5.99 |
|    1001 | ANV02   |       9.99 |
|    1001 | ANV03   |      14.99 |
|    1002 | FU1     |       3.42 |
|    1002 | FU1     |       3.42 |
|    1002 | OL1     |       8.99 |
|    1003 | TNT1    |       2.50 |
|    1003 | FC      |       2.50 |
|    1003 | SLING   |       4.49 |
+---------+---------+------------+
```

## 全文本搜索

### 理解全文本搜索

MySQL支持几种基本的数据库引擎。但是并非所有的引擎都支持全文本搜索。两个最常使用的引擎为MyISAM和InnoDB，前者支持全文本搜索，而后者不支持。

我们知道利用通配操作符和正则表达式等搜索机制非常有用，但是它们存在几个重要的限制：

* 性能——通配符和正则表达式匹配通常要求MySQL尝试匹配表中所有行（而且这些搜索极少使用表索引）。因此，由于被搜索行数不断增加，这些搜索可能非常耗时。
* 明确控制——使用通配符和正则表达式匹配，很难（而且并不总是能）明确地控制匹配什么和不匹配什么。例如，指定一个词必须匹配，一个词必须不匹配，而一个词仅在第一个词确实匹配的情况下才可以匹配或者才可以不匹配。
* 智能化的结果——虽然基于通配符和正则表达式的搜索提供了非常灵活的搜索，但它们都不能提供一种智能化的选择结果的方法。例如，一个特殊词的搜索将会返回包含该词的所有行，而不区分包含单个匹配的行和包含多个匹配的行（按照可能是更好的匹配来排列它们）。类似，一个特殊词的搜索将不会找出不包含该词但包含其他相关词的行。

所有这些限制以及更多的限制都可以用全文本搜索来解决。在使用全文本搜索时，MySQL不需要分别查看每个行，不需要分别分析和处理每个词。MySQL创建指定列中各词的一个索引，搜索可以针对这些词进行。

### 使用全文本搜索

为了进行全文本搜索，必须索引被搜索的列，而且要随着数据的改变不断地重新索引。

#### 启用全文本搜索支持

一般在创建表时启用全文本搜索。CREATE TABLE语句接受FULLTEXT子句，它给出被索引列的一个逗号分隔的列表。

```sql
create table productnotes
(
    note_id int not null auto_increment,
    prod_id char(10) not null,
    note_date datetime not null,
    note_text text null,
    primary key(note_id),
    fulltext(note_text)
) engine=MyISAM;
```

在定义之后，MySQL自动维护该索引。在增加、更新或删除行时，索引随之自动更新。

**不要在导入数据时使用FULLTEXT**：更新索引要花时间，虽然不是很多，但毕竟要花时间。如果正在导入数据到一个新表，此时不应该启用FULLTEXT索引。应该首先导入所有数据，然后再修改表，定义FULLTEXT。这样有助于更快地导入数据（而且使索引数据的总时间小于在导入每行时分别进行索引所需的总时间）。

#### 进行全文本搜索

在索引之后，使用两个函数Match()和Against()执行全文本搜索，**其中Match()指定被搜索的列，Against()指定要使用的搜索表达式**。

```sql
# 检索单个列note_text
select note_text
from productnotes
where match(note_text) against('rabbit');

# 输出
+-----------------------------------------------------------------------------------------------------------------------+
| note_text                                                                                                             |
+-----------------------------------------------------------------------------------------------------------------------+
| Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                          |
| Quantity varies, sold by the sack load.
All guaranteed to be bright and orange, and suitable for use as rabbit bait. |
+-----------------------------------------------------------------------------------------------------------------------+
```

此SELECT语句检索单个列note_text。由于WHERE子句，一个全文本搜索被执行。Match(note_text)指示MySQL针对指定的列进行搜索，Against('rabbit')指定词rabbit作为搜索文本。由于有两行包含词rabbit，这两个行被返回。

传递给 Match() 的值必须与FULLTEXT()定义中的相同。如果指定多个列，则必须列出它们（而且次序正确）。

除非使用BINARY方式，否则全文本搜索不区分大小写。

#### 使用查询扩展

查询扩展用来设法放宽所返回的全文本搜索结果的范围。

在使用查询扩展时，MySQL对数据和索引进行两遍扫描来完成搜索：

* 首先，进行一个基本的全文本搜索，找出与搜索条件匹配的所有行；
* 其次，MySQL检查这些匹配行并选择所有有用的词。
* 再其次，MySQL再次进行全文本搜索，这次不仅使用原来的条件，而且还使用所有有用的词。

利用查询扩展，能找出可能相关的结果，即使它们并不精确包含所查找的词。

```sql
# 简单的全文本搜索，没有查询扩展
select note_text
from productnotes
where match(note_text) against('anvils');

# 输出
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| note_text                                                                                                                                                |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| Multiple customer returns, anvils failing to drop fast enough or falling backwards on purchaser. Recommend that customer considers using heavier anvils. |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+

# 使用查询扩展
select note_text
from productnotes
where match(note_text) against('anvils' with query expansion);

# 输出
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| note_text                                                                                                                                                |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| Multiple customer returns, anvils failing to drop fast enough or falling backwards on purchaser. Recommend that customer considers using heavier anvils. |
| Customer complaint:
Sticks not individually wrapped, too easy to mistakenly detonate all at once.
Recommend individual wrapping.                       |
| Customer complaint:
Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead. |
| Please note that no returns will be accepted if safe opened using explosives.                                                                            |
| Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                                                             |
| Customer complaint:
Circular hole in safe floor can apparently be easily cut with handsaw.                                                              |
| Matches not included, recommend purchase of matches or detonator (item DTNTR).                                                                           |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
```

第一行包含词anvils，因此等级最高。第二行与anvils无关，但因为它包含第一行中的两个词（customer和recommend），所以也被检索出来。第3行也包含这两个相同的词，但它们在文本中的位置更靠后且分开得更远，因此也包含这一行，但等级为第三。第三行确实也没有涉及anvils（按它们的产品名）。

#### 布尔文本搜索

MySQL支持全文本搜索的另外一种形式，称为布尔方式（boolean mode）。

以布尔方式，可以提供关于如下内容的细节：

* 要匹配的词。
* 要排斥的词（如果某行包含这个词，则不返回该行，即使它包含其他指定的词也是如此）。
* 排列提示（指定某些词比其他词更重要，更重要的词等级更高）。
* 表达式分组。
* 另外一些内容。

**注意**：布尔方式不同于迄今为止使用的全文本搜索语法的地方在于，即使没有定义
FULLTEXT索引，也可以使用它。但这是一种非常缓慢的操作（其性能将随着数据量的增加而降低）。

```sql
select note_text
from productnotes
where match(note_text) against('heavy' in boolean mode);

# 输出+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| note_text                                                                                                                                                |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| Item is extremely heavy. Designed for dropping, not recommended for use with slings, ropes, pulleys, or tightropes.                                      |
| Customer complaint: Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead. |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
```

```sql
# 了匹配包含heavy但不包含任意以rope开始的词的行
select note_text
from productnotes
where match(note_text) against('heavy -rope*' in boolean mode);

# 输出
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| note_text                                                                                                                                                |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
| Customer complaint:Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead. |
+----------------------------------------------------------------------------------------------------------------------------------------------------------+
```

这一次仍然匹配词heavy，但-rope*明确地指示MySQL排除包含rope*（任何以rope开始的词，包括ropes）的行。

两个全文本搜索布尔操作符`-`和`*`，`-`排除一个词，而`*`是截断操作符（可想象为用于词尾的一个通配符）。

全文本布尔操作符：

| 布尔操作符 | 解释 |
| :--- | :--- |
| `+` | 包含，词必须存在 |
| `-` | 排除，词必须不出现 |
| `>` | 包含，而且增加等级值 |
| `<` | 包含，且减少等级值 |
| `()` | 把词组成子表达式（允许这些子表达式作为一个组被包含、
排除、排列等） |
| `~` | 取消一个词的排序值 |
| `*` | 词尾的通配符 |
| `""` | 定义一个短语（与单个词的列表不一样，它匹配整个短语以
便包含或排除这个短语） |

```sql
# 搜索匹配包含词rabbit和bait的行
select note_text
from productnotes
where match(note_text) against('+rabbit +bait' in boolean mode);

# 搜索匹配包含rabbit和bait中的至少一个词的行。
select note_text
from productnotes
where match(note_text) against('rabbit bait' in boolean mode);

# 搜索匹配短语rabbit bait而不是匹配两个词rabbit和bait。
select note_text
from productnotes
where match(note_text) against('"rabbit bait"' in boolean mode);

# 匹配rabbit和carrot，增加前者的等级，降低后者的等级
select note_text
from productnotes
where match(note_text) against('>rabbit <carrot' in boolean mode);

# 搜索匹配词safe和combination，降低后者的等级
select note_text
from productnotes
where match(note_text) against('+safe +(<combination)' in boolean mode);
```

#### 全文本搜索的使用说明

关于全文本搜索的某些重要的说明：

* 在索引全文本数据时，短词被忽略且从索引中排除。短词定义为那些具有3个或3个以下字符的词（如果需要，这个数目可以更改）。
* MySQL带有一个内建的非用词（stopword）列表，这些词在索引全文本数据时总是被忽略。如果需要，可以覆盖这个列表。
* 许多词出现的频率很高，搜索它们没有用处（返回太多的结果）。因此，MySQL规定了一条50%规则，如果一个词出现在50%以上的行中，则将它作为一个非用词忽略。50%规则不用于IN BOOLEAN MODE。
* 如果表中的行数少于3行，则全文本搜索不返回结果（因为每个词或者不出现，或者至少出现在50%的行中）。
* 忽略词中的单引号。例如，don't索引为dont。
* 不具有词分隔符（包括日语和汉语）的语言不能恰当地返回全文本搜索结果。
* 如前所述，仅在MyISAM数据库引擎中支持全文本搜索。

## 插入数据

### 数据插入

顾名思义，INSERT是用来插入（或添加）行到数据库表的。插入可以用几种方式使用：

* 插入完整的行。
* 插入行的一部分。
* 插入多行。
* 插入某些查询的结果。

> **插入及系统安全：可针对每个表或每个用户，利用MySQL的安全机制禁止使用INSERT语句。**

### 插入完整的行

把数据插入表中的最简单的方法是使用基本的INSERT语法，它要求指定表名和被插入到新行中的值。

```sql
insert into customers
value(
    null,
    'parzulpan',
    'Haidian',
    'Beijing',
    'BJ',
    '01000',
    'CN',
    null,
    null
);
```

虽然这种语法很简单，但并不安全，应该尽量避免使用。上面的SQL语句高度依赖于表中列的定义次序，并且还依赖于其次序容易获得的信息。

```sql
# 更安全（不过更烦琐）的方法
insert into customers(
    cust_name,
    cust_address,
    cust_city,
    cust_state,
    cust_zip,
    cust_country,
    cust_contact,
    cust_email
)
value(
    'parzulpanA',
    'Haidian',
    'Beijing',
    'BJ',
    '01000',
    'CN',
    null,
    null
);
```

一般不要使用没有明确给出列的列表的INSERT语句。使用列的列表能使SQL代码继续发挥作用，即使表结构发生了变化。

**注意**：不管使用哪种INSERT语法，都必须给出VALUES的正确数目。如果不提供列名，则必须给每个表列提供一个值。如果提供列名，则必须对每个列出的列给出一个值。如果不这样，将产生一条错误消息，相应的行插入不成功。

如果表的定义允许，则可以在INSERT操作中省略某些列。省略的列必须满足以下某个条件：

* 该列定义为允许NULL值（无值或空值）。
* 在表定义中给出默认值。这表示如果不给出值，将使用默认值。

**提高整体性能**：数据库经常被多个客户访问，对处理什么请求以及用什么次序处理进行管理是MySQL的任务。INSERT操作可能很耗时（特别是有很多索引需要更新时），而且它可能降低等待处理的SELECT语句的性能。如果数据检索是最重要的（通常是这样），则你可以通过在INSERT和INTO之间添加关键字LOW_PRIORITY，指示MySQL
降低INSERT语句的优先级。

```sql
insert low_priority into customers(
    cust_name,
    cust_address,
    cust_city,
    cust_state,
    cust_zip,
    cust_country,
    cust_contact,
    cust_email
)
value(
    'parzulpanB',
    'Haidian',
    'Beijing',
    'BJ',
    '01000',
    'CN',
    null,
    null
);
```

### 插入多个行

可以使用多条INSERT语句，甚至一次提交它们，每条语句用一个分号结束。

```sql
insert into customers(
    cust_name,
    cust_address,
    cust_city,
    cust_state,
    cust_zip,
    cust_country,
    cust_contact,
    cust_email
)
value(
    'parzulpanC',
    'Haidian',
    'Beijing',
    'BJ',
    '01000',
    'CN',
    null,
    null
);
insert into customers(
    cust_name,
    cust_address,
    cust_city,
    cust_state,
    cust_zip,
    cust_country,
    cust_contact,
    cust_email
)
value(
    'parzulpanD',
    'Haidian',
    'Beijing',
    'BJ',
    '01000',
    'CN',
    null,
    null
);
```

实际上，MySQL用单条INSERT语句处理多个插入比使用多条INSERT语句快。

```sql
insert into customers(
    cust_name,
    cust_address,
    cust_city,
    cust_state,
    cust_zip,
    cust_country,
    cust_contact,
    cust_email
)
value(
    'parzulpanE',
    'Haidian',
    'Beijing',
    'BJ',
    '01000',
    'CN',
    null,
    null
),
    (
    'parzulpanF',
    'Haidian',
    'Beijing',
    'BJ',
    '01000',
    'CN',
    null,
    null
);
```

### 插入检索出的数据

可以将一条SELECT语句的结果插入表中。这就是所谓的INSERT SELECT，顾名思义，它是由一条INSERT语句和一条SELECT语句组成的。

```sql
insert into customers(
    cust_id,
    cust_name,
    cust_address,
    cust_city,
    cust_state,
    cust_zip,
    cust_country,
    cust_contact,
    cust_email
)
select cust_id,
       cust_name,
       cust_address,
       cust_city,
       cust_state,
       cust_zip,
       cust_country,
       cust_contact,
       cust_email
from custonew;

# 使用INSERT SELECT从custnew中将所有数据导入customers。
# SELECT语句从custnew检索出要插入的值，而不是列出它们。
```

## 更新和删除数据

### 更新数据

为了更新（修改）表中的数据，可使用UPDATE语句。可采用两种方式使用UPDATE：

* 更新表中特定行。
* 更新表中所有行。

**注意**：在使用UPDATE时一定要注意细心。因为稍不注意，就会更新表中所有行。

基本的UPDATE语句由3部分组成，分别是：

* 要更新的表。
* 列名和它们的新值。
* 确定要更新行的过滤条件。

```sql
# 更新id为10006的电子邮件地址
update customers
set cust_email = 'xx@gmail.com'
where cust_id = 10006;
```

```sql
# 更新多个列
update customers
set cust_email = 'xx@gmail.com',
    cust_name = 'PARZULPAN'
where cust_id = 10006;
```

UPDATE语句中可以使用子查询，使得能用SELECT语句检索出的数据更新列数据。

**注意**：如果用UPDATE语句更新多行，并且在更新这些行中的一行或多行时出一个现错误，则整个UPDATE操作被取消（错误发生前更新的所有行被恢复到它们原来的值）。

为了即使是发生错误，也继续进行更新，可使用IGNORE关键字。

```sql
update ignore customers
set cust_email = 'yy@gmail.com',
    cust_name = 'PARZULPANE',
    cust_state = 'ASAF'
where cust_id = 10006;
```

### 删除数据

为了从一个表中删除（去掉）数据，使用DELETE语句。可以两种方式使用DELETE：

* 从表中删除特定的行。
* 从表中删除所有行。

**注意**：在使用DELETE时一定要注意细心。因为稍不注意，就会错误地删除表中所有行。

```sql
# 删除id为10006的行
delete from customers
where cust_id = 10006;
```

**注意**：如果想从表中删除所有行，不要使用DELETE。可使用**TRUNCATE TABLE**语句，它完成相同的工作，但速度更快（TRUNCATE实际是删除原来的表并重新创建一个表，而不是逐行删除表中的数据）。

### 更新和删除的指导原则

使用UPDATE或DELETE时所遵循的习惯：

* 除非确实打算更新和删除每一行，否则绝对不要使用不带WHERE子句的UPDATE或DELETE语句。
* 保证每个表都有主键，尽可能像WHERE子句那样使用它（可以指定各主键、多个值或值的范围）。
* 在对UPDATE或DELETE语句使用WHERE子句前，应该先用SELECT进行测试，保证它过滤的是正确的记录，以防编写的WHERE子句不正确。
* 使用强制实施引用完整性的数据库，这样MySQL将不允许删除具有与其他表相关联的数据的行。

## 创建和操纵表

### 创建表

MySQL不仅用于表数据操纵，而且还可以用来执行数据库和表的所有操作，包括表本身的创建和处理。

两种创建表的方法：

* 使用具有交互式创建和管理表的工具。
* 表也可以直接用MySQL语句操纵。

## 使用视图

## 使用存储过程

## 使用游标

## 使用触发器

## 管理事物处理

## 全球化和本地化

## 安全管理

## 数据库维护

## 改善性能