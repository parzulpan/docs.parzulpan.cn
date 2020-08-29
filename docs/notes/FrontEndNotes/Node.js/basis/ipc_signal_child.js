// 进程之间可以通过信号互相通信
// child.js

process.on('SIGTERM', function () {
    console.log('----------SIGTERM----------');
    process.exit(0);
});