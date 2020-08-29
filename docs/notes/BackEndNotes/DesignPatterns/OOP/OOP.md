# 面向对象设计原则

设计模式需要遵循基本的软件设计原则。

**可维护性(Maintainability)**和**可复用性(Reusability)** 是衡量软件质量的重要的两个属性：

* 可维护性：软件能够被理解、改正、适应及扩展的难易程度。
* 可复用性：软件能够被复用的难易程度。

**面向对象设计的原则是支持可维护性和可复用性。**

## 单一职责原则

定义：**一个对象应该只包含单一的职责，并且该职责被完全地封装在一个类中**。**就一个类而言，应该仅有一个引起它变化的原因**。

**两个重要概念：**

* **高内聚**：内聚是对软件系统中元素职责相关性和集中度的度量。如果元素具有高度相关的职责，除了这些职责内的任务，没有其他过多的工作，那么该元素就具有高内聚性；反之则称为低内聚性。
* **低耦合**：耦合是软件结构中各模块之间相互连接的度量。耦合强弱取决于模块间接口的复杂程度、进入或访问一个模块的点以及通过接口的数据。

单一职责原则用于控制类的力度大小。如果一个类承担的职责越多，则它被复用的可能性就越小，且各个职责耦合在一起。所以，应该将这些职责分离，不同的职责封装在不同的类中。

## 开闭原则

定义：**软件实体应该对扩展开发，对修改关闭**。

通俗地讲，**就是指软件实体应该在不修改原有代码的基础上进行扩展**。它的关键在于**抽象化**，可以为系统定义一个相对较为稳定的抽象层，将不同的实现行为放到具体的实现层中完成。

## 里氏替换原则

定义：**所有引用基类的地方必须能透明地使用其子类的对象**。

在编码开发中，如果用子类对象来替换基类对象，显然程序将不会产生任何异常和问题，反过来则不成立。

要求我们尽可能地使用基类类型来对对象进行定义，而在运行时再确定子类类型，然后用子类对象替换父类对象。

* 设计时应将父类设计为抽象类或者接口，子类集成父类并实现在父类中声明的方法。
* 运行时子类实例(对象)替换父类实例(对象)，这样就能很方便地扩展系统功能。

## 依赖倒转原则

定义：**高层模块不应该依赖底层模块，它们都应该依赖抽象。且抽象不应该依赖于细节，细节应该依赖于抽象**。

什么是高层，什么是低层呢？它们指的是继承（派生）中的基类子类关系，**基类或者越抽象的类，层次越高**。通俗地讲，**依赖倒转原则要求针对接口编程，不要针对实现编程**。它的关键也在于**抽象化**。

## 接口隔离原则

定义：**客户端不应该依赖那些它不需要的接口**。

每个接口仅需要承担一个相对独立的角色或功能，使用该接口的客户端仅需要知道与之相关的方法即可。一般而言，在接口中仅包含为某一类用户定制的方法即可。

## 合成复用原则

定义：**优先使用对象组合，而不是通过集成来达到复用的目的**。

在编码开发中，优先使用关联、聚合和组合关系，尽量少用泛化(继承)。

* **黑箱复用**：对象组合可以使系统更加灵活，降低类与类之间的耦合度，一个类的变化尽坑你不影响其他类。
* **白箱复用**：继承关系会破坏系统的封装性，会将基类的实现细节暴露给子类，如果基类发生改变，那么子类的实现也不得不改变。如果非要使用继承，则需要考虑里氏替换原则和依赖倒转原则。

## 迪米特法则

定义：**每一个软件单位对其他单位都只有最少的知识，而且局限于那些与本单位密切相关的软件单位**。

它要求一个软件实体应当尽可能少地与其他实体发生相互作用。在类的设计上应该注意以下几点：**在类的划分上应尽量创建松耦合的类，类之间的耦合度越低，越有利于复用**；**类的结构设计上，每一个类都应该降低其成员变量和成员函数的访问权限**。

## 实例

在编写 OOP 代码时，如果遵循这些设计原则，就更可能写出可扩展、易于修改的代码。相反，如果不断违反其中的一条或多条原则，那么很快你的代码就会变得不可扩展、难以维护。

