# Redis实战

## 简介

《Redis实战》的学习笔记和总结。

[书籍链接](https://book.douban.com/subject/26612779//)
[电子书提取码: 待更新](.)

## 初识 Redis

### Redis 简介

Redis 是一个速度非常快的键值对存储数据库，它可以存储键和五种不同类型的值之间的映射，可以将存储在内存的键值对数据持久化到硬盘，可以使用复制特性来扩展读性能，还可以使用客户端分片老扩展写性能。

Redis 的优点：

* **速度快**：
  * 因为数据存在内存中，类似于 HashMap ，HashMap 的优势就是查找和操作的时间复杂度都是O (1) 。
  * Redis 本质上是一个 Key-Value 类型的内存数据库，很像 Memcached ，整个数据库统统加载在内存当中进行操作，定期通过异步操作把数据库数据 flush 到硬盘上进行保存。fork子进程持久化。
  * 因为是纯内存操作，Redis 的性能非常出色，每秒可以处理超过 10 万次读写操作，是已知性能最快的 Key-Value 数据库。
* **支持丰富数据类型**: String ，List，Set，Sorted Set，Hash 。
* **有丰富的特性**：订阅发布功能、Key 过期策略、事务、支持多个 DB、计数等等。
* **持久化存储**：Redis 提供 RDB 和 AOF 两种数据的持久化存储方案，解决内存数据库最担心的万一 Redis 挂掉，数据会消失掉的情况。

Redis 的缺点：

* **数据量限制**：由于 Redis 是内存数据库，所以单台机器存储的数据量跟机器本身的内存大小有段。虽然 Redis 本身有 Key 过期策略，但是还是需要提前预估和节约内存。如果内存增长过快，需要定期删除数据。
*** 线程限制**：Redis 是单线程的，单台服务器无法充分利用多核服务器的 CPU。

Redis的使用场景：

* **缓存**：缓存现在几乎是所有中大型网站都在用的必杀技，合理的利用缓存不仅能够提升网站访问速度，还能大大降低数据库的压力。Redis提供了键过期功能，也提供了灵活的键淘汰策略，所以，现在Redis用在缓存的场合非常多。
* **排行榜**：很多网站都有排行榜应用的，如京东的月度销量榜单、商品按时间的上新排行榜等。Redis提供的有序集合数据类构能实现各种复杂的排行榜应用。
* **计数器**：什么是计数器，如电商网站商品的浏览量、视频网站视频的播放数等。为了保证数据实时效，每次浏览都得给+1，并发量高时如果每次都请求数据库操作无疑是种挑战和压力。Redis提供的incr命令来实现计数器功能，内存操作，性能非常好，非常适用于这些计数场景。
* **分布式会话**：集群模式下，在应用不多的情况下一般使用容器自带的session复制功能就能满足，当应用增多相对复杂的系统中，一般都会搭建以Redis等内存数据库为中心的session服务，session不再由容器管理，而是由session服务及内存数据库管理。
* **分布式锁**：在很多互联网公司中都使用了分布式技术，分布式技术带来的技术挑战是对同一个资源的并发访问，如全局ID、减库存、秒杀等场景，并发量不大的场景可以使用数据库的悲观锁、乐观锁来实现，但在并发量高的场合中，利用数据库锁来控制资源的并发访问是不太理想的，大大影响了数据库的性能。可以利用Redis的setnx功能来编写分布式的锁，如果设置返回1说明获取锁成功，否则获取锁失败，实际应用中要考虑的细节要更多。
* **社交网络**：点赞、踩、关注/被关注、共同好友等是社交网站的基本功能，社交网站的访问量通常来说比较大，而且传统的关系数据库类型不适合存储这种类型的数据，Redis提供的哈希、集合等数据结构能很方便的的实现这些功能。
* **最新列表**：Redis列表结构，LPUSH可以在列表头部插入一个内容ID作为关键字，LTRIM可用来限制列表的数量，这样列表永远为N个ID，无需查询最新的列表，直接根据ID去到对应的内容页即可。
* **消息系统**：消息队列是大型网站必用中间件，如ActiveMQ、RabbitMQ、Kafka等流行的消息队列中间件，主要用于业务解耦、流量削峰及异步处理实时性低的业务。Redis提供了发布/订阅及阻塞队列功能，能实现一个简单的消息队列系统。另外，这个不能和专业的消息中间件相比。

### Redis 数据结构简介

五种结构：

| 结构类型 | 结构存储的值 | 结构的读写能力 |
| :--- | :--- | :--- | :--- |
| STRING | 可以是字符串、整数或者浮点数 | 对整个字符串或者字符串的其中一部分执行操作；对整数和浮点数执行自增或者自减操作 |
| LIST | 一个链表，链表上的每个节点都包含了一个字符串 | 从链表的两端推入或者弹出元素；根据偏移量对链表进行修剪；读取单个或者多个元素；根据值查找或者移除元素 |
| SET | 包含字符串的无序收集器，并且被包含的每个字符串都是独一无二、各不相同的 | 添加、获取、移除单个元素；检查一个元素是否存在于集合中；计算交集、并集、差集；从集合中随机获取元素 |
| HASH | 包括键值对的无序散列表 | 添加、获取、移除单个键值对；获取所有键值对 |
| ZSET | 字符串成员与浮点数之间的有序映射，元素的排列顺序由分值的大小决定 | 添加、获取、删除单个元素；根据分值范围或者成员来获取元素 |

### Redis 中的字符串

字符串类型是二进制安全的。意思是 redis 的字符串可以包含任何数据。比如 jpg 图片或者序列化的对象。

字符串类型是 Redis 最基本的数据类型，字符串类型的值最大能存储 512MB。

![string-da](resources/string-da.png)

| 命令| 行为 | 实例 | Python |
| :--- | :--- | :--- | :--- |
| `SET key value`  | 设置指定 key 的值 |  |  |
| `GET key` | 获取指定 key 的值 |  |  |
| `GETRANGE key start end` | 返回 key 中字符串值的子字符 |  |  |
| `GETSET key value` | 将给定 key 的值设为 value ，并返回 key 的旧值 |  |  |
| `GETBIT key offset` | 对 key 所储存的字符串值，获取指定偏移量上的位 |  |  |
| `MGET key1 [key2..]` | 获取所有(一个或多个)给定 key 的值 |  |  |
| `SETBIT key offset value` | 对 key 所储存的字符串值，设置或清除指定偏移量上的位 |  |  |
| `SETEX key seconds value` | 将值 value 关联到 key ，并将 key 的过期时间设为 seconds |  |  |
| `SETNX key value` | 只有在 key 不存在时设置 key 的值 |  |  |
| `SETRANGE key offset value` | 用 value 参数覆写给定 key 所储存的字符串值，从偏移量 offset 开始 |  |  |
| `STRLEN key` | 返回 key 所储存的字符串值的长度 |  |  |
| `MSET key value [key value ...]` | 同时设置一个或多个 key-value 对 |  |  |
| `PSETEX key milliseconds value` | 和 SETEX 命令相似，但它以毫秒为单位设置 |  |  |
| `INCR key` | 将 key 中储存的数字值增一 |  |  |
| `INCRBY key increment` | 将 key 所储存的值加上给定的增量值 |  |  |
| `INCRBYFLOAT key increment` | 将 key 所储存的值加上给定的浮点增量值 |  |  |
| `DECR key` | 将 key 中储存的数字值减一 |  |  |
| `DECRBY key decrement` | key 所储存的值减去给定的减量值 |  |  |
| `APPEND key value` | 如果 key 已经存在并且是一个字符串， APPEND 命令将指定的 value 追加到该 key 原来值（value）的末尾 |  |  |

### Redis 中的列表

Redis中的列表是简单的字符串列表，按照插入顺序排序，可以添加一个元素到列表的头部或者尾部。

一个列表最多可以包含 2^32 - 1 个元素 (40多亿)。

![list-da](resources/string-da.png)

| 命令| 行为 | 实例 | Python |
| :--- | :--- | :--- | :--- |
| `BLPOP key1 [key2 ] timeout` | 移出并获取列表的第一个元素， 如果列表没有元素会阻塞列表直到等待超时或发现可弹出元素为止 |  |  |
| `BRPOP key1 [key2 ] timeout` | 移出并获取列表的最后一个元素， 如果列表没有元素会阻塞列表直到等待超时或发现可弹出元素为止 |  |  |
| `BRPOPLPUSH source destination timeout` | 从列表中弹出一个值，将弹出的元素插入到另外一个列表中并返回它，如果列表没有元素会阻塞列表直到等待超时或发现可弹出元素为止 |  |  |
| `LINDEX key index` | 通过索引获取列表中的元素 |  |  |
| `LINSERT key BEFORE|AFTER pivot value` | 在列表的元素前或者后插入元素 |  |  |
| `LLEN key` | 获取列表长度 |  |  |
| `LPOP key` | 移出并获取列表的第一个元素 |  |  |
| `LPUSH key value1 [value2]` | 将一个或多个值插入到列表头部 |  |  |
| `LPUSHX key value` | 将一个值插入到已存在的列表头部 |  |  |
| `LRANGE key start stop` | 获取列表指定范围内的元素 |  |  |
| `LREM key count value` | 移除列表元素 |  |  |
| `LSET key index value` | 通过索引设置列表元素的值 |  |  |
| `LTRIM key start stop` | 对一个列表进行修剪，即让列表只保留指定区间内的元素，不在指定区间之内的元素都将被删除 |  |  |
| `RPOP key` | 移除列表的最后一个元素，返回值为移除的元素 |  |  |
| `RPOPLPUSH source destination` | 移除列表的最后一个元素，并将该元素添加到另一个列表并返回 |  |  |
| `RPUSH key value1 [value2]` | 在列表中添加一个或多个值 |  |  |
| `RPUSHX key value` | 为已存

### Redis 中的集合

Redis 中的集合是字符串类型的无序集合，集合成员是唯一的，这就意味着集合中不能出现重复的数据。

Redis 中的集合是通过哈希表实现的，所以添加，删除，查找的复杂度都是 `O(1)`。

集合中最大的成员数为 2^32 - 1 (40多亿)。

![set-da](resources/set-da.png)

| 命令| 行为 | 实例 | Python |
| :--- | :--- | :--- | :--- |
| `SADD key member1 [member2]` | 向集合添加一个或多个成员 |  |  |
| `SCARD key` | 获取集合的成员数 |  |  |
| `SISMEMBER key member` | 判断 member 元素是否是集合 key 的成员 |  |  |
| `SMEMBERS key` | 返回集合中的所有成员 |  |  |
| `SMOVE source destination member` | 将 member 元素从 source 集合移动到 destination 集合 |  |  |
| `SPOP key` | 移除并返回集合中的一个随机元素 |  |  |
| `SRANDMEMBER key [count]` | 返回集合中一个或多个随机数 |  |  |
| `SREM key member1 [member2]` | 移除集合中一个或多个成员 |  |  |
| `SDIFF key1 [key2]` | 返回第一个集合与其他集合之间的差异 |  |  |
| `SDIFFSTORE destination key1 [key2]` | 返回给定所有集合的差集并存储在 destination 中 |  |  |
| `SINTER key1 [key2]` | 返回给定所有集合的交集 |  |  |
| `SINTERSTORE destination key1 [key2]` | 返回给定所有集合的交集并存储在 destination 中 |  |  |
| `SUNION key1 [key2]` | 返回所有给定集合的并集 |  |  |
| `SUNIONSTORE destination key1 [key2]` | 所有给定集合的并集存储在 destination 集合中 |  |  |
| `SSCAN key cursor [MATCH pattern] [COUNT count]` | 迭代集合中的元素 |  |  |

### Redis 中的哈希

是一个字符串类型的 field（字段） 和 value（值） 的映射表，哈希特别适合用于存储对象。

Redis 中每个哈希可以存储 2^32 - 1 键值对（40多亿）。

![hash-da](resources/hash-da.png)

| 命令| 行为 | 实例 | Python |
| :--- | :--- | :--- | :--- |
| `HDEL key field1 [field2]` | 删除一个或多个哈希表字段 |  |  |
| `HEXISTS key field` | 查看哈希表 key 中，指定的字段是否存在 |  |  |
| `HGET key field` | 获取存储在哈希表中指定字段的值 |  |  |
| `HGETALL key` | 获取在哈希表中指定 key 的所有字段和值 |  |  |
| `HINCRBY key field increment` | 为哈希表 key 中的指定字段的整数值加上增量 increment |  |  |
| `HINCRBYFLOAT key field increment` | 为哈希表 key 中的指定字段的浮点数值加上增量 increment  |  |  |
| `HKEYS key` | 获取所有哈希表中的字段 |  |  |
| `HLEN key` | 获取哈希表中字段的数量 |  |  |
| `HMGET key field1 [field2]` | 获取所有给定字段的值 |  |  |
| `HMSET key field1 value1 [field2 value2]` | 同时将多个 field-value (域-值)对设置到哈希表 key 中 |  |  |
| `HSET key field value` | 将哈希表 key 中的字段 field 的值设为 value |  |  |
| `HSETNX key field value` | 只有在字段 field 不存在时，设置哈希表字段的值 |  |  |
| `HVALS key` | 获取哈希表中所有值 |  |  |
| `HSCAN key cursor [MATCH pattern] [COUNT count]` | 迭代哈希表中的键值对 |  |  |

### Redis 中的有序集合

有序集合和集合一样也是字符串类型元素的集合,且不允许重复的成员。

不同的是每个元素都会关联一个浮点数类型的分数，redis 正是通过分数来为集合中的成员进行从小到大的排序。有序集合的成员是唯一的，但分数(score)却可以重复。

集合是通过哈希表实现的，所以添加，删除，查找的复杂度都是O(1)。

Redis 中每个有序集合可以存储 2^32 - 1 键值对（40多亿）。

![order-set-da](resources/order-set-da.png)

| 命令| 行为 | 实例 | Python |
| :--- | :--- | :--- | :--- |
| `ZADD key score1 member1 [score2 member2]` | 向有序集合添加一个或多个成员，或者更新已存在成员的分数 |  |  |
| `ZCARD key` | 获取有序集合的成员数 |  |  |
| `ZCOUNT key min max` | 计算在有序集合中指定区间分数的成员数 |  |  |
| `ZINCRBY key increment member` | 有序集合中对指定成员的分数加上增量 increment |  |  |
| `ZINTERSTORE destination numkeys key [key ...]` | 计算给定的一个或多个有序集的交集并将结果集存储在新的有序集合 key 中 |  |  |
| `ZLEXCOUNT key min max` | 在有序集合中计算指定字典区间内成员数量 |  |  |
| `ZRANGE key start stop [WITHSCORES]` | 通过索引区间返回有序集合指定区间内的成员 |  |  |
| `ZRANGEBYLEX key min max [LIMIT offset count]` | 通过字典区间返回有序集合的成员 |  |  |
| `ZRANGEBYSCORE key min max [WITHSCORES] [LIMIT]` | 通过分数返回有序集合指定区间内的成员 |  |  |
| `ZRANK key member` | 返回有序集合中指定成员的索引 |  |  |
| `ZREM key member [member ...]` | 移除有序集合中的一个或多个成员 |  |  |
| `ZREMRANGEBYLEX key min max` | 移除有序集合中给定的字典区间的所有成员 |  |  |
| `ZREMRANGEBYRANK key start stop` | 移除有序集合中给定的排名区间的所有成员 |  |  |
| `ZREMRANGEBYSCORE key min max` | 移除有序集合中给定的分数区间的所有成员 |  |  |
| `ZREVRANGE key start stop [WITHSCORES]` | 返回有序集中指定区间内的成员，通过索引，分数从高到低 |  |  |
| `ZREVRANGEBYSCORE key max min [WITHSCORES]` | 返回有序集中指定分数区间内的成员，分数从高到低排序 |  |  |
| `ZREVRANK key member` | 返回有序集合中指定成员的排名，有序集成员按分数值递减排序 |  |  |
| `ZSCORE key member` | 返回有序集中，成员的分数值 |  |  |
| `ZUNIONSTORE destination numkeys key [key ...]` | 计算给定的一个或多个有序集的并集，并存储在新的 key 中 |  |  |
| `ZSCAN key cursor [MATCH pattern] [COUNT count]` | 迭代有序集合中的元素（包括元素成员和元素分值） |  |  |

### 你好 Redis

构建一个简单的文章投票网站的后端。

```python
# -*- coding: utf-8 -*-

import time
import unittest

import redis


ONE_WEEK_IN_SECONDS = 7 * 86400
VOTE_SCORE = 432
ARTICLE_PER_PAGE = 25


class Vote:

    def __init__(self, conn):
        self.conn = conn

    def article_vote(self, user, article):
        """ 文章投票

        """
        # 文章的投票截止时间和发布时间
        # zscore(name, value) : 获取name对应有序集合中value对应的分数
        cutoff = time.time() - ONE_WEEK_IN_SECONDS
        post_time = self.conn.zscore("time:", article)

        # 检查是否还可以对文章进行投票
        if post_time < cutoff:
            return

        # 如果用户是第一次为这篇文章投票，那么增加这篇文章的投票数量和评分
        # sadd(name,values) : name对应的集合中添加元素
        # zincrby(name, amount, value) : 自增name对应的有序集合的name对应的分数
        # hincrby(name, key, amount=1 : 自增name对应的hash中的指定key的值，不存在则创建key=amount
        article_id = article.partition(":")[-1]
        print("article_id", article_id)
        if self.conn.sadd("voted:" + article_id, user):
            self.conn.zincrby("score:", VOTE_SCORE, article)
            self.conn.hincrby(article, "votes", 1)

    def post_article(self, user, title, link):
        """ 文章发布并获取文章

        """
        # 生成一个新的文章ID
        # incr(name, amount=1) : 自增name对应的值，当name不存在时，则创建name＝amount，否则，则自增
        article_id = str(self.conn.incr("article:"))

        # 将发布文章的用户添加到文章的已投票用户名单里面，
        # 然后将这个名单的过期时间设置为一周
        # expire(name ,time) : 为某个redis的某个name设置超时时间
        voted = "voted:" + article_id
        self.conn.sadd(voted, user)
        self.conn.expire(voted, ONE_WEEK_IN_SECONDS)

        # 将文章信息存储在一个散列表里面
        # hset(name, key, value) : name对应的hash中设置一个键值对（不存在，则创建；否则，修改）
        now = time.time()
        article = "article:" + article_id
        self.conn.hmset(article, {
            "title": title,
            "link": link,
            "poster": user,
            "time": now,
            "votes": 1,
        })

        # 将文章添加到根据发布时间排序的有序集合和根据评分排序的有序集合里面
        # zadd(name, *args, **kwargs) : 在name对应的有序集合中添加元素
        self.conn.zadd("score:", {article: now + VOTE_SCORE})
        self.conn.zadd("time:", {article: now})

        return article_id

    def get_articles(self, page, order="socre:"):
        """ 文章获取

        """
        start = (page - 1) * ARTICLE_PER_PAGE
        end = start + ARTICLE_PER_PAGE - 1

        # zrevrange(name, start, end, withscores=False, score_cast_func=float) : 从大到小排序
        # hgetall(name) : 获取name对应hash的所有键值
        ids = self.conn.zrevrange(order, start, end)
        articles = []
        for id in ids:
            article_data = self.conn.hgetall(id)
            article_data["id"] = id
            articles.append(article_data)

        return articles

    def add_remove_groups(self, article_id, to_add=[], to_remove=[]):
        """ 将文章添加到群组和从群组中移除文章

        """
        # srem(name, values) : 在name对应的集合中删除某些值
        article = "article:" +  article_id
        for group in to_add:
            self.conn.sadd("group:" + group, article)
        for group in to_remove:
            self.conn.srem("group:" + group, article)

    def get_group_articles(self, group, page, order="socre:"):
        """从群组里面获取一整页文章

        """
        # 为每个群组的每种排列顺序都创建一个键
        key = order + group

        # exists(name) : 检测redis的name是否存在，存在就是True，False 不存在
        #
        # 检查是否已缓存的排序结果，如果没有的话就现在进行排序
        if not self.conn.exists(key):
            # 根据评分或者发布时间对群组文章进行排序
            self.conn.zinterstore(key, ["group:" + group, order], aggregate="max")
            # 让Redis在60秒之后自动删除这个有序集合
            self.conn.expire(key, 60)

        return self.get_articles(page, key)


class TestVote(unittest.TestCase):

    def test_vote(self):
        host = "127.0.0.1"
        port = 6379
        conn = redis.Redis(host=host, port=port)

        vote = Vote(conn)
        article_id = str(vote.post_article('post_user', 'a titil A', 'www.parzulpan.cm'))
        print("We posted a new article with id:", article_id)
        print()
        # self.assertTrue(article_id)

        vote.article_vote('vote_user', 'artile:' + article_id)
        vote.article_vote('vote_user1', 'artile:' + article_id)
        vote.article_vote('vote_user2', 'artile:' + article_id)
        print("We voted for the article, it now has votes:")
        # hget(name,key) : 在name对应的hash中获取根据key获取value
        v = int(conn.hget('article:' + article_id, 'votes'))
        print(v)
        print()
        # self.assertTrue(v >= 1)

        print("The currently highest-scoring articles are:")
        articles = vote.get_articles(1)
        print(articles)
        print()
        # self.assertTrue(len(articles) >= 1)

        vote.add_remove_groups(article_id, ['new-group'])
        print("We added the article to a new group, other articles include:")
        articles = vote.get_group_articles('new-group', 1)
        print(articles)
        print()
        # self.assertTrue(len(articles) >= 1)

        to_del = (
            conn.keys('time:*') + conn.keys('voted:*') + conn.keys('score:*') + 
            conn.keys('article:*') + conn.keys('group:*')
        )
        if to_del:
            conn.delete(*to_del)


if __name__ == "__main__":
    test = TestVote()
    test.test_vote()
```

## 使用 Redis 构建 Web 应用

从高层次的角度来看，Web 应用就是通过 HTTP 协议对网页浏览器发送的请求进行响应的服务器或者服务，一个 Web 服务器对请求进行响应的典型步骤为：

* 服务器对客户端发来的请求（request）进行解析。
* 请求被转发给一个预定义的处理器（handler）。
* 处理器可能会从数据库中取出数据。
* 处理器根据取出的数据对模板（template）进行渲染（render）。
* 处理器向客户端返回渲染后的内容作为对请求的响应（response）。

显然这种情况下的 Web 请求被认为是**无状态的**（stateless），即服务器本身不会记录与过往请求有关的任何信息，这使得失效的服务器可以很容易被替换掉。

这一章围绕着发现并解决 Fake Web Retailer 这个虚拟的大型网上商店来展开，它每天都会有大约 500 万名不同的用户使用，这些用户会给网站带来 1 亿次点击，并从网站购买超过 10 万件商品。

### 登录和 cookie 缓存

cookie 有少量数据组成，网站会要求我们的浏览器存储这些数据，并在每次服务发送请求时将这些数据传回给服务。

对于用来登录的 cookie，有两种常见的方法可以将登录信息存储在 cookie 里面：

* 签名（signed）cookie：通常会存储用户名，可能还有用户 ID、用户最后一次成功登录的时间，以及网站觉得有用的信息。除了用户的相关信息之外，它还包含一个签名，服务器可以使用这个签名来验证浏览器发送的消息是否未经改动（比如将 cookie 中的登录用户名改成另外一个用户）。
* 令牌（token）cookie：它会在 cookie 里面存储一串随机字节作为令牌，服务器可以根据令牌在数据库中查找令牌的拥有者。随着时间的推移，旧令牌会被新令牌取代。

| cookie 类型 | 优点 | 缺点 |
| :--- | :--- | :--- |
| 签名 cookie | 验证 cookie 所需的一切信息都存储在 cookie 里面。cookie 可以包含额外的信息，并且对这些信息进行签名也很容易。 | 正确地处理签名很难。很容易忘记对数据进行签名，或者忘记验证数据的签名。从而造成安全漏洞。 |
| 令牌cookie | 添加信息非常容易。cookie 的体积非常小，因此移动端和速度较慢的客户端可以更快地发送请求。 | 需要服务器中存储更多信息。如果使用的是关系型数据库，那么载入和存储 cokkie 的代价可能会很高。 |

Fake Web Retailer 没有签名 cookie 的需求，所以使用令牌 cookie 来引用关系数据库表中负责存储用户登录信息的条目以及用户的访问时常、已浏览商品的数量。

因为其一天的负载量很大，所以使用 Redis 重新实现登录 cookie 功能，取代目前有关系数据库实现登录 cookie 功能。

首先，使用一个散列来登录 cookie 令牌与登录用户之间的映射。需要检查一个用户是否登录，需要根据给定的令牌来检查对应的用户，并在用户已经登录的情况下，返回该用户的 ID：

```python
def check_token(conn,  token):
    """检查登录 cookie """

    # 尝试获取并返回令牌对应的用户
    return conn.hget("login:", token)
```

用户登录后，每次浏览页面，都要将数据更新：

```python
def update_token(conn, token, user, item=None):
    """更新令牌"""

    timestamp = time.time()

    # 维护令牌与已登录用户之间的映射
    conn.hset("login:", token, user)

    # 记录令牌最后一次出现的时间
    conn.zadd('recent:', token, timestamp)

    if item:
        # 记录用户浏览过的商品
        conn.zadd("viewed:" + token, item, timestamp)
        # 移除旧的记录，只保留用户最近浏览过的 25 个商品
        conn.zremrangebyrank("viewed:" + token, 0, -26)
```

通过使用 `update_token()` 函数，一台最近几年生产的服务器上面，每秒至少可以记录 20000 件商品，比高峰时期所需的 6000 次读写要高 3 倍还多，通过后面介绍的方法，我们还可以对他进一步进行优化，即使是现在这个版本，也比原来的关系型数据库性能提升了 100 倍。

因为存储 session 所需的内存会随着时间不断的增加，所以我们需要一个定期清理函数来限制 session 的上限：

```python
QUIT = False
LIMIT = 10000000

def clean_sesions(con):
    """清理旧会话"""

    while not QUIT:
        # 找出目前已有令牌的数量
        size = conn.zcrad("recent:")

        # 令牌数量未超过限制，休眠并在之后重新检查
        if size <= LIMIT:
            time.sleep(1)
            continue

        # 获取需要移除的令牌 ID
        end_index = min(size - LIMIT, 100)
        tokens = conn.zrange("recent:", 0, end_index - 1)

        # 为那些将要被删除的令牌构建键名
        session_keys = []
        for token in tokens:
            session_keys.append("viewed:" + token)

        # 移除最旧的那些令牌
        conn.delete(*session_keys)
        conn.hdel("login:", *tokens)
        conn.zrem("recent:", *tokens)
```

假设网站每天有 500W 的访问量，那么两天令牌就会到达 1kW 的上限。一天有 24×3600 = 86400 秒，所以每秒网站平均产生 5000000/86400 < 58 个新对话。也就是说在达到 1kW 以后，每秒至少需要清理 58 个 token 才能防止内存消耗殆尽的情况产生。但是实际上，我们的 `clean_session()` 在通过网络来运行时，每秒能够清理 10K多个 oken，所以因为旧 token 过多耗光内存的情况不会出现。

熟悉多线程和并发编程可以知道 `clean_session()` 其实存在一个竞争条件：删除某个用户信息事，该用户又在同一时间访问该网站时。但是，目前看来，这个竞争条件除了会使得用户重新登录一次之外，并不会对数据记录数据产生明显的影响。

### 使用 Redis 实现购物车

每个用户的购物车都是一个散列，这个散列存储了商品ID与商品订购数量之间的映射：

```python
def add_to_cart(conn, session, item, count):
    """更新购物车"""

    # 加入到购物车的某件商品大于 0 则更新，否则移除
    if count <= 0:
        conn.hrem("cart:" + session, item)
    else:
        conn.hset("cart:" + session, item, count)
```

接着更新之前的清理旧会话函数，让它在清理旧会话的同时，将旧会话的购物车也一并删除：

```python
def clean_full_sessions(conn):
    """清理旧会话所有东西"""

    while not QUIT:
        # 找出目前已有令牌的数量
        size = conn.zcrad("recent:")

        # 令牌数量未超过限制，休眠并在之后重新检查
        if size <= LIMIT:
            time.sleep(1)
            continue

        # 获取需要移除的令牌 ID
        end_index = min(size - LIMIT, 100)
        tokens = conn.zrange("recent:", 0, end_index - 1)

        # 为那些将要被删除的令牌构建键名
        session_keys = []
        for sess in sessions:
            session_keys.append("viewed:" + sess)

            # 将旧会话的购物车也一并删除
            session_keys.append("cart:" + sess)

        # 移除最旧的那些令牌
        conn.delete(*session_keys)
        conn.hdel("login:", *sessions)
        conn.zrem("recent:", *sessions)
```

将会话和购物车都存储到了 Redis 里面，除了可以减少请求的体积之外，还能通过其他信息加强网站的功能。

### 网页缓存

网页中很多内容并不会发生大的变化，我们可以缓存这些静态网页，加快网页加载速度，也能提升用户使用的感受。

所有标准的 Python 应用程序都提供了在处理请求之前或者之后添加层（layer）的能力，这些层通常被成为中间件（middleware）或者插件（plugin）。创建这样一个层来调用 Redis 缓存函数：对于一个不能被缓存的请求，函数将直接生成并返回页面；而对于可以被缓存的请求，函数首先会尝试从缓存里面取出并返回被缓存的页面，如果缓存页面不存在，那么函数会生成页面并将其缓存在 Redis 里面五分钟，最后再将页面返回给函数调用者：

```python
def cache_request(conn, request, callback):
    """缓存函数"""

    # 对于不能被缓存的请求，直接调用回调函数
    if not can_cache(con, request):
        return callback(request)

    # 将请求转换成一个简单的字符串键，方便之后查找
    page_key = "cache:" + hash_request(requset)
    content = conn.get(page_key)

    # 如果页面还没有被缓存，那么生成页面，并将其放在缓存里面
    if not content:
        content = callback(request)
        conn.setex(page_key, content, 300)

    return content
```

对于那些需要经常访问数据页但不常改变的页面来说，这个缓存函数对于减少页面载入时间和降低数据库负载的作用会更加明显。

### 数据行缓存

那么对于那些经常变化的页面该如何处理呢？

假设网站在做一个促销活动，所有商品的数目都是限定的。这种情况下，不能对整个商品页面进行缓存，这样有可能让用户看到错误的剩余数量，每次载入页面都从数据库提取剩余数量的话，会对数据库带来巨大的压力。我们可以对数据行进行缓存。

具体做法是：编写一个持续运行的守护进程函数，让这个函数将指定的数据行缓存到 Redis 里面，并不定期的对这些缓存进行更新。缓存函数会将数据行编码为 JSON 字典并存储在 Redis 的字符串里面，其中，数据行的名字会被映射为 JSON 字典的键，而数据行的值会被映射为 JSON 字典的值。

![缓存的数据行](resources/缓存的数据行.png)

使用两个有序集合来记录应该何时对缓存进行更新：第一个有序集合为调度（schedule）有序集合，它的成员为数据行的行 ID，而分值则是一个时间戳，这个时间戳记录了应该在何时将指定的数据行缓存到 Redis 里面；第二个有序集合为延时（delay）有序集合，它的成员也是数据行的行 ID，而分值则记录了指定行的缓存需要每隔多少秒更新一次。

```python
def schedule_row_cache(conn, row_id, delay):
    """负责调度缓存和终止缓存"""

    # 设置数据行的延迟值
    conn.zadd("delay:", row_id, delay)

    # 立即对需要缓存的数据行进行调度
    conn.zadd("schedule:", row_id, time.time())
```

```python
def cache_rows(conn):
    """守护进程函数，负责缓存数据行"""

    while not QUIT:
        # 尝试获取下一个需要被缓存的数据行以及该行的调度时间戳，
        # 返回一个包含零个或一个元组的列表
        next = conn.zrange("schedule:", 0, 0, withscores=True)
        now = time.time()

        # 暂时没有行需要被换成，休眠 50 毫秒后重试
        if not next or next[0][1] > now:
            time.sleep(0.05)
            continue

        row_id = next[0][0]

        # 提前获取下一次调度的延迟时间， 如果延迟值<=0, 将这个行从所有缓存中移除
        delay = conn.zscore('delay:', row_id)
        if delay <= 0:
            conn.zrem("delay:", row_id)
            conn.zrem("schedule:", row_id)
            conn.delete("inv:" + row_id)
            continue

        # 读取数据行，并更新调度时间和设置缓存值
        row = Inventory.get(row_id)
        conn.zadd("schedule:", row_id, now + delay)
        conn.set("inv:" + row_id, json.dumps(row.to_dict()))
```

通过组合使用调度函数和持续运行的守护进程函数，我们实现了一种重复进行调度的自动缓存机制，并且可以随心所欲的控制数据行缓存的更新频率：如果参与活动的用户非常多，我们最好几秒更新一次缓存，如果商品数据并不经常改变，或者缺货是可以接受的，我们可以一分钟更新一次缓存。

### 网页分析

通过缓存我们极大的提升了网站的响应速度，但是网站总共有 100000 件商品，全部缓存将会耗光内存，于是我们决定只缓存 10000 件最经常被浏览的商品。

修改之前的update_token()函数，使之能够记录最常被访问的商品：

```python
def update_token(conn, token, user, item = None):
    """更新令牌"""

    # 获取当前时间
    timestamp = time.time()

    # 对用户存储在登录散列里的数据进行更新
    conn.hset('login:', token, user)

    # 将用户的令牌和当前时间戳添加到记录最近登录的用户的有序集合里面
    conn.zadd('recent:', token, timestamp)

    if item:
        # 将用户正在浏览的商品加入到他的最近浏览中去
        conn.zadd('viewed:' + token, item, timestamp)

        # 对每个用户，只保留最新的 25 条最近浏览
        conn.zremrangebyrank('viewed:' + token, 0, -26)

        # 新添加：采用负数表示页面浏览次数，浏览次数越高的页面，其索引值越小，排名也就越靠前
        conn.zincrby('viewed:', item, -1)
```

为了浏览次数排行榜能够保持最新，我们需要定期修剪有序集合的长度并且调整已有元素的分值，使得新流行的商品也可以在排行榜里占据一席之地：

```python
def rescale_viewed(conn):
    """守护进程函数，调整商品"""

    while not QUIT:
        # 删除所有排名在 20000 名之后的商品
        conn.zremrangebyrank("viewed:", 0, -20001)

        # 将浏览次数降低为原来的一半
        conn.zinterstore("viewed:", {"viewed:": 0.5})

        # 五分钟之后再次执行这个操作
        time.sleep(300)
```

实现在缓存页面时用到的函数 `can_cache()`：

```python
def can_cache(conn, request):
    """判断页面是否需要被缓存"""

    item_id = extract_item_id(request)

    # 检查这个页面能否被缓存以及这个页面是否为商品页面
    if not item_id or is_dynamic(request):
        return False

    # 获得商品的浏览次数排名，并根据它来判断是否需要缓存这个页面
    rank = conn.zrank("viewed:", item_id)
    return rank is not None and rank < 10000
```

### 小结

以上介绍了几种用于降低网站的数据库负载和 Web 服务器负责的方法。

在为应用程序创建新构件的时候，不要害怕去重构已有的构件，就像购物车cookie的例子和基于登录会话cookie实现网页分析的的例子一样，已有的构件有时候需要细微的修改才能真正满足需求。

## Redis命令

### 字符串



### 列表

### 集合

### 散列

### 有序集合

### 发布与订阅

### 其他命令

#### 排序

#### 基本的 Redis 事务

#### 键的过期时间

### 小结

## 数据安全与性能保障

## 使用Redis构建支持程序

## 使用Redis构建应用程序组件

## 基于搜索的应用程序

## 构建简单的社交网络

## 降低内存占用

## 扩展Redis

## Redis的Lua脚本编程

