// 如果父子进程都是NodeJS进程，就可以通过IPC（进程间通讯）双向传递数据
// child.js


// 在process对象上监听message事件接收来自父进程的消息，并通过.send方法向父进程发送消息
process.on('message', function(msg) {
    msg.hello = msg.hello.toUpperCase();
    process.send(msg);
});