### `Single responsibility principle` 单一职责原则

这个原则认为，**一个类应该仅仅只有一个被修改的理由。** 换句话说，每个类都应该只有一种职责。

#### 具体例子

一个需求：编写一个脚本，自动抓取 Hacker News(HN) 首页 Top5 的新闻标题与链接，并用纯文本的方式写入到文件，方便自己用其他工具阅读。

```python
import io
import sys
from typing import Generator

import requests
from lxml import etree


class Post:
    """HN(https://news.ycombinator.com/) 上的条目

    :param title: 标题
    :param link: 链接
    :param points: 当前得分
    :param comments_cnt: 评论数
    """
    def __init__(self, title: str, link: str, points: str, comments_cnt: str):
        self.title = title
        self.link = link
        self.points = int(points)
        self.comments_cnt = int(comments_cnt)


class HNTopPostsSpider:
    """抓取 HackerNews Top 内容条目

    :param fp: 存储抓取结果的目标文件对象
    :param limit: 限制条目数，默认为 5
    """
    ITEMS_URL = 'https://news.ycombinator.com/'
    FILE_TITLE = 'Top news on HN'

    def __init__(self, fp: io.TextIOBase, limit: int = 5):
        self.fp = fp
        self.limit = limit

    def fetch(self) -> Generator[Post, None, None]:
        """从 HN 抓取 Top 内容
        """
        resp = requests.get(self.ITEMS_URL)

        # 使用 XPath 可以方便的从页面解析出你需要的内容，以下均为页面解析代码
        # 如果你对 xpath 不熟悉，可以忽略这些代码，直接跳到 yield Post() 部分
        html = etree.HTML(resp.text)
        items = html.xpath('//table[@class="itemlist"]/tr[@class="athing"]')
        for item in items[:self.limit]:
            node_title = item.xpath('./td[@class="title"]/a')[0]
            node_detail = item.getnext()
            points_text = node_detail.xpath('.//span[@class="score"]/text()')
            comments_text = node_detail.xpath('.//td/a[last()]/text()')[0]

            yield Post(
                title=node_title.text,
                link=node_title.get('href'),
                # 条目可能会没有评分
                points=points_text[0].split()[0] if points_text else '0',
                comments_cnt=comments_text.split()[0]
            )

    def write_to_file(self):
        """以纯文本格式将 Top 内容写入文件
        """
        self.fp.write(f'# {self.FILE_TITLE}\n\n')
        # enumerate 接收第二个参数，表示从这个数开始计数（默认为 0）
        for i, post in enumerate(self.fetch(), 1):
            self.fp.write(f'> TOP {i}: {post.title}\n')
            self.fp.write(f'> 分数：{post.points} 评论数：{post.comments_cnt}\n')
            self.fp.write(f'> 地址：{post.link}\n')
            self.fp.write('------\n')


def main():

    # with open('/tmp/hn_top5.txt') as fp:
    #     crawler = HNTopPostsSpider(fp)
    #     crawler.write_to_file()

    # 因为 HNTopPostsSpider 接收任何 file-like 的对象，所以我们可以把 sys.stdout 传进去
    # 实现往控制台标准输出打印的功能
    crawler = HNTopPostsSpider(sys.stdout)
    crawler.write_to_file()


if __name__ == '__main__':
    main()
```

分析可知，上面的解决方案中，定义了两个类：

* Post：表示单个 HN 内容条目，其中定义了标题、链接等字段，是用来衔接“抓取”和“写入文件”两件事情的数据类
* HNTopPostsSpider：抓取 HN 内容的爬虫类，其中定义了抓取页面、解析、写入结果的方法，是完成主要工作的类

但是从设计的角度来看，HNTopPostsSpider 这个类违反了单一职责原则。至少存在两个不同的修改它的理由：

* HN 网站的程序员突然更新了页面样式，旧的 xpath 解析算法从新页面上解析不到内容，需要修改 fetch 方法内的解析逻辑。
* 用户突然觉得纯文本格式的输出不好看，想要改成 Markdown 样式。需要修改 write_to_file 方法内的输出逻辑。

