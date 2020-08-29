// 创建 Web 客户端

const http = require('http');

// 用于请求的选项
let options = {
    host: 'localhost',
    port: 2333,
    path: '/express_get.html'
};

// 处理响应的回调函数
let callback = function(response) {
    // 不断更新数据
    let body = '';
    response.on('data', function(data) {
        body += data;
    });

    response.on('end', function() {
        // 数据接收完成
        console.log(body);
    });
}

// 向服务端发送数据
let request = http.request(options, callback);
request.end();

