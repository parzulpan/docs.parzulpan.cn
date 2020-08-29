// Net
const net = require('net');


// net模块可用于创建Socket服务器或Socket客户端，
// 使用Socket搭建一个很不严谨的HTTP服务器，这个HTTP服务器不管收到啥请求，都固定返回相同的响应
net.createServer(function(connection) {
    connection.on('data', function(data) {
        connection.write([
            'HTTP/1.1 200 OK',
            'Content-Type: text/plain',
            'Content-Length: 11',
            '',
            'Hello World'
        ].join('\n'));
    });
}).listen(8764);


// 使用Socket发起HTTP客户端请求，socket客户端在建立连接后发送了一个HTTP GET请求，并通过data事件监听函数来获取服务器响应
let options = {
    port: 80,
    host: 'www.baidu.com'
};

let client = net.connect(options, function() {
    client.write([
        'GET / HTTP/1.1',
        'User-Agent: curl/7.26.0',
        'Host: www.baidu.com',
        'Accept: */*',
        '',
        ''
    ].join('\n'));
});
client.on('data', function(data) {
    console.log(data.toString());
    client.end();
})