根本原因在于，**HNTopPostsSpider 类承担着 “抓取帖子列表” 和 "将帖子列表写入文件" 这两种完全不同的职责**。

#### 违反单一职责原则的坏处

**坏处**：

* 意味着经常会因为不同的原因去修改它，这可能会导致不同功能之间相互影响
* 单个类承担的职责越多，意味着这个类的复杂度也就越高，它的维护成本也同样会水涨船高
* 且这样的类同样也难以被复用

**解决方法**：

* 拆分大类为更多小类
* 使用函数

#### 拆分大类为更多小类

为了让 HNTopPostsSpider 类的职责更纯粹，我们可以把其中与“写入文件”相关的内容拆分出去作为一个新的类：

```python
class PostsWriter:
    """负责将帖子列表写入到文件
    """
    def __init__(self, fp: io.TextIOBase, title: str):
        self.fp = fp
        self.title = title

    def write(self, posts: List[Post]):
        self.fp.write(f'# {self.title}\n\n')
        # enumerate 接收第二个参数，表示从这个数开始计数（默认为 0）
        for i, post in enumerate(posts, 1):
            self.fp.write(f'> TOP {i}: {post.title}\n')
            self.fp.write(f'> 分数：{post.points} 评论数：{post.comments_cnt}\n')
            self.fp.write(f'> 地址：{post.link}\n')
            self.fp.write('------\n')
```

而在 HNTopPostsSpider 类里，可以通过调用 PostsWriter 的方式来完成之前的工作：

```python
class HNTopPostsSpider:
    FILE_TITLE = 'Top news on HN'
    # <... 已省略 ...>

    def write_to_file(self, fp: io.TextIOBase):
        """以纯文本格式将 Top 内容写入文件

        实例化参数文件对象 fp 被挪到了 write_to_file 方法中
        """
        # 将文件写入逻辑托管给 PostsWriter 类处理
        writer = PostsWriter(fp, title=self.FILE_TITLE)
        writer.write(list(self.fetch()))
```

通过这种方式，我们让 HNTopPostsSpider 和 PostsWriter 类都各自满足了“单一职责原则”。我只会因为解析逻辑变动才去修改 HNTopPostsSpider 类，同样，修改 PostsWriter 类的原因也只有调整输出格式一种。这两个类各自的修改可以单独进行而不会相互影响。

#### 使用函数

以把“写入文件”的逻辑拆分为一个新的函数，由它来专门承担起将帖子列表写入文件的职责：

```python
def write_posts_to_file(posts: List[Post], fp: io.TextIOBase, title: str):
    """负责将帖子列表写入文件
    """
    fp.write(f'# {title}\n\n')
    for i, post in enumerate(posts, 1):
        fp.write(f'> TOP {i}: {post.title}\n')
        fp.write(f'> 分数：{post.points} 评论数：{post.comments_cnt}\n')
        fp.write(f'> 地址：{post.link}\n')
        fp.write('------\n')
```

而对于 HNTopPostsSpider 类来说，改动可以更进一步。这次我们可以直接删除其中和文件写入相关的所有代码。让它只负责一件事情：“获取帖子列表”。

```python
lass HNTopPostsSpider:
    """抓取 HackerNews Top 内容条目

    :param limit: 限制条目数，默认为 5
    """
    ITEMS_URL = 'https://news.ycombinator.com/'

    def __init__(self, limit: int = 5):
        self.limit = limit

    def fetch(self) -> Generator[Post, None, None]:
        # <... 已省略 ...>
```

相应的，类和函数的调用方 main 函数就需要稍作调整，它需要负责把 write_posts_to_file 函数和 HNTopPostsSpider 类之间协调起来，共同完成工作：

```python
def main():
    crawler = HNTopPostsSpider()

    posts = list(crawler.fetch())
    file_title = 'Top news on HN'
    write_posts_to_file(posts, sys.stdout, file_title)
```

### `Open–closed principle` 开放-关闭原则

