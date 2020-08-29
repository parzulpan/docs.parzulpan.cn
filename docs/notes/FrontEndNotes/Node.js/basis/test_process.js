// 进程管理
const child_process = require('child_process');
const util = require('util');
const http = require('http');


// 使用NodeJS调用终端命令来简化目录拷贝
function copy(src, dest, callback) {
    child_process.exec(util.format('cp - r %s/* %s', src, dest), callback);
}

copy('../resources/test_dst.txt', '../resources/test_dst_copy1.txt', function(err, data) {
    console.log(data.toString());
})


// Process
// 任何一个进程都有启动进程时使用的命令行参数，有标准输入标准输出，有运行环境和运行状态
// 注意：process不是内置模块，而是一个全局对象，因此在任何地方都可以直接使用


// Child Process
// 使用child_process模块可以创建和控制子进程，它最核心是.spawn


// Cluster
// cluster模块是对child_process模块的进一步封装，专用于解决单进程Node.js Web服务器无法充分利用多核CPU的问题
// 使用该模块可以简化多进程服务器程序的开发，让每个核上运行一个工作进程，并统一通过主进程监听端口和分发请求


// 应用场景
// 1. 如何获取命令行参数
function main(argv) {
    // ...
}
main(process.argv.slice(2));

// 2. 如何退出程序
try {
    // ...
} catch (err) {
    // ...
    process.exit(1);
}

// 3. 如何控制输入输出
// NodeJS程序的标准输入流（stdin）、一个标准输出流（stdout）、一个标准错误流（stderr）
// 分别对应process.stdin、process.stdout和process.stderr，第一个是只读数据流，后边两个是只写数据流
function log() {
    process.stdout.write(
        util.format.apply(util, arguments) + '\n');
}

// 4. 如何降权
http.createServer().listen(80, function () {
    let env = process.env,
        uid = parseInt(env['SUDO_UID'] || process.getuid(), 10),
        gid = parseInt(env['SUDO_GID'] || process.getgid(), 10);

    process.setgid(gid);
    process.setuid(uid);
});