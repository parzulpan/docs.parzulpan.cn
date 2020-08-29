// OS 模块

const os = require('os');


// 返回操作系统的默认临时文件夹
console.log(`tmpdir : ${os.tmpdir()}`);

// 返回 CPU 的字节序，可能的是 "BE" 或 "LE"
console.log('endianness : ' + os.endianness());

// 返回操作系统的主机名
console.log('hostname : ' + os.hostname());

// 返回操作系统名
console.log('type : ' + os.type());

// 返回编译时的操作系统名
console.log('platform : ' + os.platform());

// 返回操作系统 CPU 架构，可能的值有 "x64"、"arm" 和 "ia32"
console.log(`arch : ${os.arch()}`);

// 返回操作系统的发行版本
console.log(`release : ${os.release()}`);

// 返回操作系统运行的时间，以秒为单位
console.log(`uptime : ${os.uptime()}`);

// 返回一个包含 1、5、15 分钟平均负载的数组
console.log(`loadavg : ${os.loadavg()}`);

// 返回系统内存总量
console.log('totalmem : ' + os.totalmem() + " bytes.");

// 返回操作系统空闲内存量
console.log('free memory : ' + os.freemem() + " bytes.");

// 返回一个对象数组，包含所安装的每个CPU/内核的信息：
// 型号、速度（单位 MHz）、时间（一个包含 user、nice、sys、idle 和 irq 所使用 CPU/内核毫秒数的对象）。
console.log(`cpus : ${os.cpus()}`);

// 获得网络接口列表
console.log(`networkInterfaces : ${os.networkInterfaces()}`);