这个原则认为，**类应该对扩展开放，对修改封闭。** 换句话说，你应该可以在不修改某个类的前提下，扩展它的行为。

一个非常恰当的例子，**Python 里的内置排序函数 sorted**

如果我们想对某个列表排序，可以直接调用 sorted 函数：

```python
>>> l = [5, 3, 2, 4, 1]
>>> sorted(l)
[1, 2, 3, 4, 5]
```

假如我们想改变 sorted 函数的排序逻辑。比如，让它使用所有元素对 3 取余后的结果来排序。我们是不是需要去修改 sorted 函数的源码？当然不用，只需要在调用 sort 函数时，传入自定义的排序函数 key 参数就行了：

```python
>>> l = [8, 1, 9]
# 按照元素对 3 的余数排序，能被 3 整除的 9 排在了最前面，随后是 1 和 8
>>> sorted(l, key=lambda i: i % 3)
[9, 1, 8]
```

sorted函数满足这个原则：

* 对扩展开放：可以通过传入自定义key函数来扩展它的行为
* 对修改关闭：无需修改sorted函数本身

还是回到之前那个具体例子，在使用了一段时间之后，用户觉得每次抓取到的内容有点不合口味。其实只关注那些来自特定网站，比如 github 上的内容。所以需要修改 HNTopPostsSpider 类的代码来对结果进行过滤：

```python
class HNTopPostsSpider:
    # <... 已省略 ...>

    def fetch(self) -> Generator[Post, None, None]:
        # <... 已省略 ...>
        counter = 0
        for item in items:
            if counter >= self.limit:
                break

            # <... 已省略 ...>
            link = node_title.get('href')

            # 只关注来自 github.com 的内容
            if 'github' in link.lower():
                counter += 1
                yield Post(... ...)
```

这样写的话，如果现在还想过滤其他关键字，那么必须又要修改现有的 HNTopPostsSpider 类代码，并且调整 if 判断语句。那么此时，它就违反了开放-关闭原则。

**解决方法**：

* 使用类继承来改造代码
* 使用组合与依赖注入来改造代码
* 使用数据驱动思想来改造代码

#### 使用类继承来改造代码

使用继承的方式来让类遵守“开放-关闭原则”的关键点在于：**找到父类中会变动的部分，将其抽象成新的方法（或属性），最终允许新的子类来重写它以改变类的行为**。

对于 HNTopPostsSpider 类来说。首先，我们需要找到其中会变动的那部分逻辑，也就是**判断是否对条目感兴趣**，然后将其抽象出来，定义为新的方法：

```python
class HNTopPostsSpider:
    # <... 已省略 ...>

    def fetch(self) -> Generator[Post, None, None]:
        # <... 已省略 ...>
        for item in items:
            # <... 已省略 ...>
            post = Post( ... ... )
            # 使用测试方法来判断是否返回该帖子
            if self.interested_in_post(post):
                counter += 1
                yield post

    def interested_in_post(self, post: Post) -> bool:
        """判断是否应该将帖子加入结果中
        """
        return True
```

只关心来自 GitHub 的帖子：

```python
class GithubOnlyHNTopPostsSpider(HNTopPostsSpider):
    """只关心来自 GitHub 的帖子
    """
    def interested_in_post(self, post: Post) -> bool:
        return 'github' in post.link.lower()

def main():
    # crawler = HNTopPostsSpider()
    # 使用新的子类
    crawler = GithubOnlyHNTopPostsSpider()
    <... ...>
```

只关心来自 GitHub/BloomBerg 的帖子：

```python
class GithubNBloomBergHNTopPostsSpider(HNTopPostsSpider):
    """只关心来自 GitHub/BloomBerg 的帖子
    """
    def interested_in_post(self, post: Post) -> bool:
        if 'github' in post.link.lower() \
                or 'bloomberg' in post.link.lower():
            return True
        return False
```

#### 使用组合与依赖注入来改造代码

与继承不同，依赖注入允许我们在类实例化时，通过参数将业务逻辑的变化点：**帖子过滤算法** 注入到类实例中。最终同样实现“开放-关闭原则”。

