// 创建子进程
const child_process = require('child_process');


let child = child_process.spawn('node', ['./traverse_dir.js']);
child.stdout.on('data', function(data) {
    console.log('stdout: ' + '\n' + data);
});

child.stderr.on('data', function(data) {
    console.log('stderr: ' + '\n' + data);
});

child.on('close', function(code) {
    console.log('child process exit with code: ' + '\n' + code);
});