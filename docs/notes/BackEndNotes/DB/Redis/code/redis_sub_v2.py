from redis_helper_v1 import RedisHelper


# 订阅者
redis_helper = RedisHelper()
sub = redis_helper.subscribe()
i = 0
while True:
    msg = sub.parse_response()
    print(msg)
    i = i + 1
    if i == 5:
        print(f"接收消息完毕！")
        sub.unsubscribe()
        break