定义一个名为 PostFilter 的抽象类：

```python
from abc import ABC, abstractmethod

class PostFilter(metaclass=ABCMeta):
    """抽象类：定义如何过滤帖子结果
    """
    @abstractmethod
    def validate(self, post: Post) -> bool:
        """判断帖子是否应该被保留"""
```

定义一个继承于该抽象类的默认 DefaultPostFilter 类，过滤逻辑为保留所有结果。之后再调整一下 HNTopPostsSpider 类的构造方法，让它接收一个名为 post_filter 的结果过滤器：

```python
class DefaultPostFilter(PostFilter):
    """保留所有帖子
    """
    def validate(self, post: Post) -> bool:
        return True


class HNTopPostsSpider:
    """抓取 HackerNews Top 内容条目

    :param limit: 限制条目数，默认为 5
    :param post_filter: 过滤结果条目的算法，默认为保留所有
    """
    ITEMS_URL = 'https://news.ycombinator.com/'

    def __init__(self, limit: int = 5, post_filter: Optional[PostFilter] = None):
        self.limit = limit
        self.post_filter = post_filter or DefaultPostFilter()

    def fetch(self) -> Generator[Post, None, None]:
        # <... 已省略 ...>
        for item in items:
            # <... 已省略 ...>
            post = Post( ... ... )
            # 使用测试方法来判断是否返回该帖子
            if self.post_filter.validate(post):
                counter += 1
                yield post
```

默认情况下，HNTopPostsSpider.fetch 会保留所有的结果。假如我们想要定义自己的过滤算法，只要新建自己的 PostFilter 类即可，下面是两个分别过滤 GitHub 与 BloomBerg 的 PostFilter 类：

```python
class GithubPostFilter(PostFilter):
    def validate(self, post: Post) -> bool:
        return 'github' in post.link.lower()


class GithubNBloomPostFilter(PostFilter):
    def validate(self, post: Post) -> bool:
        if 'github' in post.link.lower() or 'bloomberg' in post.link.lower():
            return True
        return False
```

最后使用：

```python
def main():
    # crawler = HNTopPostsSpider()
    # crawler = HNTopPostsSpider(post_filter=GithubPostFilter())
    crawler = HNTopPostsSpider(post_filter=GithubNBloomPostFilter())

    posts = list(crawler.fetch())
    file_title = 'Top news on HN'
    write_posts_to_file(posts, sys.stdout, file_title)
```

#### 使用数据驱动思想来改造代码

这个方式的核心思想在于：**将经常变动的东西，完全以数据的方式抽离出来。当需求变动时，只改动数据，代码逻辑保持不动**。它的原理与“依赖注入”有一些相似，同样是把变化的东西抽离到类外部。不同的是，后者抽离的通常是类，而前者抽离的是数据。

为了让 HNTopPostsSpider 类的行为可以被数据驱动，需要使其接收 filter_by_link_keywords 参数：

```python
class HNTopPostsSpider:
    """抓取 HackerNews Top 内容条目

    :param limit: 限制条目数，默认为 5
    :param filter_by_link_keywords: 过滤结果的关键词列表，默认为 None 不过滤
    """
    ITEMS_URL = 'https://news.ycombinator.com/'

    def __init__(self,
                 limit: int = 5,
                 filter_by_link_keywords: Optional[List[str]] = None):
        self.limit = limit
        self.filter_by_link_keywords = filter_by_link_keywords

    def fetch(self) -> Generator[Post, None, None]:
        # <... 已省略 ...>
        for item in items:
            # <... 已省略 ...>
            post = Post( ... ... )
            if self.filter_by_link_keywords is None:
                counter += 1
                yield post
            # 当 link 中出现任意一个关键词时，返回结果
            elif any(keyword in post.link for keyword in self.filter_by_link_keywords):
                counter += 1
                yield post
```

在 main 函数中定义 link_keywords 变量并将其传入到 HNTopPostsSpider 类的构造方法中：

