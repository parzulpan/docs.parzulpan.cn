// 进程之间可以通过信号互相通信
// parent.js

const child_process = require('child_process');

// 父进程通过.kill方法向子进程发送SIGTERM信号，子进程监听process对象的SIGTERM事件响应信号
let child = child_process.spawn('node', ['./ipc_signal_child.js']);
// 该方法本质上是用来给进程发送信号的，进程收到信号后具体要做什么，完全取决于信号的种类和进程自身的代码
child.kill('SIGTERM');