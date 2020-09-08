import redis


class RedisHelper(object):

    def __init__(self):
        self._conn = redis.Redis("127.0.0.1", 6379)
        
        # 订阅频道
        self.channel = "FM99.9"

    def publish(self, msg):
        """在指定频道上发布消息"""

        self._conn.publish(self.channel, msg)
        return True

    def subscribe(self):
        """返回订阅对象，通过它可以订阅频道"""

        pub = self._conn.pubsub()
        pub.subscribe(self.channel)
        return pub