```python
def main():
    # link_keywords = None
    link_keywords = [
        'github.com',
        'bloomberg.com'
    ]
    crawler = HNTopPostsSpider(filter_by_link_keywords=link_keywords)

    posts = list(crawler.fetch())
    file_title = 'Top news on HN'
    write_posts_to_file(posts, sys.stdout, file_title)
```

### `Liskov Substitution Principle` 里氏替换原则与继承

L原则大概的意思是，**当你使用继承时，子类（派生类）对象应该可以在程序中替代父类（基类）对象使用，而不破坏程序原本的功能**。

#### 具体例子

为一个 Web 站点设计用户模型。这个站点的用户分为两类：普通用户和站点管理员。

```python
class User(Model):
    """普通用户模型类
    """
    def __init__(self, username: str):
        self.username = username

    def deactivate(self):
        """停用当前用户
        """
        self.is_active = True
        self.save()

class Admin(User):
    """管理员用户类
    """
    def deactivate(self):
        # 管理员用户不允许被停用
        raise RuntimeError('admin can not be deactivated!')
```

#### 不当继承关系会违反 L 原则

显然，具体例子的写法是违反L原则的。具体如下：

假设我们需要写一个新函数，它可以同时接受多个用户对象作为参数，批量将它们停用。

```python
def deactivate_users(users: Iterable[User]):
    """批量停用多个用户
    """
    for user in users:
        user.deactivate()
```

因为 deactivate_users 函数在参数注解里写到，它接受一切 可被迭代的 User 对象，那么管理员 Admin 是不是 User 对象？当然是，因为它是继承自 User 类的子类。 但是传入参数：
> [User("foo"), Admin("bar_admin")]

会发现立马抛出异常。在 deactivate_users 函数看来，子类 Admin 无法随意替换父类 User 使用，所以现在的代码是不符合 L 原则的。

#### 错误的解决办法

要修复上面的函数，最直接的办法就是在函数内部增加一个额外的类型判断：

```python
def deactivate_users(users: Iterable[User]):
    """批量停用多个用户
    """
    for user in users:
        # 管理员用户不支持 deactivate 方法，跳过
        if isinstance(user, Admin):
            logger.info(f'skip deactivating admin user {user.username}')
            continue

        user.deactivate()
```

但是，这样修改的缺点是显而易见的。因为虽然到目前为止，只有 Admin 类型的用户不允许被停用。但是，谁能保证未来不会出现其他不能被停用的用户类型呢？如果不断增加需求，那就需要重复的修改，那么就违反了**开放-关闭原则**。

#### 正确的解决办法

子类不能只是简单通过抛出异常的方式对某个类方法进行“退化”。如果 “对象不能支持某种操作” 本身就是这个类型的**核心特征**之一，那我们在进行父类设计时，**就应该把这个核心特征设计进去**。

```python
class User(Model):
    """普通用户模型类
    """
    def __init__(self, username: str):
        self.username = username

    def allow_deactivate(self) -> bool:
        """是否允许被停用
        """
        return True

    def deactivate(self):
        """将当前用户停用
        """
        self.is_active = True
        self.save()

class Admin(User):
    """管理员用户类
    """
    def allow_deactivate(self) -> bool:
        # 管理员用户不允许被停用
        return False

def deactivate_users(users: Iterable[User]):
    """批量停用多个用户
    """
    for user in users:
        if not user.allow_deactivate():
            logger.info(f'user {user.username} does not allow deactivating, skip.')
            continue

        user.deactivate()
```

#### 子类修改方法返回值会违反 L 原则

给用户类增加了一个新方法：list_related_posts，调用它可以拿到所有和当前用户有关的帖子 ID。对于普通用户，方法返回的是自己发布过的所有帖子，而管理员则是站点里的所有帖子。

```python
class User(Model):
    """普通用户模型类
    """
    def __init__(self, username: str):
        self.username = username

    def list_related_posts(self) -> List[int]:
        """查询所有与之相关的帖子 ID
        """
        return [post.id for post in session.query(Post).filter(username=self.username)]

class Admin(User):
    """管理员用户类
    """
    def list_related_posts(self) -> Iterable[int]:
        # 管理员与所有的帖子都有关，为了节约内存，使用生成器返回帖子 ID
        for post in session.query(Post).all():
            yield post.id
```

