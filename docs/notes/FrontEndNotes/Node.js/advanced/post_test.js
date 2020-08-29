// POST请求

const http = require('http');
const querystring = require('querystring');
const util = require('util');

// 基本语法
// http.createServer(function (request, response) {
//     // 定义了一个post变量，用于暂存请求体的信息
//     let post = '';
//
//     // 通过request的data事件监听函数，每当接受到请求体的数据，就累加到post变量中
//     request.on('data', function(chunk) {
//         post += chunk;
//     })
//
//     // // 在end事件触发后，通过querystring.parse将post解析为真正的POST请求格式，然后向客户端返回
//     request.on('end', function() {
//         post = querystring.parse(post);
//         response.end(util.inspect(post));
//     });
// }).listen(8083);


// 表单通过POST提交并输出数据
let postHTML =
    '<html><head><meta charset="utf-8"><title> Node.js 演示例子</title></head>' +
    '<body>' +
    '<form method="post">' +
    'NAME: <input name="name"><br>' +
    'URL: <input name="url"><br>' +
    '<input type="submit">' +
    '</form>' +
    '</body>' +
    '</html>';

http.createServer(function (request, response) {
    console.log(`创建服务器...`)
    let body = '';

    request.on('data', function (chunk) {
        console.log(`data...`)
        body += chunk;
    });

    request.on('end', function () {
        console.log(`end...`)
        body = querystring.parse(body);

        response.writeHead(200, {'Content-Type': 'text/html; charset=utf8'});

        if(body.name && body.url) {
            response.write(`NAME: ${body.name}`);
            response.write('<br>')
            response.write(`URL: ${body.url}`);
        } else {
            response.write(postHTML);
        }

        response.end();
    });
}).listen(3000);





