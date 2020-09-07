import redis


host = '127.0.0.1'
port = 6379
conn = redis.Redis(host=host, port=port)


def string_ds():
    """ 字符串
    
    """
    # set hello world
    conn.set("hello", "world")


def list_ds():
    """
    
    """


def set_ds():
    """
    
    """


def hash_ds():
    """
    
    """

def zset_ds():
    """
    
    """