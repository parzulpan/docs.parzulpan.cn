// Zlib
const zlib = require('zlib');
const http = require('http');


// zlip模块提供了数据压缩和解压的功能，当处理HTTP请求和响应时，可能需要这个模块
// 判断客户端是否支持gzip，并在支持的情况下使用zlib模块返回gzip之后的响应体数据
http.createServer(function (request, response) {
    let i = 1024;
    let data = '';

    while (i--) {
        data += '.';
    }

    if ((request.headers['accept-encoding'] || '').indexOf('gzip') !== -1) {
        console.log('客户端支持gzip');
        zlib.gzip(data, function (err, data) {
            response.writeHead(
                200,
                {'Content-Type': 'text/plain', 'Content-Encoding': 'gzip'}
                );
            response.end(data);
        });
    } else {
        console.log('客户端不支持gzip');
        response.writeHead(
            200,
            {'Content-Type': 'text/plain'}
        );
        response.end(data);
    }
}).listen(8765);


// 判断服务端响应是否使用gzip压缩，并在压缩的情况下使用zlib模块解压响应体数据
let options = {
    hostname: 'www.baidu.com',
    port: 80,
    path: '/',
    method: 'GET',
    headers: {
        'Accept-Encoding': 'gzip, deflate'
    }
}
http.request(options, function(response) {
    let body = [];

    response.on('data', function(chunk) {
        body.push(chunk);
    });

    response.on('end', function() {
        body = Buffer.concat(body);

        if(response.headers['content-encoding'] === 'gzip') {
            console.log('服务端响应使用gzip压缩');
            zlib.gunzip(body, function(err, data) {
                console.log(data.toString());
            });
        } else {
            console.log('服务端响应使用gzip压缩');
            console.log(data.toString());
        }
    });
}).end();