import time
from redis_helper_v1 import RedisHelper


# 发布者
redis_helper = RedisHelper()
i = 0
while True:
    print(f"发送消息：hello world __{i}")
    redis_helper.publish(f"hello world __{i}")
    time.sleep(3)
    i = i + 1
    if i == 10:
        print(f"发送消息完毕！")
        break