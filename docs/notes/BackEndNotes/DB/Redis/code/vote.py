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

