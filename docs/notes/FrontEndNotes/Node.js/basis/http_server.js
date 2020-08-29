// HTTP
// 实现一个简单的HTTP服务器
let http = require('http');

http.createServer(function(request, response) {
    response.writeHead(200, {'Content-Type': 'text-plain'});
    response.end('Hello World!\n');
}).listen(8124);


// HTTP
// 'http'模块提供两种使用方式：
// 1. 作为服务端使用时，创建一个HTTP服务器，监听HTTP客户端请求并返回响应
// 2. 作为客户端使用时，发起一个HTTP客户端请求，获取服务端响应

// 服务端模式下的工作流程，首先需要使用.createServer方法创建一个服务器，然后调用.listen方法监听端口。
// 之后，每当来了一个客户端请求，创建服务器时传入的回调函数就被调用一次，可以看出，这是一种事件机制。
// HTTP请求本质上是一个数据流，由请求头（headers）和请求体（body）组成。

// POST / HTTP/1.1
// User-Agent: curl/7.26.0
// Host: localhost
// Accept: */*
// Content-Length: 11
// Content-Type: application/x-www-form-urlencoded
//
// Hello World

// 可以看到，空行之上是请求头，之下是请求体。HTTP请求在发送给服务器时，可以认为时按照从头到尾的顺序一个字节一个字节地以数据流方式发送的。
// 而http模块创建的HTTP服务器在接收到完整的请求头后，就会调用回调函数
// 在回调函数中，除了可以使用request对象访问请求头数据外，还能把request对象当作一个只读数据流来访问请求体数据
http.createServer(function (request, response) {
    let body = [];
    console.log(request.method);
    console.log(request.headers);

    request.on('data', function (chunk) {
        body.push(chunk);
    });

    request.on('end', function () {
        body = Buffer.concat(body);
        console.log(body.toString());
    });
}).listen(8125);

// 把response对象当作一个只写数据流来写入响应体数据
http.createServer(function (request, response) {
    response.writeHead(200, { 'Content-Type': 'text/plain' });

    request.on('data', function (chunk) {
        response.write(chunk);
    });

    request.on('end', function () {
        response.end();
    });
}).listen(8126);


// 客户端模式下的工作流程，为了发起一个客户端HTTP请求，需要指定目标服务器的位置并发送请求头和请求体
let options = {
    hostname: 'www.baidu.com',
    port: 8127,
    path: '/upload',
    method: 'POST',
    headers: {
        'Content-Type': 'pplication/x-www-form-urlencoded'
    }
};

let request = http.request(options, function(response){

});

// 创建了一个客户端，并指定请求目标和请求头数据
request.write('Hello World C!');
request.end();


// 由于HTTP请求中GET请求是最常见的一种，并且不需要请求体
http.get('http://www.baidu.com/', function (response) {
    let body = [];

    console.log(response.statusCode);
    console.log(response.headers);

    response.on('data', function (chunk) {
        body.push(chunk);
    });

    response.on('end', function () {
        body = Buffer.concat(body);
        console.log(body.toString());
    });
});