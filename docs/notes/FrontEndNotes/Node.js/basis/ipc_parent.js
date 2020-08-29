// 如果父子进程都是NodeJS进程，就可以通过IPC（进程间通讯）双向传递数据
// parent.js
const child_process = require('child_process');


let child = child_process.spawn('node', ['./ipc_child.js'], {
    // 父进程在创建子进程时，在options.stdio字段中通过ipc开启了一条IPC通道，之后就可以监听子进程对象的message事件接收来自子进程的消息
    stdio: [0, 1, 2, 'ipc']
});

// 监听
child.on('message', function(msg) {
    console.log(msg);
});

// 通过.send方法给子进程发送消息
child.send({hello: 'hello world'});


