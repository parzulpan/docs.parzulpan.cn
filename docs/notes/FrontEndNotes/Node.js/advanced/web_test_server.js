// Web服务器一般指网站服务器，是指驻留于因特网上某种类型计算机的程序，Web服务器的基本功能就是提供Web信息浏览服务。
// 它只需支持HTTP协议、HTML文档格式及URL等，与客户端的网络浏览器配合。
// 目前最主流的三个Web服务器是Apache、Nginx、IIS

// Web应用架构：
// Client(Mobile Browser、Web Browser、Application) - 客户端，一般指浏览器，浏览器可以通过 HTTP 协议向服务器请求数据
// Server - 服务端，一般指 Web 服务器，可以接收客户端请求，并向客户端发送响应数据
// Business - 业务层， 通过 Web 服务器处理应用程序，如与数据库交互，逻辑运算，调用外部程序等
// Data - 数据层，一般由数据库组成


// 创建 Web 服务器
const http = require('http');
const fs = require('fs');
const url = require('url');

http.createServer(function (request, response) {
    // 解析请求，包括文件名等
    let pathName = url.parse(request.url).pathname;

    // 输出请求的文件名
    console.log(`Request for ${pathName} received.`);

    // 从文件系统中读取请求的文件内容
    fs.readFile(pathName.substr(1), function(err, data) {
        if(err) {
            console.log(err);
            // HTTP 状态码: 404 : NOT FOUND
            response.writeHead(404, {'Content-Type': 'text/html'});
        } else {
            // HTTP 状态码: 200 : OK
            response.writeHead(200, {'Content-Type': 'text/html'});

            // 响应文件内容
            response.write(data.toString());
        }

        // 发生响应数据
        response.end();
    });
}).listen(2333);

console.log('Server running at http://localhost:2333/');


