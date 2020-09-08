# 使用事务
# 使用事务来处理命令的并行执行问题
import time
import threading
import redis


conn = redis.Redis("127.0.0.1", 6379)


def notrans():
    pipeline = conn.pipeline()
    pipeline.incr("notrans:"), "\n"
    time.sleep(0.1)
    pipeline.incr("notrans:", -1)
    print(pipeline.execute()[0])


def run():
    for i in range(3):
        threading.Thread(target=notrans).start()
    time.sleep(0.5)


if __name__ == "__main__":
    run() # 输出 1 1 1