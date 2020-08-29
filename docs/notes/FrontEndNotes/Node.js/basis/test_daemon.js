// 守护子进程
// 守护进程一般用于监控工作进程的运行状态，在工作进程不正常退出时重启工作进程，保障工作进程不间断运行。
const child_process = require('child_process');

function spawn(mainModule) {
    let worker = child_process.spawn('node', [mainModule]);

    worker.on('exit', function(code) {
        if(code !== 0) {
            console.log('工作进程非正常退出时，守护进程立即重启工作进程');
            spawn(mainModule);
        }
    });
}

spawn('ipc_parent.js');