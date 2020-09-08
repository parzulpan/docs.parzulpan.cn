from redis_helper_v1 import RedisHelper


# 订阅者
redis_helper = RedisHelper()
sub = redis_helper.subscribe()
while True:
    msg = sub.listen()
    for i, m in enumerate(msg):
        print(m)
        if i == 5:
            print(f"接收消息完毕！")
            sub.unsubscribe()
            break
    break