有一位新成员最近加入了项目开发，她需要实现一个新函数来获取与用户有关的所有帖子数量。当她读到 User 类代码时，发现 list_related_posts 方法返回一个包含所有帖子 ID 的列表，于是她就此写下了统计帖子数量的代码：

```python
def get_user_posts_count(user: User) -> int:
    """获取与用户相关的帖子个数
    """
    return len(user.list_related_posts())
```

显然，这样写会报异常。因为 Admin 虽然是 User 类型的子类，但它的 list_related_posts 方法返回却是一个可迭代的生成器，并不是列表对象。而生成器是不支持 len() 操作的。

针对某个特定函数，子类可以替代父类使用，并不等同于代码就符合“里氏替换原则”。要符合 L 原则，**一定得让子类方法和父类返回同一类型的结果，支持同样的操作。或者更进一步，返回支持更多种操作的子类型结果也是可以接受的**。

```python
# 改写

class User(Model):
    """普通用户模型类
    """
    def __init__(self, username: str):
        self.username = username

    def list_related_posts(self) -> Iterable[int]:
        """查询所有与之相关的帖子 ID
        """
        for post in session.query(Post).filter(username=self.username):
            yield post.id

    def get_related_posts_count(self) -> int:
        """获取与用户有关的帖子总数
        """
        value = 0
        for _ in self.list_related_posts():
            value += 1
        return value


class Admin(User):
    """管理员用户类
    """
    def list_related_posts(self) -> Iterable[int]:
        # 管理员与所有的帖子都有关，为了节约内存，使用生成器返回
        for post in session.query(Post).all():
            yield post.id
```

#### 子类修改方法参数会违反 L 原则

```python
class User(Model):
    def list_related_posts(self, include_hidden: bool = False) -> List[int]:
        # ... ...


class Admin(User):
    def list_related_posts(self) -> List[int]:
        # ... ...
```

很明显，上面的代码是不符合 L 原则的，如果父类 User 的 list_related_posts 方法接收一个可选的 include_hidden 参数，那它的子类就不应该去掉这个参数。否则当某个函数调用依赖了 include_hidden 参数，但用户对象却是子类 Admin 类型时，程序就会报错。

```python
# 改写

class User(Model):
    def list_related_posts(self, include_hidden: bool = False) -> List[int]:
        # ... ...


class Admin(User):
    def list_related_posts(self, include_hidden: bool = False, active_only = True) -> List[int]:
        # 子类可以为方法增加额外的可选参数：active_only
        # ... ...
```

### `Dependency Inversion Principle` 依赖倒置原则

它是一条和有关依赖的原则，它认为：**高层模块不应该依赖于低层模块，二者都应该依赖于抽象**。

### `Interface Segregation Principles` 接口隔离原则

它是一条和接口有关的原则，它认为：**客户（client）应该不依赖于它不使用的方法**。

### 总结

* “S: 单一职责原则” 认为一个类只应该有一种被修改的原因
  * 编写更小的类通常更不容易违反 S 原则
  * S 原则同样适用于函数，你可以让函数和类协同工作
* “O: 开放-关闭原则” 认为类应该对改动关闭，对扩展开放
  * 找到需求中频繁变化的那个点，是让类遵循 O 原则的重点所在
  * 使用子类继承的方式可以让类遵守 O 原则
  * 通过定义算法类，并进行依赖注入，也可以让类遵循 O 原则
  * 将数据与逻辑分离，使用数据驱动的方式也是改造代码的好办法
* “L：里氏替换原则” 认为子类应该可以任意替换父类被使用
  * 在类的使用方增加具体的类型判断（isinstance），通常不是最佳解决方案
  * 违反里氏替换原则，通常也会导致违反“开放-关闭”原则
  * 考虑什么是类的核心特征，然后为父类增加新的方法和属性可以帮到你
  * 子类方法应该和父类同名方法返回同一类型，或者返回支持更多操作的子类型也行
  * 子类的方法参数应该和父类同名方法完全一致，或者更为宽松
