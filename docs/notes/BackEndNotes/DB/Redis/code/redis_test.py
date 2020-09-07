import redis


host = '127.0.0.1'
port = 6379
 
r = redis.Redis(host=host, port=port)
 
r.set('foo', 'bar')
print(r.get('foo'))