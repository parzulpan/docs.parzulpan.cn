import redis


host = '127.0.0.1'
port = 6379
 
conn = redis.Redis(host=host, port=port)
 
conn.sadd("set-dest-key2", 4, 3, 5, 2, 6, 1)
for index, val in enumerate(conn.sscan("set-dest-key2")): 
    if index == 1:
        for v in val:
            print(v)

conn.hmset("hash-key", {"k1": "v1", "k2": "v2", "k3": "v3", "intk": 2})
for index, val in enumerate(conn.hscan("hash-key")):
    if index == 1:
        for k, v in val.items():
            print(k, v)

conn.zadd("zset-key-1", {"a": 1, "b": 2, "c": 3})
conn.zadd("zset-key-2", {"b": 4, "c": 1, "d": 0})

# 默认集合函数是sum
conn.zinterstore("zset-key-3", ["zset-key-1", "zset-key-2"])
conn.zrange("zset-key-3", 0, -1, withscores=True)

conn.zunionstore("zset-key-4", ["zset-key-1", "zset-key-2"], aggregate="min")
conn.zrange("zset-key-4", 0, -1, withscores=True)

for index, val in enumerate(conn.zscan("zset-key-1")):
    if index == 1:
        for v in val:
            print(v)