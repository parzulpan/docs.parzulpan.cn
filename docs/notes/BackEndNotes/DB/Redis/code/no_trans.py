# 不使用事务
# 在并行执行命令时，缺少事务可能会引发问题
import redis
import time
import threading


conn = redis.Redis("127.0.0.1", 6379)


def notrans():
    print(conn.incr("notrans:"), "\n")
    time.sleep(0.1)
    conn.incr("notrans:", -1)


def run():
    for i in range(3):
        threading.Thread(target=notrans).start()
    time.sleep(0.5)


if __name__ == "__main__":
    run() # 输出 1 2 3